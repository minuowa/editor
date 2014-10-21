#include "stdafx.h"
#include "qlineedit.h"
#include "qcombobox.h"
/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

/*
    delegate.cpp

    A delegate that allows the user to change integer values from the model
    using a spin box widget.
*/


#include "EPropertySheetDelegate.h"
#include "EPropertySheetTreeItem.h"
#include "EPropertyHelper.h"
#include "GObject.h"
#include "EEditorManager.h"
#include "Game.h"
#include "QToolButton.h"
//! [0]
EPropertySheetDelegate::EPropertySheetDelegate ( QObject *parent )
    : QItemDelegate ( parent )
{
}
//! [0]

//! [1]
QWidget *EPropertySheetDelegate::createEditor ( QWidget *parent,
        const QStyleOptionViewItem & option ,
        const QModelIndex & index ) const
{
    QVariant var = index.model()->data ( index, Qt::EditRole );

    QStandardItemModel* mymode = ( QStandardItemModel* ) ( index.model() );
    EPropertySheetTreeItem* item = dynamic_cast<EPropertySheetTreeItem*> ( mymode->itemFromIndex ( index ) );
	EPropertyVar* propVar = ( EPropertyVar* ) item->mPtr;

    QWidget* widget = 0;
    switch ( var.type() )
    {
    case QMetaType::Int:
    {
        QSpinBox *editor = new QSpinBox ( parent );
        editor->setMaximum ( INT_MAX );
        editor->setMinimum ( INT_MIN );
        widget = editor;
    }
    break;
    case QMetaType::Bool:
    {
        QCheckBox *editor = new QCheckBox ( parent );
        editor->setCheckState ( var.toBool() ? Qt::Checked : Qt::Unchecked );
        widget = editor;
    }
    break;
    case QMetaType::QString:
    {
        QLineEdit *editor = new QLineEdit ( parent );
        widget = editor;
    }
    break;
    case QMetaType::Double:
    {
        QDoubleSpinBox *editor = new QDoubleSpinBox ( parent );
        editor->setMaximum ( DOUBLE_MAX );
        editor->setMinimum ( DOUBLE_MIN );
        widget = editor;
    }
    break;
    case QMetaType::Float:
    {
        QDoubleSpinBox *editor = new QDoubleSpinBox ( parent );
        editor->setMaximum ( DOUBLE_MAX );
        editor->setMinimum ( DOUBLE_MIN );
        widget = editor;
    }
    break;
    case QMetaType::QStringList:
    {
		QComboBox *editor = new QComboBox ( parent );
		editor->setFrame(true);
		editor->addItems ( var.toStringList() );
		int idx = 0;
		dCast ( idx, propVar->mPtr );
		editor->setCurrentIndex ( idx );
		widget = editor;
    }
    break;
    }

    return widget;
}
//! [1]

//! [2]
void EPropertySheetDelegate::setEditorData ( QWidget *editor,
        const QModelIndex &index ) const
{
    //int value = index.model()->data(index, Qt::EditRole).toInt();
    QVariant var = index.model()->data ( index, Qt::EditRole );

    switch ( var.type() )
    {
    case QMetaType::Int:
    {
        QSpinBox *curEditor = static_cast<QSpinBox*> ( editor );
        curEditor->setMinimum ( 0 );
        curEditor->setMaximum ( 100 );
        curEditor->setValue ( var.toInt() );
    }
    break;
    case QMetaType::Bool:
    {
        QCheckBox *curEditor = static_cast<QCheckBox*> ( editor );
        curEditor->setCheckState ( var.toBool() ? Qt::Checked : Qt::Unchecked );
    }
    break;
    case QMetaType::QString:
    {
        QLineEdit *curEditor = static_cast<QLineEdit*> ( editor );
        curEditor->setText ( var.toString() );
    }
    break;
    case QMetaType::Double:
    {
        QDoubleSpinBox *curEditor = static_cast<QDoubleSpinBox*> ( editor );
        curEditor->setValue ( var.toFloat() );
    }
    break;
    case QMetaType::Float:
    {
        QDoubleSpinBox *curEditor = static_cast<QDoubleSpinBox*> ( editor );
        curEditor->setValue ( var.toFloat() );
    }
    break;
    case QMetaType::QStringList:
    {
		//QToolButton *curEditor = static_cast<QComboBox*> ( editor );
        //curEditor->clear();
        //curEditor->addItems ( var.toStringList() );
        //curEditor->setCurrentText() ( var.toStringList() );
    }
    break;
    }

    //QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
    //spinBox->setValue(value);
}
//! [2]

//! [3]
void EPropertySheetDelegate::setModelData ( QWidget *editor, QAbstractItemModel *model,
        const QModelIndex &index ) const
{
    QVariant var = index.model()->data ( index, Qt::EditRole );

    QStandardItemModel* mymode = static_cast<QStandardItemModel*> ( model );
    EPropertySheetTreeItem* item = dynamic_cast<EPropertySheetTreeItem*> ( mymode->itemFromIndex ( index ) );

    EPropertyVar* propVar = ( EPropertyVar* ) item->mPtr;
    CXASSERT ( propVar );
    switch ( var.type() )
    {
    case QMetaType::Int:
    {
        QSpinBox *curEditor = static_cast<QSpinBox*> ( editor );
        int prop = curEditor->value();
        model->setData ( index, prop, Qt::EditRole );
        EditorMgr->notifyPropertyChange ( propVar->mPtr, &prop );
        dCast ( propVar->mPtr, prop );
        EditorMgr->notifyPropertyChangeEnd ( propVar->mPtr );
    }
    break;
    case QMetaType::Bool:
    {
        QCheckBox *curEditor = static_cast<QCheckBox*> ( editor );
        bool prop = curEditor->checkState() == Qt::Checked ? true : false;
        model->setData ( index, prop, Qt::EditRole );
        EditorMgr->notifyPropertyChange ( propVar->mPtr, &prop );
        dCast ( propVar->mPtr, prop );
        EditorMgr->notifyPropertyChangeEnd ( propVar->mPtr );
    }
    break;
    case QMetaType::QString:
    {
        QLineEdit *curEditor = static_cast<QLineEdit*> ( editor );
        GString prop = curEditor->text().toStdString();
        model->setData ( index, prop.c_str(), Qt::EditRole );
        EditorMgr->notifyPropertyChange ( propVar->mPtr, &prop );
        dCast ( propVar->mPtr, prop );
        EditorMgr->notifyPropertyChangeEnd ( propVar->mPtr );
    }
    break;
    case QMetaType::Double:
    {
        QDoubleSpinBox *curEditor = static_cast<QDoubleSpinBox*> ( editor );
        double prop = ( double ) curEditor->value();
        model->setData ( index, prop, Qt::EditRole );
        EditorMgr->notifyPropertyChange ( propVar->mPtr, &prop );
        dCast ( propVar->mPtr, prop );
        EditorMgr->notifyPropertyChangeEnd ( propVar->mPtr );
    }
    break;
    case QMetaType::Float:
    {
        QDoubleSpinBox *curEditor = static_cast<QDoubleSpinBox*> ( editor );
        float prop = ( float ) curEditor->value();
        model->setData ( index, prop, Qt::EditRole );
        EditorMgr->notifyPropertyChange ( propVar->mPtr, &prop );
        dCast ( propVar->mPtr, prop );
        EditorMgr->notifyPropertyChangeEnd ( propVar->mPtr );
    }
    break;
    case QMetaType::QStringList:
    {
		QComboBox *curEditor = static_cast<QComboBox*> ( editor );
        int prop =  curEditor->currentIndex();
        EditorMgr->notifyPropertyChange ( propVar->mPtr, &prop );
        dCast ( propVar->mPtr, prop );
        EditorMgr->notifyPropertyChangeEnd ( propVar->mPtr );
    }
    break;
    }
}
//! [3]

//! [4]
void EPropertySheetDelegate::updateEditorGeometry ( QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex & index ) const
{
    QVariant var = index.model()->data ( index, Qt::EditRole );
    switch ( var.type() )
    {
    case QMetaType::Bool:
    {
        QCheckBox *curEditor = static_cast<QCheckBox*> ( editor );
        QRect rc;
        rc.setRight ( option.rect.right() - 1 );
        rc.setLeft ( rc.right() - curEditor->rect().width() );
        rc.setTop ( option.rect.top() + 1 );
        rc.setBottom ( option.rect.bottom() - 1 );
        curEditor->setGeometry ( rc );
    }
    break;
    default:
    {
        editor->setGeometry ( option.rect );
    }
    break;
    }
}
//! [4]
