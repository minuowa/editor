#pragma once
#include "qobject.h"
#include "XDelegate.h"
class QFrame;
class QTreeView;
class QWidget;
class TreeModel;
class EPropertySheetDelegate;
class QStandardItemModel;
class QStandardItem;
class QMenu;
class QModelIndex;
class QItemSelection;
class GNode;
class EObjListSheetTreeView;
class  EObjectListSheet: public QObject, public CXCallBack
{
	Q_OBJECT
public:
    EObjectListSheet (QWidget *parent=0 );
    ~EObjectListSheet();
	inline EObjListSheetTreeView* getView() const;
public:
	void clearTreeItem();
    void show();

	void updateAll();
	void addChildByType(const char* typeName);
	void alterItemName(const char* oldName,const char* targetName);
protected:
	void updateItemByAddObj ( const char* name, const char* parentName = 0 );
	void updateItemByDeleteObj ( const char* name);
	void addChild(GNode* node,QStandardItem* item);
	QStandardItem* getItem ( const char* name );
	static void deleteItem ( QStandardItem* parent, const char* name);

	bool getItemPosition(int& row,int& col,const char* text);
	void onSelect ( const QModelIndex& index );

	virtual void onCallBack ( const CXDelegate& , CXEventArgs*  )override;
	public slots:
    void onSelectionChanged ( const QItemSelection &selected, const QItemSelection &deselected );
private:
    QTreeView* mTreeView;
    QStandardItemModel* mTreeModel;
    EPropertySheetDelegate*	mDelegate;
};

inline EObjListSheetTreeView* EObjectListSheet::getView() const
{
	return (EObjListSheetTreeView*)mTreeView;
}

