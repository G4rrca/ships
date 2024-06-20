#ifndef MAINWINDOW_SETT_H
#define MAINWINDOW_SETT_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>

namespace Ui {
class MainWindow_set;
}

enum ShipType {
    None,
    Ship1,
    Ship2,
    Ship3,
    Ship5
};

class MainWindow_set : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_set(QWidget *parent = nullptr, int gameMode = 0);
    ~MainWindow_set();

private slots:
    void selectShip1();
    void selectShip2();
    void selectShip3();
    void selectShip5();
    void selectShip22();
    void selectShip33();
    void selectShip55();
    void selectClear();
    void selectRandom();
    void selectPlay(int gameMode);


private:
    Ui::MainWindow_set *ui;
    char selectedDirection;
    QPushButton *ship5Button;
    QPushButton *ship3Button;
    QPushButton *ship2Button;
    QPushButton *ship1Button;
    QPushButton *ship55Button;
    QPushButton *ship33Button;
    QPushButton *ship22Button;
    QPushButton *clearButton;
    QPushButton *randomButton;
    QPushButton *playButton;
    int currentPlayer = 1;
    QPixmap ship1, ship2, ship3, ship5, clr, rndm, play;
    ShipType selectedShipType;
    QLabel* boardCells[10][10];
    bool eventFilter(QObject *watched, QEvent *event) override;
    void placeShip(int row, int col);
    int gameMode;
};

#endif // MAINWINDOW_SETT_H
