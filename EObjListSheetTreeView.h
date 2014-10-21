#pragma once
#include "qtreeview.h"
class QWidget;
class EObjListSheetTreeView :
    public QTreeView
{
public:
    EObjListSheetTreeView ( QWidget *parent = 0);
    ~EObjListSheetTreeView ( void );
	void setPopupMenu(QMenu* menu);
protected:
    virtual void mouseReleaseEvent ( QMouseEvent *event );
	bool event(QEvent *event);

protected:
    QMenu* mPopupMenu;
};

