#include "stdafx.h"
#include "EFilmSheet.h"
#include "qmenubar.h"
#include "qpushbutton.h"
#include "qstyleoption.h"
#include "QToolButton.h"
#include "QRadioButton.h"
#include "ui_EFilmSheet.h"
#include "qstandarditemmodel.h"
#include "qevent.h"
#include "QMenu.h"
#include "qabstractitemmodel.h"
#include "EFilmSheetDelegate.h"
void updateItemBack ( QStandardItemModel* model );

EFilmSheet::EFilmSheet ( QWidget *parent )
    : QWidget ( parent )
    , ui ( new Ui::EFilmSheet )
{
    ui->setupUi ( this );

    mFrameList = ui->mFrameList;
    mFrameList->setModel ( new QStandardItemModel ( this ) );
    mFrameList->setItemDelegate ( new EFilmSheetDelegate );
    connect ( mFrameList, SIGNAL ( clicked ( const QModelIndex& ) ), this, SLOT ( onClicked ( const QModelIndex& ) ) );
    connect ( ui->mFileNew, SIGNAL ( released ( ) ), this, SLOT ( onFileNew() ) );
    connect ( ui->mFileOpen, SIGNAL ( released ( ) ), this, SLOT ( onFileOpen() ) );
    connect ( ui->mFileSave, SIGNAL ( released ( ) ), this, SLOT ( onFileSave() ) );

    connect ( ui->mCtrlPlay, SIGNAL ( released ( ) ), this, SLOT ( onPlay( ) ) );
    connect ( ui->mCtrlPause, SIGNAL ( released ( ) ), this, SLOT ( onPause() ) );
    connect ( ui->mCtrlStop, SIGNAL ( released ( ) ), this, SLOT ( onStop() ) );

    mPopMenu = new QMenu ( "Frames" , this );
    mPopMenu->addAction ( tr ( "Add" ), this, SLOT ( addFrame() ) );
    mPopMenu->addAction ( tr ( "Delete" ), this, SLOT ( deleteFrame() ) );
    mPopMenu->addAction ( tr ( "Play" ), this, SLOT ( playFrame() ) );

     Content::FilmPlayer.mDelegateAddFrame += this;
     Content::FilmPlayer.mDelegateDeleteFrame += this;
}

EFilmSheet::~EFilmSheet()
{
    dSafeDelete ( ui );
    QAbstractItemDelegate * d = mFrameList->itemDelegate();
    dSafeDelete ( d );
     Content::FilmPlayer.mDelegateAddFrame -= this;
     Content::FilmPlayer.mDelegateDeleteFrame -= this;
}

void EFilmSheet::onFileNew()
{

}

void EFilmSheet::onFileOpen()
{

}

void EFilmSheet::onFileSave()
{

}

void EFilmSheet::onPlay()
{
}

void EFilmSheet::onPause()
{

}

void EFilmSheet::onStop()
{

}
bool EFilmSheet::event ( QEvent* event )
{
    switch ( event->type() )
    {
    case QEvent::ContextMenu:
    {
        QContextMenuEvent* menuEvent = ( QContextMenuEvent* ) event;
        if ( ui->mFrameList->geometry().contains ( menuEvent->pos() ) )
        {
            mPopMenu->exec ( menuEvent->globalPos() );
        }
    }
    break;
    }
    return __super::event ( event );
}

void EFilmSheet::addFrame()
{
    GString prev;
    if ( mSelectedIndex.isValid() )
    {
        QVariant var = mFrameList->model()->data ( mSelectedIndex );
        assert ( var.type() == QVariant::String );
        prev = var.toString().toStdString().c_str();
    }
     Content::FilmPlayer.addFrameBehind ( prev );
}

void EFilmSheet::deleteFrame()
{
    QModelIndex index = mFrameList->currentIndex();
    QStandardItemModel* model = ( QStandardItemModel* ) mFrameList->model();
    if ( index.isValid() )
    {
        QVariant var = mFrameList->model()->data ( index );
        assert ( var.type() == QVariant::String );
         Content::FilmPlayer.deleteFrame ( var.toString().toStdString().c_str() );
        updateItemBack ( model );
    }
}

void EFilmSheet::playFrame()
{
    QModelIndex index = mFrameList->currentIndex();
    if ( index.isValid() )
    {
        QVariant var = mFrameList->model()->data ( index );
        assert ( var.type() == QVariant::String );
         Content::FilmPlayer.play ( var.toString().toStdString().c_str() );
    }
}
void updateItemBack ( QStandardItemModel* model )
{
    int rowCnt = model->rowCount();
    QBrush defaultBrush ( QColor ( 255, 255, 255 ) );
    for ( int i = 0; i < rowCnt; ++i )
    {
        QStandardItem* item = model->item ( i );
        if ( i % 2 == 0 )
        {
            QLinearGradient linearGrad ( QPointF ( 0, 0 ), QPointF ( 200, 200 ) );
            linearGrad.setColorAt ( 0, Qt::lightGray );
            linearGrad.setColorAt ( 1, Qt::white );
            QBrush brush ( linearGrad );
            item->setBackground ( brush );
        }
        else
        {
            item->setBackground ( defaultBrush );
        }
    }
}
void EFilmSheet::onCallBack ( const CXDelegate& d, CXEventArgs* arg )
{
    if ( d ==  Content::FilmPlayer.mDelegateAddFrame )
    {
        QStandardItemModel* model = ( QStandardItemModel* ) mFrameList->model();
        QStandardItem* itemBrother = nullptr;
        GFilmAddFrameEvent* args = ( GFilmAddFrameEvent* ) arg;
        QStandardItem *item = new QStandardItem ( args->mFrameName.c_str() );
        if ( !args->mPrevName.empty() )
        {
            QList<QStandardItem*> itemList = model->findItems ( args->mPrevName.c_str() );
            if ( itemList.size() )
                itemBrother = itemList[0];
            if ( itemBrother != nullptr )
            {
                int row = itemBrother->index().row() + 1;
                model->insertRow ( row, item );
                updateItemBack ( model );
            }
        }
        else
        {
            model->appendRow ( item );
            updateItemBack ( model );
        }
    }
    else if ( d ==  Content::FilmPlayer.mDelegateDeleteFrame )
    {
        GFilmDeleteFrameEvent* args = ( GFilmDeleteFrameEvent* ) arg;
        QStandardItemModel* model = ( QStandardItemModel* ) mFrameList->model();
        QList<QStandardItem*> itemList = model->findItems ( args->mFrameName.c_str() );
        QStandardItem* item = nullptr;
        if ( itemList.size() )
            item = itemList[0];
        if ( item != nullptr )
            model->removeRow ( item->row() );
    }
}



void EFilmSheet::onClicked ( const QModelIndex &index )
{
    mSelectedIndex = index;
}
