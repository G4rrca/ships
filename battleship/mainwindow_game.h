#ifndef MAINWINDOW_GAME_H
#define MAINWINDOW_GAME_H

#include <QMainWindow>
#include <QPixmap>
#include <QVector>
#include <QLabel>
#include "board.h"
#include <QPushButton>


namespace Ui {
    class MainWindow2;
}

class MainWindow2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow2(Board* board, Ship* ship, QWidget *parent = nullptr, bool gameMode = false);
    ~MainWindow2();
private slots:
    void selectShot1();
    void selectShot2();
    void selectShot3();
    void selectShot4();
    void selectShot5();
private:
    Ui::MainWindow2 *ui;
    QPushButton *shot1Button;
    QPushButton *shot2Button;
    QPushButton *shot3Button;
    QPushButton *shot4Button;
    QPushButton *shot5Button;
    QPixmap shp;
    QPixmap hlf;
    QPixmap dt;
    QPixmap fll;

    QPixmap shot1;
    QPixmap shot2;
    QPixmap shot3;
    QPixmap shot4;
    QPixmap shot5;
    QLabel* turnLabel;

    QVector<QLabel*> boardLabels;
    QLabel* boardCells1[10][10];
    QLabel* boardCells2[10][10];
    Board* board1;
    Ship* ship1;
    int shotType;
    int player = 1;
    bool gameMode;

    void createButtons();
    void updateBoard(int row, int col, bool gameMode);
    void placeShip(int row, int col);
    bool eventFilter(QObject *watched, QEvent *event) override;
};

#endif // MAINWINDOW_GAME_H
