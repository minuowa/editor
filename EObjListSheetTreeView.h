#pragma once
#include "qtreeview.h"
#include "Game.h"
class QWidget;
class QMenu;
class EObjListSheetTreeView :
    public QTreeView
{
	Q_OBJECT
public:
    EObjListSheetTreeView ( QWidget *parent = 0 );
    ~EObjListSheetTreeView ( void );
	void initComponentMenu ( const CharStringArr& componentTypeArr );
	void updateMenus();
	void setComponentMenuState ( const char* componentType, bool checked, bool enabled );
	void resetComponentMenuState();
protected:
    virtual void mouseReleaseEvent ( QMouseEvent *event );
    bool event ( QEvent *event );
	QMenu* mComponentMenu;

	public slots:
    void deleteObj();
	void onComponentAction ( QAction* );

};

