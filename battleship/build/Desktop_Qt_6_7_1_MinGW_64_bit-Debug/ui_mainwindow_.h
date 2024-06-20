/********************************************************************************
** Form generated from reading UI file 'mainwindow_.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW__H
#define UI_MAINWINDOW__H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow_
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow_)
    {
        if (MainWindow_->objectName().isEmpty())
            MainWindow_->setObjectName("MainWindow_");
        MainWindow_->resize(800, 600);
        centralwidget = new QWidget(MainWindow_);
        centralwidget->setObjectName("centralwidget");
        MainWindow_->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow_);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 20));
        MainWindow_->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow_);
        statusbar->setObjectName("statusbar");
        MainWindow_->setStatusBar(statusbar);

        retranslateUi(MainWindow_);

        QMetaObject::connectSlotsByName(MainWindow_);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow_)
    {
        MainWindow_->setWindowTitle(QCoreApplication::translate("MainWindow_", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow_: public Ui_MainWindow_ {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW__H
