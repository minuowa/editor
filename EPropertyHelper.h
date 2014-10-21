#pragma once
#include "qspinbox.h"
#include "qcheckbox.h"
#include "qlineedit.h"
#include <string>
namespace EPropertyHelper
{
    bool WriteProperty ( void*& data,QSpinBox* editor );
    bool WriteProperty ( void*& data,QLineEdit* editor );
    bool WriteProperty ( void*& data,QCheckBox* editor );

    template<typename T>
    bool WriteProperty ( void*& data,QDoubleSpinBox* editor )
    {
        * ( ( T* ) data ) =editor->value();
        return true;
    }
};

