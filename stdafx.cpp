#include "stdafx.h"

void eFindItem ( QStandardItem* parent, const char* name, QStandardItem*& res )
{
	if ( !parent )
	{
		return;
	}
	if ( parent->hasChildren() )
	{
		int row = parent->rowCount();
		int col = parent->columnCount();

		for ( int i = 0; i < row; ++i )
		{
			for ( int j = 0; j < col; ++j )
			{
				QStandardItem* item = parent->child ( i, j );
				if ( item )
				{
					if ( item->text() == name )
					{
						res = item;
						return;
					}
					else
					{
						eFindItem ( item, name, res );
					}
				}
			}
		}
	}
}
