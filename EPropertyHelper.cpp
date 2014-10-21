#include "stdafx.h"
#include "EPropertyHelper.h"
#include "Game.h"

bool EPropertyHelper::WriteProperty ( void*& data,QSpinBox* editor )
{
    * ( ( int* ) data ) =editor->value();
    return true;
}

//bool EPropertyHelper::WriteProperty( void*& data,QDoubleSpinBox* editor )
//{
//	*((double*)data)=editor->value();
//	return true;
//}

bool EPropertyHelper::WriteProperty ( void*& data,QLineEdit* editor )
{
    GString& str=* ( ( GString* ) data );
    str=editor->text().toStdString();
    return true;
}

bool EPropertyHelper::WriteProperty ( void*& data,QCheckBox* editor )
{
    * ( ( bool* ) data ) =editor->checkState() ==Qt::Checked;
    return true;
}
