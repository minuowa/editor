#include "editor.h"
#include "QMenu.h"
#include "QMenubar.h"
#include "..\src\gui\widgets\qdockwidget.h"
#include "Editorapp.h"
#include "..\src\gui\dialogs\qfiledialog.h"
#include "EObjectListSheet.h"
#define MyApp ((EditorApp*)qApp)
#include "EEditorSheetManager.h"

Editor::Editor ( QWidget *parent, Qt::WFlags flags )
    : QMainWindow ( parent, flags )
    , mIdleTimeID ( 0 )
{
    ui.setupUi ( this );

    //-------------------------------------------------------------------------
    // file
    //-------------------------------------------------------------------------

    fileMenu = menuBar()->addMenu ( tr ( "&File" ) );
    fileMenu->addAction ( tr ( "&Open..." ), this, SLOT ( openFile() ),
                          QKeySequence::Open );

    //-------------------------------------------------------------------------
    // create object
    //-------------------------------------------------------------------------



    //-------------------------------------------------------------------------
    //view
    //-------------------------------------------------------------------------

    viewMenu = menuBar()->addMenu ( tr ( "&View" ) );

    mScenePanel = new QFrame ( this );
    setCentralWidget ( mScenePanel );

    mObjectPropertyPanel = new QDockWidget ( tr ( "ObjectProperty" ), this );
    mObjectPropertyPanel->setAllowedAreas ( Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea );
    viewMenu->addAction ( mObjectPropertyPanel->toggleViewAction() );
    addDockWidget ( Qt::RightDockWidgetArea, mObjectPropertyPanel );
    mObjectPropertyPanel->setMinimumWidth ( 200 );
    mObjectPropertyPanel->setMinimumHeight ( 200 );
    //mObjectPropertyPanel->hide();

    mObjectListPanel = new QDockWidget ( tr ( "ObjectList" ), this );
    mObjectListPanel->setAllowedAreas ( Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea );
    viewMenu->addAction ( mObjectListPanel->toggleViewAction() );
    addDockWidget ( Qt::LeftDockWidgetArea, mObjectListPanel );
    mObjectListPanel->setMinimumWidth ( 300 );
    mObjectListPanel->setMinimumHeight ( 200 );

    mIdleTimeID = startTimer ( 0 );

    createPopupMenu();
}

Editor::~Editor()
{

}


void Editor::timerEvent ( QTimerEvent * timeevent )
{
    if ( timeevent->timerId() == mIdleTimeID )
    {
        EditorApp* app = ( EditorApp* ) qApp;
        app->RenderGame();
    }
    else
    {
        __super::timerEvent ( timeevent );
    }
}

void Editor::openFile()
{
    QString filePath = QFileDialog::getOpenFileName ( this, tr ( "Open File" ),
                       curSceneFile, tr ( "XML files (*.xml);;HTML files (*.html);;"
                                          "SVG files (*.svg);;User Interface files (*.ui)" ) );

    if ( !filePath.isEmpty() )
    {
        curSceneFile = filePath;
    }
}



void Editor::createObj ( const char* string )
{

}


bool Editor::winEvent ( MSG *message, long *result )
{
    return __super::winEvent ( message, result );
}

void Editor::setFocus ( Qt::FocusReason reason )
{
    __super::setFocus ( reason );
}



