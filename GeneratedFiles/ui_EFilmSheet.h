/********************************************************************************
** Form generated from reading UI file 'EFilmSheet.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EFILMSHEET_H
#define UI_EFILMSHEET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EFilmSheet
{
public:
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *gp1;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QRadioButton *mModePlay;
    QRadioButton *mModeRecord;
    QGroupBox *horizontalGroupBox_2;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *mCtrlPlay;
    QPushButton *mCtrlPause;
    QPushButton *mCtrlStop;
    QGroupBox *horizontalGroupBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *mFileNew;
    QPushButton *mFileOpen;
    QPushButton *mFileSave;
    QLabel *mFileName;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QListView *mFrameList;

    void setupUi(QWidget *EFilmSheet)
    {
        if (EFilmSheet->objectName().isEmpty())
            EFilmSheet->setObjectName(QStringLiteral("EFilmSheet"));
        EFilmSheet->resize(279, 570);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(EFilmSheet->sizePolicy().hasHeightForWidth());
        EFilmSheet->setSizePolicy(sizePolicy);
        EFilmSheet->setAutoFillBackground(true);
        horizontalLayout_5 = new QHBoxLayout(EFilmSheet);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        gp1 = new QGroupBox(EFilmSheet);
        gp1->setObjectName(QStringLiteral("gp1"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(gp1->sizePolicy().hasHeightForWidth());
        gp1->setSizePolicy(sizePolicy1);
        horizontalLayout_6 = new QHBoxLayout(gp1);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(gp1);
        label->setObjectName(QStringLiteral("label"));
        label->setBaseSize(QSize(30, 0));

        horizontalLayout->addWidget(label);

        mModePlay = new QRadioButton(gp1);
        mModePlay->setObjectName(QStringLiteral("mModePlay"));
        mModePlay->setEnabled(true);
        mModePlay->setChecked(true);

        horizontalLayout->addWidget(mModePlay);

        mModeRecord = new QRadioButton(gp1);
        mModeRecord->setObjectName(QStringLiteral("mModeRecord"));
        mModeRecord->setMaximumSize(QSize(16777215, 16));

        horizontalLayout->addWidget(mModeRecord);


        horizontalLayout_6->addLayout(horizontalLayout);


        verticalLayout_4->addWidget(gp1);

        horizontalGroupBox_2 = new QGroupBox(EFilmSheet);
        horizontalGroupBox_2->setObjectName(QStringLiteral("horizontalGroupBox_2"));
        horizontalLayout_7 = new QHBoxLayout(horizontalGroupBox_2);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_7->setSizeConstraint(QLayout::SetDefaultConstraint);
        mCtrlPlay = new QPushButton(horizontalGroupBox_2);
        mCtrlPlay->setObjectName(QStringLiteral("mCtrlPlay"));

        horizontalLayout_7->addWidget(mCtrlPlay);

        mCtrlPause = new QPushButton(horizontalGroupBox_2);
        mCtrlPause->setObjectName(QStringLiteral("mCtrlPause"));

        horizontalLayout_7->addWidget(mCtrlPause);

        mCtrlStop = new QPushButton(horizontalGroupBox_2);
        mCtrlStop->setObjectName(QStringLiteral("mCtrlStop"));

        horizontalLayout_7->addWidget(mCtrlStop);


        verticalLayout_4->addWidget(horizontalGroupBox_2);

        horizontalGroupBox = new QGroupBox(EFilmSheet);
        horizontalGroupBox->setObjectName(QStringLiteral("horizontalGroupBox"));
        verticalLayout_2 = new QVBoxLayout(horizontalGroupBox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        mFileNew = new QPushButton(horizontalGroupBox);
        mFileNew->setObjectName(QStringLiteral("mFileNew"));

        horizontalLayout_2->addWidget(mFileNew);

        mFileOpen = new QPushButton(horizontalGroupBox);
        mFileOpen->setObjectName(QStringLiteral("mFileOpen"));

        horizontalLayout_2->addWidget(mFileOpen);

        mFileSave = new QPushButton(horizontalGroupBox);
        mFileSave->setObjectName(QStringLiteral("mFileSave"));

        horizontalLayout_2->addWidget(mFileSave);


        verticalLayout_2->addLayout(horizontalLayout_2);

        mFileName = new QLabel(horizontalGroupBox);
        mFileName->setObjectName(QStringLiteral("mFileName"));

        verticalLayout_2->addWidget(mFileName);


        verticalLayout_4->addWidget(horizontalGroupBox);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_2 = new QLabel(EFilmSheet);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAutoFillBackground(true);
        label_2->setWordWrap(true);

        verticalLayout->addWidget(label_2);

        mFrameList = new QListView(EFilmSheet);
        mFrameList->setObjectName(QStringLiteral("mFrameList"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(1);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(mFrameList->sizePolicy().hasHeightForWidth());
        mFrameList->setSizePolicy(sizePolicy2);
        mFrameList->setFrameShape(QFrame::Box);
        mFrameList->setFrameShadow(QFrame::Sunken);
        mFrameList->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        verticalLayout->addWidget(mFrameList);


        verticalLayout_4->addLayout(verticalLayout);


        horizontalLayout_5->addLayout(verticalLayout_4);


        retranslateUi(EFilmSheet);

        QMetaObject::connectSlotsByName(EFilmSheet);
    } // setupUi

    void retranslateUi(QWidget *EFilmSheet)
    {
        EFilmSheet->setWindowTitle(QApplication::translate("EFilmSheet", "EFilmSheet", 0));
        label->setText(QApplication::translate("EFilmSheet", "Mode:", 0));
        mModePlay->setText(QApplication::translate("EFilmSheet", "Play", 0));
        mModeRecord->setText(QApplication::translate("EFilmSheet", "Record", 0));
        mCtrlPlay->setText(QApplication::translate("EFilmSheet", "Play", 0));
        mCtrlPause->setText(QApplication::translate("EFilmSheet", "Pause", 0));
        mCtrlStop->setText(QApplication::translate("EFilmSheet", "Stop", 0));
        mFileNew->setText(QApplication::translate("EFilmSheet", "New", 0));
        mFileOpen->setText(QApplication::translate("EFilmSheet", "Open", 0));
        mFileSave->setText(QApplication::translate("EFilmSheet", "Save", 0));
        mFileName->setText(QApplication::translate("EFilmSheet", "File:", 0));
        label_2->setText(QApplication::translate("EFilmSheet", "Frames", 0));
    } // retranslateUi

};

namespace Ui {
    class EFilmSheet: public Ui_EFilmSheet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EFILMSHEET_H
