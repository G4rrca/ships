#include <ctime>
#include <windows.h>
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include "mainwindow.h"
#include <windows.h>

int main(int argc, char *argv[]) {
    srand(static_cast<unsigned int>(std::time(0)));
    SetConsoleOutputCP(1251);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

}
