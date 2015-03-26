#include "stdafx.h"
#include "Editorapp.h"
#include <windows.h>
#include "EPropertySheet.h"

EditorApp::EditorApp ( int &argc, char **argv, int flag )
    : QApplication ( argc, argv, flag )
{
}

EditorApp::~EditorApp()
{
    Content::Game.shutDown();
}

bool EditorApp::updateGame()
{
	return Content::Game.loop();
}

EEditorManager EditorApp::Editor;

