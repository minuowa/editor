#include "stdafx.h"
#include "EPropertySheet.h"
#include "qstandarditemmodel.h"
#include "EPropertySheetDelegate.h"
#include <assert.h>
#include "EPropertySheetTreeItem.h"
#include "EPropertytreeview.h"
#include "GObject.h"
#include "qtablewidget.h"

void toQVariant ( CXProp* prop, QVariant& var )
{
    switch ( prop->getType() )
    {
    case eType_Bool:
    {
        var = * ( ( bool* ) ( ( CXPropEntity<bool>* ) prop )->mVar );
    }
    break;
    case eType_Int:
    {
        var = * ( ( int* ) ( ( CXPropEntity<int>* ) prop )->mVar );
    }
    break;
	case eType_UInt:
	{
		var = * ( ( unsigned int* ) ( ( CXPropEntity<unsigned int>* ) prop )->mVar );
	}
	break;
    case eType_Float:
    {
        var = * ( ( float* ) ( ( CXPropEntity<float>* ) prop )->mVar );
    }
    break;
    case eType_String:
    {
        var = ( ( GString* ) ( ( CXPropEntity<GString>* ) prop )->mVar )->c_str();
    }
    break;
    case eType_Enum:
    {
        CXPropEnum* pEnum = ( CXPropEnum* ) prop;
        var = pEnum->getTheName();
    }
    break;
    default:
        break;
    }
}

EPropertySheet::~EPropertySheet()
{
    clearData();
    dSafeDelete ( mDelegate );
    dSafeDelete ( mTreeModel );
}

EPropertySheet::EPropertySheet ( QWidget* parent/*=0*/ )
    : QWidget ( parent )
    , mTreeView ( 0 )
    , mTreeModel ( 0 )
{
    mTreeView = new EPropertyTreeView ( parent );
    mTreeModel = new QStandardItemModel();
    mTreeView->setModel ( mTreeModel );
    //mTreeView->setGeometry(parent->childrenRect());
    mTreeView->setWindowTitle ( "Simple Tree Model" );


    mDelegate = new EPropertySheetDelegate;
    mTreeView->setItemDelegate ( mDelegate );
    mTreeView->setBaseSize ( 350, 300 );
    QSizePolicy sizePolicy ( QSizePolicy::Expanding, QSizePolicy::Expanding );
    mTreeView->setSizePolicy ( sizePolicy );
    mTreeView->setAcceptDrops ( true );
    mTreeView->setColumnWidth ( 0, 150 );
}

void EPropertySheet::show()
{
    mTreeView->show();
}

void EPropertySheet::update ( GObject* obj, bool changeHeader/*=true*/ )
{
    CXASSERT_RETURN ( obj );

    obj->registerAll();

    clearPropertyies();

    if ( changeHeader )
    {
        setHeader ( "Object", obj->categoryName() );
    }
    const CategoryPropertyMap& propMap = obj->getPropertyMap();

for ( auto pMap: propMap )
    {
        PropertyMap* propMap = pMap.second;
for ( auto walk: *propMap )
        {
            addProperty ( pMap.first.c_str(), walk.first.c_str(), walk.second );
        }
    }
}

QStandardItem* EPropertySheet::getCategory ( const char* name )
{
    int row = mTreeModel->rowCount();
    QStandardItem* item = 0;
    for ( int i = 0; i < row; ++i )
    {
        QStandardItem* child = mTreeModel->item ( i, 0 );
        if ( child )
        {
            if ( child->text() == name )
            {
                item = child;
                return item;
            }
        }
    }
    return item;
}

void EPropertySheet::clearPropertyies()
{
    clearData();
    mTreeModel->setColumnCount ( 2 );
    mTreeView->setColumnWidth ( 0, 160 );
}

void EPropertySheet::addProperty ( const char* categoryName, const char* propName, EPropertyVar* propVar )
{
    QStandardItem* categoryItem = getCategory ( categoryName );
    int curRow = 0;
    if ( !categoryItem )
    {
        curRow = mTreeModel->rowCount();
        mTreeModel->setRowCount ( curRow + 1 );
        categoryItem = new QStandardItem ( categoryName );
        mTreeModel->setItem ( curRow, 0, categoryItem );
        categoryItem->setEditable ( false );
        mTreeView->expand ( categoryItem->index() );
    }

    QList<QStandardItem*> lists;
    EPropertySheetTreeItem* item  = new EPropertySheetTreeItem ( propName );
    item->setBackground ( QBrush ( Qt::lightGray ) );
    item->setEditable ( false );
    lists.push_back ( item );

    item  = new EPropertySheetTreeItem();
    item->SetExtraData ( propVar );
    QVariant var;
    toQVariant ( propVar->mProp, var );
    item->setData ( var, Qt::EditRole );
	//item->setWhatsThis("WhatsThis");
	//item->setStatusTip("StatusTip");
	item->setToolTip("ToolTip");
    //item->setData ( Qt::EditRole ,var);
    lists.push_back ( item );

    categoryItem->appendRow ( lists );
}

void EPropertySheet::clearData()
{
    int row = mTreeModel->rowCount();
    int col = mTreeModel->columnCount();
    for ( int i = 0; i < row; ++i )
    {
        for ( int j = 0; j < col; ++j )
        {
            QStandardItem* child = mTreeModel->item ( i, j );
            dSafeDelete ( child );
        }
    }
    mTreeModel->clear();
}

void EPropertySheet::setHeader ( const char* first, const char* second )
{
    mTreeModel->setHeaderData ( 0, Qt::Horizontal, first, Qt::DisplayRole );
    mTreeModel->setHeaderData ( 1, Qt::Horizontal, second, Qt::DisplayRole );
}


