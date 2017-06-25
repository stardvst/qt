/********************************************************************************
** Form generated from reading UI file 'FindDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDDIALOG_H
#define UI_FINDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FindDialogClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *FindDialogClass)
    {
        if (FindDialogClass->objectName().isEmpty())
            FindDialogClass->setObjectName(QStringLiteral("FindDialogClass"));
        FindDialogClass->resize(600, 400);
        menuBar = new QMenuBar(FindDialogClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        FindDialogClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(FindDialogClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        FindDialogClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(FindDialogClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        FindDialogClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(FindDialogClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        FindDialogClass->setStatusBar(statusBar);

        retranslateUi(FindDialogClass);

        QMetaObject::connectSlotsByName(FindDialogClass);
    } // setupUi

    void retranslateUi(QMainWindow *FindDialogClass)
    {
        FindDialogClass->setWindowTitle(QApplication::translate("FindDialogClass", "FindDialog", 0));
    } // retranslateUi

};

namespace Ui {
    class FindDialogClass: public Ui_FindDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDDIALOG_H
