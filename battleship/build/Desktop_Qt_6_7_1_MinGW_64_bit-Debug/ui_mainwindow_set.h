/********************************************************************************
** Form generated from reading UI file 'mainwindow_set.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_SET_H
#define UI_MAINWINDOW_SET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow_set
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow_set)
    {
        if (MainWindow_set->objectName().isEmpty())
            MainWindow_set->setObjectName("MainWindow_set");
        MainWindow_set->resize(800, 600);
        centralwidget = new QWidget(MainWindow_set);
        centralwidget->setObjectName("centralwidget");
        MainWindow_set->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow_set);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 20));
        MainWindow_set->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow_set);
        statusbar->setObjectName("statusbar");
        MainWindow_set->setStatusBar(statusbar);

        retranslateUi(MainWindow_set);

        QMetaObject::connectSlotsByName(MainWindow_set);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow_set)
    {
        MainWindow_set->setWindowTitle(QCoreApplication::translate("MainWindow_set", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow_set: public Ui_MainWindow_set {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_SET_H
