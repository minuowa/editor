#include "stdafx.h"
#include "Editorapp.h"
#include <windows.h>
#include "EPropertySheet.h"

EditorApp::EditorApp ( int &argc, char **argv, int flag )
    : QApplication ( argc, argv, flag )
    , mBackUpdate ( 0 )
    , mBackShutDown ( 0 )
{
}

EditorApp::~EditorApp()
{
    if ( mBackShutDown )
        mBackShutDown();
}

