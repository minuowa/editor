#include "Editorapp.h"
#include <windows.h>
#include "EPropertySheet.h"

EditorApp::EditorApp ( int &argc, char **argv, int flag )
    : QApplication ( argc, argv, flag )
    , mBackUpdate ( 0 )
    , mBackShutDown ( 0 )
    , mSheetManager ( 0 )
{
}

EditorApp::~EditorApp()
{
    if ( mBackShutDown )
        mBackShutDown();
}

void EditorApp::SetSheetManager ( EEditorManager* mgr )
{
    mSheetManager = mgr;
}

bool EditorApp::filterEvent ( void *message, long *result )
{
    return __super::filterEvent ( message, result );
}

bool EditorApp::winEventFilter ( MSG *message, long *result )
{
    if ( mSheetManager )
        mSheetManager->ProcWindowEvent ( message );
    return __super::winEventFilter ( message, result );
}
