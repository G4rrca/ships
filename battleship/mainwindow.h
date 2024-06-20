#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void botSelected();
    void humanSelected();

private:
    Ui::MainWindow *ui;

    QPixmap bot;
    QPixmap two;

    QPushButton *botButton;
    QPushButton *twoButton;
};

#endif // MAINWINDOW_H
