#include "editor.h"
#include <QtGui/QApplication>
#include "../src/gui/widgets/qpushbutton.h"
#include "../src/corelib/codecs/qtextcodec_p.h"
#include "QDockWidget.h"
#include "Editorapp.h"
#include "EEditorSheetManager.h"
#include "QTreeView.h"
#include "gui/widgets/qmenubar.h"
#include "XSingleton.h"
void InitCodeSetting();
int main ( int argc, char *argv[] )
{
    EditorApp* app = new EditorApp ( argc, argv );

    InitCodeSetting();

    Editor* editor=new Editor();

    app->SetSheetManager ( SheetMgr );
    CXASSERT_RETURN_FALSE ( SheetMgr->Init ( editor ) );
    SheetMgr->GetObjectListView()->setParent ( editor->GetObjectListPanel() );
    editor->GetObjectEditPanel()->setWidget ( ( reinterpret_cast<QWidget*> ( SheetMgr->GetPropertyView() ) ) );
    editor->GetObjectListPanel()->setWidget ( ( reinterpret_cast<QWidget*> ( SheetMgr->GetObjectListView() ) ) );
    editor->show();

	FiGameDemo_Init( editor->GetScenePanel()->winId(), SheetMgr );
	app->SetUpdateBack ( FiGameDemo_Update );
	app->SetShutDownBack ( FiGameDemo_ShutDown );

	app->exec();

	delete editor;
	editor=0;
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

void InitCodeSetting()
{
    QTextCodec *codec = QTextCodec::codecForName ( "UTF-8" );

    QTextCodec::setCodecForTr ( codec );
    QTextCodec::setCodecForLocale ( QTextCodec::codecForLocale() );
    QTextCodec::setCodecForCStrings ( QTextCodec::codecForLocale() );
}
