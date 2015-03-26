#include "stdafx.h"
#include "EObjectListSheet.h"
#include "qwidget.h"
#include "qtreeview.h"
#include "qstandarditemmodel.h"
#include "EEditorManager.h"
#include "EObjListSheetTreeView.h"
#include "XSingleton.h"
#include "Game.h"
#include "qshortcut.h"
#include "qkeysequence.h"
#include "Editorapp.h"
EObjectListSheet::EObjectListSheet ( QWidget *parent/*=0*/ )
    : QObject ( parent )
{
    mTreeView = new EObjListSheetTreeView ( parent );
    mTreeModel = new QStandardItemModel();
    mTreeView->setModel ( mTreeModel );
    mTreeView->setWindowTitle ( "Simple Tree Model" );
    mTreeView->setBaseSize ( 200, 300 );
    QSizePolicy sizePolicy ( QSizePolicy::Expanding, QSizePolicy::Expanding );
    mTreeView->setSizePolicy ( sizePolicy );

    QItemSelectionModel* selectionModel = mTreeView->selectionModel();
    bool res = connect ( selectionModel, SIGNAL ( selectionChanged ( const QItemSelection &, const QItemSelection & ) ),
                         this, SLOT ( onSelectionChanged ( const QItemSelection &, const QItemSelection & ) ) );
    CXASSERT ( res );

    GNode::mDelegateAddObj += this;
    GNode::mDelegateDeleteObj += this;
}


EObjectListSheet::~EObjectListSheet ( void )
{
    clearTreeItem();
    dSafeDelete ( mTreeModel );
}

void EObjectListSheet::updateItemByAddObj ( const char* name, const char* parentName/*=0*/ )
{
    if ( nullptr == name )
        return;
    if ( nullptr == parentName )
        return;
    QStandardItem* root = mTreeModel->item ( 0, 0 );
    QStandardItem* newobj = new QStandardItem ( name );
    newobj->setEditable ( false );
    if ( root )
    {
        QStandardItem* parent = 0;
        if ( parentName )
        {
            parent = getItem ( parentName );
        }
        if ( !parent )
        {
            dSafeDelete ( newobj );
            return;
        }
        CXASSERT_RETURN ( parent );
        //mTreeModel->setRowCount ( mTreeModel->rowCount() + 1 );
        parent->appendRow ( newobj );
    }
    else
    {
        root = newobj;
        mTreeModel->setRowCount ( 1 );
        mTreeModel->setItem ( 0, 0, root );
        mTreeView->expand ( root->index() );
    }
}


QStandardItem* EObjectListSheet::getItem ( const char* name )
{
    QStandardItem* item = 0;
    QStandardItem* root = mTreeModel->item ( 0, 0 );
    eFindItem ( root, name, item );
    return item;
}

void EObjectListSheet::show()
{
    mTreeView->show();
}

void EObjectListSheet::onSelect ( const QModelIndex& index )
{
    QVariant var = mTreeModel->data ( index );
    if ( var.type() != QVariant::String )
        return;

    EditorApp::Editor.SetSelectObj ( var.toString().toStdString().c_str() );
}

void EObjectListSheet::onSelectionChanged ( const QItemSelection &selected, const QItemSelection &/*deselected*/ )
{
    const QModelIndexList&  indexlist = selected.indexes();
    CXASSERT ( indexlist.size() == 1 );
    {
        onSelect ( indexlist.front() );
    }
}

void EObjectListSheet::onCallBack ( const CXDelegate& delgate, CXEventArgs* args )
{
    if ( delgate == GNode::mDelegateAddObj )
    {
        GNodeAddArgs* arg = ( GNodeAddArgs* ) args;

        updateItemByAddObj ( arg->mAddNode, arg->mAddNodeParent );
    }
    else if ( delgate == GNode::mDelegateDeleteObj )
    {
        GNodeDeleteArgs* arg = ( GNodeDeleteArgs* ) args;
        updateItemByDeleteObj ( arg->mDeleteNode );
    }
}

void EObjectListSheet::updateAll()
{
    clearTreeItem();

    auto root =  Content::Scene.getSceneRoot();
    QStandardItem* rootItem = mTreeModel->item ( 0, 0 );
    if ( rootItem == nullptr )
    {
        rootItem = new QStandardItem;
        mTreeModel->setItem ( 0, 0, rootItem );
    }
    addChild ( root, rootItem );
}

void EObjectListSheet::addChild ( GNode* node, QStandardItem* item )
{
    item->setEditable ( false );
    item->setText ( node->getName() );

    size_t cnt = node->mChildren.size();

    item->setRowCount ( cnt );

    for ( size_t i = 0; i < cnt; ++i )
    {
        GNode* child = node->mChildren[i];
        QStandardItem* newItem = new QStandardItem;
        item->setChild ( i, newItem );
        addChild ( child, newItem );
    }
}

void EObjectListSheet::addChildByType ( const char* typeName )
{
     Content::Scene.addObj ( EditorApp::Editor.getSelectObj().toStdString().c_str(), typeName );
}

void EObjectListSheet::alterItemName ( const char* oldName, const char* targetName )
{
    CXASSERT ( oldName );
    CXASSERT ( targetName );
    QStandardItem* item = getItem ( oldName );
    CXASSERT ( item );
    item->setText ( targetName );
    //EditorApp::Editor.SetSelectObj ( targetName );
}

void EObjectListSheet::clearTreeItem()
{
    int row = mTreeModel->rowCount();
    int col = mTreeModel->columnCount();
    for ( int i = 0; i < row; ++i )
    {
        for ( int j = 0; j < col; ++j )
        {
            QStandardItem* child = mTreeModel->item ( i, j );
            dSafeDelete ( child );
        }
    }
    mTreeModel->clear();
}

void EObjectListSheet::updateItemByDeleteObj ( const char* name )
{
    if ( nullptr == name )
        return;
    QStandardItem* root = mTreeModel->item ( 0, 0 );
    if ( root )
        deleteItem ( root, name );
}

bool EObjectListSheet::getItemPosition ( int& r, int& c, const char* text )
{
    int row = mTreeModel->rowCount();
    int col = mTreeModel->columnCount();
    //QStandardItem* item = 0;
    for ( int i = 0; i < row; ++i )
    {
        for ( int j = 0; j < col; ++j )
        {
            QStandardItem* child = mTreeModel->item ( i, j );
            if ( child )
            {
                if ( child->text() == text )
                {
                    r = i;
                    c = j;
                    return true;
                }
                else
                {
                    //if ( getItemPosition ( r, c, text ) )
                    //    return true;
                }
            }
        }
    }
    return false;
}



void EObjectListSheet::deleteItem ( QStandardItem* parent, const char* name )
{
    int row = parent->rowCount();
    int col = parent->columnCount();

    for ( int i = 0; i < row; ++i )
    {
        for ( int j = 0; j < col; ++j )
        {
            QStandardItem* item = parent->child ( i, j );
            if ( item )
            {
                if ( item->text() == name )
                {
                    parent->takeChild ( i, j );
                    parent->removeRow ( i );
                    dSafeDelete ( item );
                    return;
                }
                else
                {
                    deleteItem ( item, name );
                }
            }
        }
    }
}




