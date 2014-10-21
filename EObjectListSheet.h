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
class  EObjectListSheet: public QObject, public CXCallBack
{
	Q_OBJECT
public:
    EObjectListSheet (QWidget *parent=0 );
    ~EObjectListSheet();
	inline QTreeView* getView() const;
public:
	void clearTreeItem();
    void show();

	void updateAll();
	void addChildByType(const char* typeName);
	void alterItemName(const char* oldName,const char* targetName);
protected:
    void updateItemByAddObj ( const char* name, const char* parentName = 0 );
	void addChild(GNode* node,QStandardItem* item);
	QStandardItem* getItem ( const char* name );
	void onSelect ( const QModelIndex& index );

	virtual void onCallBack(const CXDelegate& delgate);
public slots:
    void onSelectionChanged ( const QItemSelection &selected, const QItemSelection &deselected );
private:
    QTreeView* mTreeView;
    QStandardItemModel* mTreeModel;
    EPropertySheetDelegate*	mDelegate;
};

inline QTreeView* EObjectListSheet::getView() const
{
	return mTreeView;
}

