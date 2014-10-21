#ifndef PROPERTYSHEET_H
#define PROPERTYSHEET_H

#include "GObject.h"
#include "qwidget.h"

class QFrame;
class QTreeView;
class QWidget;
class TreeModel;
class EPropertySheetDelegate;
class QStandardItemModel;
class QStandardItem;
class GObject;
class QStandardItem;
class  EPropertySheet: public QWidget
{
	Q_OBJECT
public:
    EPropertySheet ( QWidget* parent = 0 );
    ~EPropertySheet();

	void update ( GObject* obj,bool changeHeader=true);
	void clearPropertyies();
    void addProperty ( const char* categoryName, const char* propName,EPropertyVar* propVar );
    void show();
	void setHeader(const char* first,const char* second);
protected:
	void clearData();
	QStandardItem* getCategory ( const char* name );
private:
    QTreeView* mTreeView;
    QStandardItemModel* mTreeModel;
    EPropertySheetDelegate*	mDelegate;
public:
	inline QTreeView* getView() const
	{
		return mTreeView;
	}
};

#endif // PROPERTYSHEET_H
