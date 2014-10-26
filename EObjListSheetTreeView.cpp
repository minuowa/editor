#include "stdafx.h"
#include "EObjListSheetTreeView.h"
#include "qwidget.h"
#include "QMenu.h"
#include "qevent.h"
#include "Game.h"
#include "qshortcut.h"
#include "qkeysequence.h"
#include "EEditorManager.h"


EObjListSheetTreeView::EObjListSheetTreeView ( QWidget *parent/* = 0*/ )
    : QTreeView ( parent )
{
    setContextMenuPolicy ( Qt::ActionsContextMenu );

    mComponentMenu = new QMenu ( ( QWidget* ) EditorMgr->getMainWindow() );
    connect ( mComponentMenu, SIGNAL ( triggered ( QAction* ) ), this, SLOT ( onComponentAction (  QAction* ) ) );
    //QAction* a1=new QAction(this);
    //a1->setShortcut(QKeySequence(tr("Ctrl+D")));
    //this->addAction(a1);
    //connect(a1,SIGNAL(triggered()),this,SLOT(close()));

    QShortcut* shortcut = new QShortcut ( QKeySequence ( Qt::SHIFT + Qt::Key_Delete ), this );
    connect ( shortcut, SIGNAL ( activated() ), this, SLOT ( deleteObj() ) );
}


EObjListSheetTreeView::~EObjListSheetTreeView ( void )
{
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
        QString obj = EditorMgr->getSelectObj();
        if ( !obj.isEmpty() )
        {
            QContextMenuEvent* menuEvent = ( QContextMenuEvent* ) event;
            CXASSERT ( mComponentMenu );
            mComponentMenu->exec ( menuEvent->globalPos() );
        }
    }
    break;
    }
    return __super::event ( event );
}

void EObjListSheetTreeView::deleteObj()
{
    QString selObj = EditorMgr->getSelectObj();
    if ( !selObj.isEmpty() )
    {
        TheSceneMgr->deleteObj ( selObj.toStdString().c_str() );
        EditorMgr->clearSelect();
        EditorMgr->updatePropertySheet();
    }
}

void EObjListSheetTreeView::initComponentMenu ( const CharStringArr& componentTypeArr )
{
    /** @brief add obj **/

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
    const QString& name = EditorMgr->getSelectObj();

    GNode* node = TheSceneMgr->getNodeByName ( name.toStdString().c_str() );
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
    QString name = EditorMgr->getSelectObj();
    GNode* target = TheSceneMgr->getNodeByName ( name.toStdString().c_str() );
    CXASSERT ( target );

    resetComponentMenuState();

    GComponentOwner& owner = target->getComponentOwner();

    for ( int i = 0; i < eComponentType_Count; ++i )
    {
        GComponentInterface* component = owner.getComponent ( ( eComponentType ) i );
        if ( component )
        {
            setComponentMenuState ( component->GetComponentName(), true, component->canDetach()  );
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
