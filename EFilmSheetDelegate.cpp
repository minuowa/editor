#include "stdafx.h"
#include "EFilmSheetDelegate.h"
#include "qlineedit.h"
EFilmSheetDelegate::EFilmSheetDelegate ( QObject *parent )
    : QItemDelegate ( parent )
{

}

EFilmSheetDelegate::~EFilmSheetDelegate()
{

}

void EFilmSheetDelegate::setEditorData ( QWidget *editor, const QModelIndex &index ) const
{
    QLineEdit* lineEdit = ( QLineEdit* ) editor;
    QStandardItemModel* standModel = ( QStandardItemModel* ) index.model();
    QVariant var = standModel->data ( index );
    assert ( var.type() == QVariant::String );
    lineEdit->setText ( var.toString() );
}

void EFilmSheetDelegate::setModelData ( QWidget *editor, QAbstractItemModel *model, const QModelIndex &index ) const
{
    QLineEdit* lineEdit = ( QLineEdit* ) editor;
    QStandardItemModel* standModel = ( QStandardItemModel* ) model;
    QVariant var = standModel->data ( index );
    assert ( var.type() == QVariant::String );
    if ( lineEdit->text().isEmpty() )
    {
        lineEdit->setText ( var.toString() );
        return;
    }
    if ( nullptr != FilmPlayer->getFrame ( lineEdit->text().toStdString().c_str() ) )
    {
        return;
    }
    else
    {
        FilmPlayer->renameFrame ( var.toString().toStdString().c_str()
                                  , lineEdit->text().toStdString().c_str() );
        standModel->setData ( index, QVariant ( lineEdit->text() ) );
    }

}

QWidget * EFilmSheetDelegate::createEditor ( QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    QLineEdit *editor = new QLineEdit ( parent );
    return editor;
}
