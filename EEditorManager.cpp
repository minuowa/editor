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
//-------------------------------------------------------------------------
EEditorManager::EEditorManager ( void )
    : mWindowProc ( 0 )
    , mParent ( 0 )
{
}


EEditorManager::~EEditorManager ( void )
{
    TheSceneMgr->mDelegateReloadScene -= this;

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

    initObjectMenu ( TheSceneMgr->getGameObjectTypes() );
    mObjectListSheet->getView()->initComponentMenu ( TheSceneMgr->getObjectComponentTypes() );

    GNode::mDelegateComponentChange += this;
    GObject::mDelegateAlterName += this;
    TheSceneMgr->mDelegateReloadScene += this;

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




void EEditorManager::initObjectMenu ( const CharStringArr& gameobjTypeArr )
{
    mObjectListSheet->getView()->initObjectMenu ( gameobjTypeArr );
}

void EEditorManager::setComponentMenuState ( const char* componentType, bool checked, bool enabled )
{
    mObjectListSheet->getView()->setComponentMenuState ( componentType, checked, enabled );
}




void EEditorManager::notifyPropertyChange ( void* pre, void* changed )
{
    const QString& name = getSelectObj();

    GNode* node = TheSceneMgr->getObj ( name.toStdString().c_str() );
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
    GNode* target = TheSceneMgr->getObj ( mSelectedObj.toStdString().c_str() );
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

    GNode* node = TheSceneMgr->getObj ( name.toStdString().c_str() );
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

const QString& EEditorManager::getSelectObj() const
{
    return mSelectedObj;
}

EPropertySheet* EEditorManager::getPropertySheet() const
{
    return mObjectPropertySheet;
}


