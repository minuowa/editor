#ifndef EDITORAPP_H
#define EDITORAPP_H

#include <QApplication>
#include "EEditorManager.h"

extern "C"
{
	typedef int ( *Game_Init ) ( HWND );
	typedef bool ( *Game_Update ) ();
	typedef void ( *Game_ShutDown ) ();
};


class EditorApp : public QApplication
{
    Q_OBJECT

public:
	static EEditorManager Editor;
    EditorApp ( int &argc, char **argv, int = ApplicationFlags );
    ~EditorApp();
	bool updateGame();
private:
};

#endif // EDITORAPP_H
