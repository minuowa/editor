#ifndef EDITORAPP_H
#define EDITORAPP_H

#include <QApplication>
#include "EEditorManager.h"
#include "FiGameDemo.h"

extern "C"
{
	typedef int ( *Game_Init ) ( HWND );
	typedef void ( *Game_Update ) ();
	typedef void ( *Game_ShutDown ) ();
};


class EditorApp : public QApplication
{
    Q_OBJECT

public:
    EditorApp ( int &argc, char **argv, int = ApplicationFlags );
    ~EditorApp();
private:
    Game_Update mBackUpdate;
    Game_ShutDown mBackShutDown;

public:
    void setGameUpdate ( Game_Update update )
    {
        mBackUpdate = update;
    }
    void setGameShutDown ( Game_ShutDown shutdown )
    {
        mBackShutDown = shutdown;
    }
    void updateGame()
    {
        if ( mBackUpdate )
        {
            mBackUpdate();
        }
    }
};

#endif // EDITORAPP_H
