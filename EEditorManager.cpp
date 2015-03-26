#include "stdafx.h"
#include "Game.h"
#include "EEditorManager.h"
#include "EPropertySheet.h"
#include "EObjectListSheet.h"
#include "qmenu.h"
#include "EObjListSheetTreeView.h"
#include "qmainwindow.h"
#include "qmenubar.h"
#include "qcoreapplication.h"
#include "qapplication.h"
#include "editor.h"
#include "QDockWidget.h"
#include "qcombobox.h"
#include "EFilmSheet.h"
#include "..\Content\Content.h"
//-------------------------------------------------------------------------
EEditorManager::EEditorManager ( void )
    : mWindowProc ( 0 )
    , mParent ( 0 )
{
}


EEditorManager::~EEditorManager ( void )
{
    Content::Scene.mDelegateReloadScene -= this;
}

bool EEditorManager::init ( Editor* parent )
{
    mParent = parent;

    mObjectPropertySheet = new EPropertySheet ( parent->getObjectEditPanel() );
    parent->getObjectEditPanel()->setWidget ( mObjectPropertySheet->getView() );

    mOptionSheet = new EPropertySheet ( parent->getOptionPanel() );
    parent->getOptionPanel()->setWidget ( mOptionSheet->getView() );

    mFilmSheet = new EFilmSheet ( mParent );
    parent->getFilmPanel()->setWidget ( ( QWidget* ) mFilmSheet );

    mObjectListSheet = new EObjectListSheet ( mParent );
    parent->getObjectListPanel()->setWidget ( mObjectListSheet->getView() );



    initObjectMenu (   );



    mObjectListSheet->getView()->initComponentMenu (  );

    GNode::mDelegateComponentChange += this;
    GObject::mDelegateAlterName += this;
    Content::Scene.mDelegateReloadScene += this;

    updateOptionSheet();
    updateObjectList();


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




void EEditorManager::initObjectMenu ( )
{

    mObjectListSheet->getView()->initObjectMenu (  );
}

void EEditorManager::setComponentMenuState ( const char* componentType, bool checked, bool enabled )
{
    mObjectListSheet->getView()->setComponentMenuState ( componentType, checked, enabled );
}




void EEditorManager::notifyPropertyChange ( void* pre, void* changed )
{
    const QString& name = getSelectObj();

    GNode* node =  Content::Scene.getObj ( name.toStdString().c_str() );
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

void EEditorManager::onCallBack ( const CXDelegate& xdelegate, CXEventArgs* args )
{
    if ( xdelegate == GNode::mDelegateComponentChange )
    {
        GNodeComponentChangeArgs* arg = ( GNodeComponentChangeArgs* ) args;

        if ( !arg->mChangedNode.empty() )
        {
            if ( 0 == arg->mChangedNode.compare ( mSelectedObj.toStdString().c_str() ) )
            {
                updatePopMenu();
                updatePropertySheet();
            }
        }
    }
    else if ( xdelegate == GObject::mDelegateAlterName )
    {
        CXAlterNameArgs* arg = ( CXAlterNameArgs* ) args;
        mObjectListSheet->alterItemName ( arg->mCurName, arg->mChangedName );
    }
    else if ( xdelegate ==  Content::Scene.mDelegateReloadScene )
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
    GNode* target =  Content::Scene.getObj ( mSelectedObj.toStdString().c_str() );
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

    GNode* node =  Content::Scene.getObj ( name.toStdString().c_str() );
    if ( node )
        node->onPropertyChangeEnd ( cur );

    Content::GameOption.onPropertyChangeEnd ( cur );
}

void EEditorManager::updateOptionSheet()
{
    mOptionSheet->update ( &Content::GameOption, false );
}

Editor* EEditorManager::getMainWindow()
{
    return ( Editor* ) mParent;
}

void EEditorManager::clearSelect()
{
    mSelectedObj.clear();
}

const QString& EEditorManager::getSelectObj() const
{
    return mSelectedObj;
}

EPropertySheet* EEditorManager::getPropertySheet() const
{
    return mObjectPropertySheet;
}


