#ifndef MAINWINDOW_BOT_H
#define MAINWINDOW_BOT_H

#include <QMainWindow>
#include <QPushButton>
#include <QPixmap>

namespace Ui {
class MainWindow_bot;
}

class MainWindow_bot : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_bot(QWidget *parent = nullptr);
    ~MainWindow_bot();

private:
    QPixmap ship1;
    QPixmap ship2;
    QPixmap ship3;
    QPixmap ship5;

    QPushButton *ship1Button;
    QPushButton *ship2Button;
    QPushButton *ship3Button;
    QPushButton *ship5Button;

    Ui::MainWindow_bot *ui;
};

#endif // MAINWINDOW_BOT_H
