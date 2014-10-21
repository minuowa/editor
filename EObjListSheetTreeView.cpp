#include "stdafx.h"
#include "EObjListSheetTreeView.h"
#include "qwidget.h"
#include "QMenu.h"
#include "qevent.h"
#include "Game.h"


EObjListSheetTreeView::EObjListSheetTreeView ( QWidget *parent/* = 0*/ )
    : QTreeView ( parent )
    , mPopupMenu ( 0 )
{
    setContextMenuPolicy ( Qt::ActionsContextMenu );
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

void EObjListSheetTreeView::setPopupMenu ( QMenu* menu )
{
    mPopupMenu = menu;
}
bool EObjListSheetTreeView::event ( QEvent* event )
{
    switch ( event->type() )
    {
    case QEvent::ContextMenu:
    {
        QContextMenuEvent* menuEvent = ( QContextMenuEvent* ) event;
        CXASSERT ( mPopupMenu );
        mPopupMenu->exec ( menuEvent->globalPos() );
    }
    break;
    }
    return __super::event ( event );
}
