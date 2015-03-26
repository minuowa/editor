#include "stdafx.h"
#include "EObjListSheetTreeView.h"
#include "qwidget.h"
#include "QMenu.h"
#include "qevent.h"
#include "Game.h"
#include "qshortcut.h"
#include "qkeysequence.h"
#include "EEditorManager.h"
#include "EObjectListSheet.h"
#include "Editorapp.h"

EObjListSheetTreeView::EObjListSheetTreeView ( QWidget *parent/* = 0*/ )
    : QTreeView ( parent )
{
    setContextMenuPolicy ( Qt::ActionsContextMenu );

    mMainMenu = new QMenu ( this );

    mComponentMenu = new QMenu ( "&Component" );
    connect ( mComponentMenu, SIGNAL ( triggered ( QAction* ) ), this, SLOT ( onComponentAction (  QAction* ) ) );
    mMainMenu->addMenu ( mComponentMenu );

    mObjectMenu = new QMenu ( "&GameObject" );
    mMainMenu->addMenu ( mObjectMenu );

    mObjectMenu->addAction ( tr ( "&Delete(Shift+Del)" ), this, SLOT ( deleteObj() ) );

    QShortcut* shortcut = new QShortcut ( QKeySequence ( Qt::SHIFT + Qt::Key_Delete ), this );
    connect ( shortcut, SIGNAL ( activated() ), this, SLOT ( deleteObj() ) );
}


EObjListSheetTreeView::~EObjListSheetTreeView ( void )
{
    dSafeDelete ( mObjectMenu );
    dSafeDelete ( mComponentMenu );
}

void EObjListSheetTreeView::mouseReleaseEvent ( QMouseEvent *event )
{
    __super::mouseReleaseEvent ( event );
    if ( event->button( ) == Qt::RightButton )
    {
        //CXASSERT ( 0 );
        //CreatePopupMenu();

    }
}

bool EObjListSheetTreeView::event ( QEvent* event )
{
    switch ( event->type() )
    {
    case QEvent::ContextMenu:
    {
        QString obj = EditorApp::Editor.getSelectObj();
        if ( !obj.isEmpty() )
        {
            QContextMenuEvent* menuEvent = ( QContextMenuEvent* ) event;
            CXASSERT ( mMainMenu );
            mMainMenu->exec ( menuEvent->globalPos() );
        }
    }
    break;
    }
    return __super::event ( event );
}

void EObjListSheetTreeView::deleteObj()
{
    QString selObj = EditorApp::Editor.getSelectObj();
    if ( !selObj.isEmpty() )
    {
         Content::Scene.deleteObj ( selObj.toStdString().c_str() );
        EditorApp::Editor.clearSelect();
        EditorApp::Editor.updatePropertySheet();
    }
}

void EObjListSheetTreeView::initComponentMenu (   )
{
    /** @brief add obj **/
	CharStringArr componentTypeArr;
	typedef GComponentFactory::ComponentCreatorMap ComponentCreatorMap;
	const ComponentCreatorMap& nodeCreatorMap =
		Content::ComponentFactory.getCreators();
	ComponentCreatorMap::const_iterator walk = nodeCreatorMap.begin();
	ComponentCreatorMap::const_iterator end = nodeCreatorMap.end();
	for ( ; walk != end; ++walk )
	{
		componentTypeArr.push_back ( walk->first.c_str() );
	}

    CharStringArr::const_iterator it ( componentTypeArr.begin() );
    CharStringArr::const_iterator iend ( componentTypeArr.end() );
    for ( ; it != iend; ++it )
    {
        const GString& name = *it;
        QAction* action = new QAction ( name.c_str(), this );
        action->setCheckable ( true );
        action->setChecked ( false );
        mComponentMenu->addAction ( action );
    }
}

void EObjListSheetTreeView::onComponentAction ( QAction* action )
{
    QString componentTypeName = action->text();
    const QString& name = EditorApp::Editor.getSelectObj();

    GNode* node =  Content::Scene.getObj ( name.toStdString().c_str() );
    CXASSERT ( node );
    if ( action->isChecked() )
    {
        node->attachComponent ( componentTypeName.toStdString().c_str() );
    }
    else
    {
        node->detachComponent ( componentTypeName.toStdString().c_str() );
    }
}

void EObjListSheetTreeView::updateMenus()
{
    QString name = EditorApp::Editor.getSelectObj();
    GNode* target =  Content::Scene.getObj ( name.toStdString().c_str() );
    CXASSERT ( target );

    resetComponentMenuState();

    GComponentOwner& owner = target->getComponentOwner();

    for ( int i = 0; i < eComponentType_Count; ++i )
    {
        GComponentInterface* component = owner.getComponent ( ( eComponentType ) i );
        if ( component )
        {
            setComponentMenuState ( component->getComponentName(), true, component->canDetach()  );
        }
    }
}

void EObjListSheetTreeView::setComponentMenuState ( const char* componentType, bool checked, bool enabled )
{
    assert ( mComponentMenu );
    QList<QAction*> actionList = mComponentMenu->actions();
    int cnt = actionList.count();

    for ( int i = 0; i < cnt; ++i )
    {
        QAction* action = actionList[i];
        if ( action->text() == componentType )
        {
            action->setChecked ( checked );
            action->setEnabled ( enabled );
        }
    }
}

void EObjListSheetTreeView::resetComponentMenuState()
{
    assert ( mComponentMenu );
    QList<QAction*> actionList = mComponentMenu->actions();
    int cnt = actionList.count();

    for ( int i = 0; i < cnt; ++i )
    {
        QAction* action = actionList[i];
        action->setChecked ( false );
        action->setEnabled ( true );
    }
}

void EObjListSheetTreeView::initObjectMenu (  )
{
	CharStringArr gameobjTypeArr;
	typedef GFactory<GNode>::ObjCreatorMap GNodeCreatorMap;
	const GNodeCreatorMap& nodeCreatorMap = Content::GameObjFactory.getCreators();
	GNodeCreatorMap::const_iterator walk = nodeCreatorMap.begin();
	GNodeCreatorMap::const_iterator end = nodeCreatorMap.end();
	for ( ; walk != end; ++walk )
	{
		gameobjTypeArr.push_back ( walk->first.c_str() );
	}
    QMenu* menu = mObjectMenu->addMenu ( "Add" );
    CharStringArr::const_iterator it ( gameobjTypeArr.begin() );
    CharStringArr::const_iterator iend ( gameobjTypeArr.end() );
    for ( ; it != iend; ++it )
    {
        const GString& name = *it;
        menu->addAction ( name.c_str() );
    }
    connect ( menu, SIGNAL ( triggered ( QAction* ) ), this, SLOT ( onAddObjectAction (  QAction* ) ) );

}

void EObjListSheetTreeView::onAddObjectAction ( QAction* action )
{
    QString typeName = action->text();
    EditorApp::Editor.getObjectListSheet()->addChildByType ( typeName.toStdString().c_str() );
}
