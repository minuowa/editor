#include "stdafx.h"
#include <vld.h>
#include "editor.h"
//#include <QtGui/QApplication>
//#include "gui/widgets/qpushbutton.h"
#include "QDockWidget.h"
#include "Editorapp.h"
#include "EEditorManager.h"
#include "QTreeView.h"
//#include "gui/widgets/qmenubar.h"
#include "XSingleton.h"
#include "qtextcodec.h"
void initCodeSetting();
#ifndef _DEBUG
#include < QtPlugin >
//Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
#endif
int main ( int argc, char *argv[] )
{
    EditorApp* app = new EditorApp ( argc, argv );

    initCodeSetting();

    Editor* editor = new Editor();
    HWND sceneWindowHandle = ( HWND ) editor->getScenePanel()->winId();
    Content::Game.init ( sceneWindowHandle );

    CXASSERT_RETURN_FALSE ( EditorApp::Editor.init ( editor ) );

    editor->show();
    app->exec();

    delete editor;
    editor = 0;
    delete app;
    app = 0;


    //FiGameDemo(w.GetScenePanel()->winId(),psheet);

    //HMODULE dll = LoadLibraryA ( "FiGameDemo.dll" );
    //if ( dll )
    //{
    //    Game_Init game = ( Game_Init ) GetProcAddress ( dll, "FiGameDemo_Init" );
    //    if ( game )
    //    {
    //        if ( !game ( w.GetScenePanel()->winId(), SheetMgr ) )
    //        {
    //            Q_ASSERT ( 0 );
    //            return 0;
    //        }
    //    }
    //    Game_Update gameUpdate = ( Game_Update ) GetProcAddress ( dll, "FiGameDemo_Update" );
    //    Game_ShutDown gameShutDown = ( Game_ShutDown ) GetProcAddress ( dll, "FiGameDemo_ShutDown" );
    //    app->SetUpdateBack ( gameUpdate );
    //    app->SetShutDownBack ( gameShutDown );
    //}

    //app->exec();

    //delete app;
    //app = 0;

    //if ( dll )
    //{
    //    FreeLibrary ( dll );
    //}
    return 0;
}

void initCodeSetting()
{
    QTextCodec *codec = QTextCodec::codecForName ( "UTF-8" );

    QTextCodec::setCodecForLocale ( codec );
    QTextCodec::setCodecForLocale ( QTextCodec::codecForLocale() );
    //QTextCodec::setCodecForCStrings ( QTextCodec::codecForLocale() );
}
