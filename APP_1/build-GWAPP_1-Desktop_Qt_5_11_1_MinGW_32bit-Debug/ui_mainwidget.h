/********************************************************************************
** Form generated from reading UI file 'mainwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIDGET_H
#define UI_MAINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWidget
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWidget)
    {
        if (MainWidget->objectName().isEmpty())
            MainWidget->setObjectName(QStringLiteral("MainWidget"));
        MainWidget->resize(400, 300);
        menuBar = new QMenuBar(MainWidget);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        MainWidget->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWidget);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWidget->addToolBar(mainToolBar);
        centralWidget = new QWidget(MainWidget);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MainWidget->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWidget);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWidget->setStatusBar(statusBar);

        retranslateUi(MainWidget);

        QMetaObject::connectSlotsByName(MainWidget);
    } // setupUi

    void retranslateUi(QMainWindow *MainWidget)
    {
        MainWidget->setWindowTitle(QApplication::translate("MainWidget", "MainWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWidget: public Ui_MainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H
