#include "stdafx.h"
#include "EPropertytreeview.h"
#include "qevent.h"
#include "qurl.h"
#include "Game.h"
#include "qmimedata.h"

EPropertyTreeView::EPropertyTreeView ( QWidget *parent )
    : QTreeView ( parent )
{
}

EPropertyTreeView::~EPropertyTreeView()
{

}
void EPropertyTreeView::dragEnterEvent ( QDragEnterEvent *event )
{
    event->acceptProposedAction();
    emit changed ( event->mimeData() );
}
//! [dragEnterEvent() function]

//! [dragMoveEvent() function]
void EPropertyTreeView::dragMoveEvent ( QDragMoveEvent *event )
{
    event->acceptProposedAction();
}
//! [dragMoveEvent() function]

//! [dropEvent() function part1]
void EPropertyTreeView::dropEvent ( QDropEvent *event )
{
    const QMimeData *mimeData = event->mimeData();
    //! [dropEvent() function part1]

    //! [dropEvent() function part2]
    if ( mimeData->hasImage() )
    {
    }
    else if ( mimeData->hasHtml() )
    {
    }
    else if ( mimeData->hasText() )
    {
    }
    else if ( mimeData->hasUrls() )
    {
        QList<QUrl> urlList = mimeData->urls();
        QString text;
        for ( int i = 0; i < urlList.size() && i < 32; ++i )
        {
            QString url = urlList.at ( i ).path();
            CXASSERT ( url.toStdString().c_str() );
            text += url + QString ( "\n" );
        }
        QModelIndex idx = indexAt ( event->pos() );
        if ( model() )
        {
            QVariant var = model()->data ( idx );
            if ( var.type() == QMetaType::QString )
            {
                text = text.right ( text.length() - 1 );
                CXFileName path ( text.toStdString().c_str() );
                GString relname;
                path.GetRelativeFileName ( relname );
                model()->setData ( idx, relname.c_str() );
            }
        }
    }
    else
    {
    }
    //! [dropEvent() function part2]

    //! [dropEvent() function part3]
    setBackgroundRole ( QPalette::Dark );
    event->acceptProposedAction();
}
//! [dropEvent() function part3]

//! [dragLeaveEvent() function]
void EPropertyTreeView::dragLeaveEvent ( QDragLeaveEvent *event )
{
    event->accept();
}