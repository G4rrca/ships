#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QtGui>
#include <QMessageBox>
#include "mainwindow_sett.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(1000, 562);

    if (!bot.load("C:\\Users\\DEll\\Documents\\battleship\\img\\bot.png") ||
        !two.load("C:\\Users\\DEll\\Documents\\battleship\\img\\two.png")) {
        qCritical() << "Failed to load one or more images";
        return;
    }

    QPixmap bkgnd("C:\\Users\\DEll\\Documents\\battleship\\img\\main.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    botButton = new QPushButton(this);
    QIcon botIcon(bot);
    botButton->setIcon(botIcon);
    botButton->setIconSize(bot.size());
    botButton->resize(bot.size());
    botButton->move(279, 336);

    twoButton = new QPushButton(this);
    QIcon twoIcon(two);
    twoButton->setIcon(twoIcon);
    twoButton->setIconSize(two.size());
    twoButton->resize(two.size());
    twoButton->move(536, 336);

    connect(botButton, &QPushButton::clicked, this, &MainWindow::botSelected);
    connect(twoButton, &QPushButton::clicked, this, &MainWindow::humanSelected);
}

MainWindow::~MainWindow(){
    delete ui;
    delete botButton;
    delete twoButton;
}

void MainWindow::botSelected(){
    MainWindow_set *newWindow = new MainWindow_set(this, false); // pass false to the constructor
    this->close();
    newWindow->show();
}

void MainWindow::humanSelected(){ 
    MainWindow_set *newWindow = new MainWindow_set(this, true); // pass true to the constructor
    this->close();
    newWindow->show();
}
