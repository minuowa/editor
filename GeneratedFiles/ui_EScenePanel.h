/********************************************************************************
** Form generated from reading UI file 'EScenePanel.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ESCENEPANEL_H
#define UI_ESCENEPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EScenePanel
{
public:

    void setupUi(QWidget *EScenePanel)
    {
        if (EScenePanel->objectName().isEmpty())
            EScenePanel->setObjectName(QStringLiteral("EScenePanel"));
        EScenePanel->resize(400, 300);

        retranslateUi(EScenePanel);

        QMetaObject::connectSlotsByName(EScenePanel);
    } // setupUi

    void retranslateUi(QWidget *EScenePanel)
    {
        EScenePanel->setWindowTitle(QApplication::translate("EScenePanel", "EScenePanel", 0));
    } // retranslateUi

};

namespace Ui {
    class EScenePanel: public Ui_EScenePanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ESCENEPANEL_H
