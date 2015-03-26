#include "stdafx.h"
#include "editor.h"
#include "QMenu.h"
#include "QMenubar.h"
#include "qdockwidget.h"
#include "Editorapp.h"
#include "qfiledialog.h"
#include "EObjectListSheet.h"
#include "EEditorManager.h"
#include "ui_mainwindow.h"
#include "qevent.h"
#include "EScenePanel.h"
#include "GGame.h"
#include "qshortcut.h"
static const int gMinWidth=250;
Editor::Editor ( QWidget *parent, Qt::WindowType flags )
    : QMainWindow ( parent, flags )
    , mIdleTimeID ( 0 )
    , ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );
    setAcceptDrops ( true );
    //-------------------------------------------------------------------------
    // file
    //-------------------------------------------------------------------------

    fileMenu = menuBar()->addMenu ( tr ( "&File" ) );
    fileMenu->addAction ( tr ( "&Open..." ), this, SLOT ( openFile() ),
                          QKeySequence::Open );

    fileMenu->addAction ( tr ( "&Save..." ), this, SLOT ( saveFile() ),
                          QKeySequence::Save );
    //-------------------------------------------------------------------------
    //view
    //-------------------------------------------------------------------------
    mAssistMenu = menuBar()->addMenu ( tr ( "&Assist" ) );
    mAssistMenu->addAction ( tr ( "&ChangeToNextCamera(F3)" ), this, SLOT ( changeToNextCamera() ) );
    QShortcut* shortcut = new QShortcut ( QKeySequence ( Qt::Key_F3 ), this );
    connect ( shortcut, SIGNAL ( activated() ), this, SLOT ( changeToNextCamera() ) );

    mAssistMenu->addAction ( tr ( "&MoveToNextCamera(F4)" ), this, SLOT ( moveToNextCamera() ) );
    shortcut = new QShortcut ( QKeySequence ( Qt::Key_F4 ), this );
    connect ( shortcut, SIGNAL ( activated() ), this, SLOT ( moveToNextCamera() ) );

    viewMenu = menuBar()->addMenu ( tr ( "&View" ) );

    mScenePanel = new EScenePanel ( this );
    this->setCentralWidget ( mScenePanel );

    mObjectPropertyPanel = new QDockWidget ( tr ( "ObjectProperty" ), this );
    mObjectPropertyPanel->setAllowedAreas ( Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea );
    mObjectPropertyPanel->setMinimumWidth ( gMinWidth );
    mObjectPropertyPanel->setMinimumHeight ( 200 );
    viewMenu->addAction ( mObjectPropertyPanel->toggleViewAction() );
    addDockWidget ( Qt::RightDockWidgetArea, mObjectPropertyPanel );

    mObjectListPanel = new QDockWidget ( tr ( "ObjectList" ), this );
    mObjectListPanel->setAllowedAreas ( Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea );
    mObjectListPanel->setMinimumWidth ( 300 );
    mObjectListPanel->setMinimumHeight ( 200 );
    viewMenu->addAction ( mObjectListPanel->toggleViewAction() );
    addDockWidget ( Qt::LeftDockWidgetArea, mObjectListPanel );

    mOptionPanel = new QDockWidget ( tr ( "Option" ), this );
    mOptionPanel->setAllowedAreas ( Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea );
    mOptionPanel->setMinimumWidth ( gMinWidth );
    mOptionPanel->setMinimumHeight ( 200 );
    viewMenu->addAction ( mOptionPanel->toggleViewAction() );
    addDockWidget ( Qt::LeftDockWidgetArea, mOptionPanel );

    mFilmPanel = new QDockWidget ( tr ( "Film" ), this );
    mFilmPanel->setAllowedAreas ( Qt::AllDockWidgetAreas );
    mFilmPanel->setMinimumWidth ( gMinWidth );
    mFilmPanel->setMinimumHeight ( 400 );
    viewMenu->addAction ( mFilmPanel->toggleViewAction() );
    addDockWidget ( Qt::RightDockWidgetArea, mFilmPanel );

    mIdleTimeID = startTimer ( 0 );

    createPopupMenu();
}

Editor::~Editor()
{
    dSafeDelete ( ui );
}


void Editor::timerEvent ( QTimerEvent * timeevent )
{
    if ( timeevent->timerId() == mIdleTimeID )
    {
        EditorApp* app = ( EditorApp* ) qApp;
        if ( !app->updateGame() )
        {
            close();
        }
    }
    else
    {
        __super::timerEvent ( timeevent );
    }
}

void Editor::openFile()
{
    QString filePath = QFileDialog::getOpenFileName ( this, tr ( "Open File" ),
                       mcurSceneFile, tr ( "XML files (*.xml);;" ) );

    if ( !filePath.isEmpty() )
    {
        mcurSceneFile = filePath;
         Content::Scene.loadScene ( mcurSceneFile.toStdString().c_str() );
    }
}


bool Editor::winEvent ( MSG *message, long *result )
{
    //return __super::winEvent ( message, result );
    return true;
}

void Editor::setFocus ( Qt::FocusReason reason )
{
    __super::setFocus ( reason );
}

void Editor::mouseMoveEvent ( QMouseEvent * mouseEvent )
{
    __super::mouseMoveEvent ( mouseEvent );
}

bool Editor::event ( QEvent* event )
{
    switch ( event->type() )
    {
    case  QEvent::WindowActivate:
    {
         Content::Game.active ( true );
    }
    break;
    case QEvent::WindowDeactivate :
    {
         Content::Game.active ( false );
    }
    break;
    default:
        break;
    }
    return __super::event ( event );
}

void Editor::saveFile()
{
    QString filePath = QFileDialog::getOpenFileName ( this, tr ( "Save File" ),
                       mcurSceneFile, tr ( "XML files (*.xml);;" ) );

    if ( !filePath.isEmpty() )
    {
        mcurSceneFile = filePath;
         Content::Scene.saveScene ( mcurSceneFile.toStdString().c_str() );
    }
}

void Editor::changeToNextCamera()
{
     Content::Scene.changeToNextCamera();
}

void Editor::moveToNextCamera()
{
     Content::Scene.moveToNextCamera();
}



