#ifndef EDITORAPP_H
#define EDITORAPP_H

#include <QApplication>
#include "EEditorSheetManager.h"
#include "..\FiGameDemo\FiGameDemo.h"

extern "C"
{
	typedef int ( *Game_Init ) ( HWND , EEditorManager* );
	typedef void ( *Game_Update ) ();
	typedef void ( *Game_ShutDown ) ();
};


class EditorApp : public QApplication
{
    Q_OBJECT

public:
    EditorApp ( int &argc, char **argv, int = ApplicationFlags );
    ~EditorApp();
    void SetSheetManager ( EEditorManager* mgr );
    bool filterEvent ( void *message, long *result );

    virtual bool winEventFilter ( MSG *message, long *result );
private:
    Game_Update mBackUpdate;
    Game_ShutDown mBackShutDown;
    EEditorManager* mSheetManager;

public:
    void SetUpdateBack ( Game_Update update )
    {
        mBackUpdate = update;
    }
    void SetShutDownBack ( Game_ShutDown shutdown )
    {
        mBackShutDown = shutdown;
    }
    void RenderGame()
    {
        if ( mBackUpdate )
        {
            mBackUpdate();
        }
    }
    EEditorManager* GetSheetManager() const
    {
        return mSheetManager;
    }
};

#endif // EDITORAPP_H
