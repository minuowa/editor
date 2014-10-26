#include "stdafx.h"
#include "EEditorManager.h"
#include "EPropertySheet.h"
#include "EObjectListSheet.h"
#include "qmenu.h"
#include "EObjListSheetTreeView.h"
#include "qmainwindow.h"
#include "qmenubar.h"
#include "qcoreapplication.h"
#include "qapplication.h"
#include "Game.h"
#include "editor.h"
#include "QDockWidget.h"
#include "qcombobox.h"
//-------------------------------------------------------------------------
EEditorManager::EEditorManager ( void )
    : mWindowProc ( 0 )
    , mParent ( 0 )
{
}


EEditorManager::~EEditorManager ( void )
{
    dSafeDelete ( mObjectMenu );
    TheSceneMgr->mDelegateReloadScene -= this;

}

bool EEditorManager::init ( Editor* parent )
{
    mParent = parent;

    mObjectPropertySheet = new EPropertySheet ( parent->getObjectEditPanel() );
    parent->getObjectEditPanel()->setWidget ( mObjectPropertySheet->getView() );

    mOptionSheet = new EPropertySheet ( parent->getOptionPanel() );
    parent->getOptionPanel()->setWidget ( mOptionSheet->getView() );

    if ( 0 )
    {
        QComboBox* pbox = new QComboBox ( mOptionSheet->getView() );
        pbox->setGeometry ( 20, 100, 50, 30 );
        pbox->addItem ( "1" );
        pbox->addItem ( "2" );
        pbox->addItem ( "3" );
        pbox->addItem ( "4" );
        pbox->setCurrentText ( "3" );
        pbox->setCurrentIndex ( 1 );
    }


    mObjectListSheet = new EObjectListSheet ( mParent );
    parent->getObjectListPanel()->setWidget ( mObjectListSheet->getView() );

    mObjectMenu = new QMenu ( "&GameObject"  );
    mParent->menuBar()->addMenu ( mObjectMenu );

    initObjectMenu ( TheSceneMgr->getGameObjectTypes() );
    mObjectListSheet->getView()->initComponentMenu ( TheSceneMgr->getObjectComponentTypes() );

    //mComponentMenu->hide();

    GNode::mDelegateComponentChange += this;
    GObject::mDelegateAlterName += this;
    TheSceneMgr->mDelegateReloadScene += this;

    updateOptionSheet();

    updateObjectList();

    //mOptionSheet->hide();
    //mObjectPropertySheet->hide();

    return true;
}



QTreeView* EEditorManager::getPropertyView() const
{
    return mObjectPropertySheet->getView();
}

QTreeView* EEditorManager::getObjectListView() const
{
    return mObjectListSheet->getView();
}

EObjectListSheet* EEditorManager::getObjectListSheet() const
{
    return mObjectListSheet;
}




void EEditorManager::initObjectMenu ( const CharStringArr& gameobjTypeArr )
{
    QMenu* menu = mObjectMenu->addMenu ( "AddObject" );
    CharStringArr::const_iterator it ( gameobjTypeArr.begin() );
    CharStringArr::const_iterator iend ( gameobjTypeArr.end() );
    for ( ; it != iend; ++it )
    {
        const GString& name = *it;
        menu->addAction ( name.c_str() );
    }
    connect ( menu, SIGNAL ( triggered ( QAction* ) ), this, SLOT ( onAddObjectAction (  QAction* ) ) );
}

void EEditorManager::setComponentMenuState ( const char* componentType, bool checked, bool enabled )
{
    mObjectListSheet->getView()->setComponentMenuState ( componentType, checked, enabled );
}




void EEditorManager::onAddObjectAction ( QAction* action )
{
    QString typeName = action->text();
    mObjectListSheet->addChildByType ( typeName.toStdString().c_str() );
}



void EEditorManager::notifyPropertyChange ( void* pre, void* changed )
{
    const QString& name = getSelectObj();

    GNode* node = TheSceneMgr->getNodeByName ( name.toStdString().c_str() );
    if ( node )
        node->onPropertyChange ( pre, changed );
}

void EEditorManager::updateObjectList()
{
    mObjectListSheet->updateAll();
}

void EEditorManager::SetSelectObj ( const char* obj )
{
    mSelectedObj = obj;

    updatePropertySheet();

    updatePopMenu();
}

void EEditorManager::onCallBack ( const CXDelegate& xdelegate )
{
    if ( xdelegate == GNode::mDelegateComponentChange )
    {
        GNode* target = TheSceneMgr->getNodeByName ( mSelectedObj.toStdString().c_str() );

        if ( target != nullptr )
        {
            if ( GNode::mOperatorObj == target )
            {
                updatePopMenu();
                updatePropertySheet();
            }
        }
    }
    else if ( xdelegate == GObject::mDelegateAlterName )
    {
        mObjectListSheet->alterItemName ( GObject::mOperatorObjectName, GObject::mTargetName );
    }
    else if ( xdelegate == TheSceneMgr->mDelegateReloadScene )
    {
        updateObjectList();
        updatePropertySheet();
    }
}

void EEditorManager::updatePopMenu()
{
    mObjectListSheet->getView()->updateMenus();
}

void EEditorManager::updatePropertySheet()
{
    GNode* target = TheSceneMgr->getNodeByName ( mSelectedObj.toStdString().c_str() );
    if ( !target )
    {
        mObjectPropertySheet->clearPropertyies();
        return;
    }

    CXASSERT ( target );
    mObjectPropertySheet->update ( target );
}

void EEditorManager::notifyPropertyChangeEnd ( void* cur )
{
    const QString& name = getSelectObj();

    GNode* node = TheSceneMgr->getNodeByName ( name.toStdString().c_str() );
    if ( node )
        node->onPropertyChangeEnd ( cur );

    GameOption->onPropertyChangeEnd ( cur );
}

void EEditorManager::updateOptionSheet()
{
    mOptionSheet->update ( GameOption, false );
}

Editor* EEditorManager::getMainWindow()
{
    return ( Editor* ) mParent;
}

void EEditorManager::clearSelect()
{
    mSelectedObj.clear();
}


