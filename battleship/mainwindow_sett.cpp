#include "mainwindow_sett.h"
#include "ui_mainwindow_sett.h"
#include "mainwindow_game.h"
#include <QGridLayout>
#include <QLabel>
#include <QDebug>
#include <QPushButton>
#include "set.h"
#include "board.h"
#include "ships.h"
#include <QMessageBox>

setting SET;
Board board;
Ship ship;
std::vector<string> placement;

MainWindow_set::MainWindow_set(QWidget *parent, int gameMode):
    QMainWindow(parent),
    ui(new Ui::MainWindow_set),
    selectedDirection('H'),
    currentPlayer(1),
    selectedShipType(None),
    gameMode(gameMode){
    ui->setupUi(this);  // Ініціалізація UI
    this->resize(1000, 562);
    // int gamemode = gameMode;
    if (gameMode == 2)
        currentPlayer = 2;
    // Завантаження зображень з перевіркою
    if (!ship1.load("C:\\Users\\DEll\\Documents\\battleship\\img\\ship1.png") ||
        !ship2.load("C:\\Users\\DEll\\Documents\\battleship\\img\\ship2.png") ||
        !ship3.load("C:\\Users\\DEll\\Documents\\battleship\\img\\ship3.png") ||
        !ship5.load("C:\\Users\\DEll\\Documents\\battleship\\img\\ship5.png") ||
        !rndm.load("C:\\Users\\DEll\\Documents\\battleship\\img\\random.png") ||
        !play.load("C:\\Users\\DEll\\Documents\\battleship\\img\\play.png") ||
        !clr.load("C:\\Users\\DEll\\Documents\\battleship\\img\\clear.png")
        ) {
        qCritical() << "Failed to load one or more images";
        return;
    }

    QPixmap bkgnd("C:\\Users\\DEll\\Documents\\battleship\\img\\set1000x574.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    // Ініціалізація кнопок
    ship5Button = new QPushButton(this);
    QIcon icon5(ship5);
    ship5Button->setIcon(icon5);
    ship5Button->setIconSize(ship5.size());
    ship5Button->resize(ship5.size());


    QTransform transform;
    transform.rotate(90);

    QPixmap rotatedShip55 = ship5.transformed(transform);
    ship55Button = new QPushButton(this);
    QIcon icon55(rotatedShip55);
    ship55Button->setIcon(icon55);
    ship55Button->setIconSize(rotatedShip55.size());
    ship55Button->resize(rotatedShip55.size());

    ship3Button = new QPushButton(this);
    QIcon icon3(ship3);
    ship3Button->setIcon(icon3);
    ship3Button->setIconSize(ship3.size());
    ship3Button->resize(ship3.size());

    QPixmap rotatedShip33 = ship3.transformed(transform);
    ship33Button = new QPushButton(this);
    QIcon icon33(rotatedShip33);
    ship33Button->setIcon(icon33);
    ship33Button->setIconSize(rotatedShip33.size());
    ship33Button->resize(rotatedShip33.size());

    ship2Button = new QPushButton(this);
    QIcon icon2(ship2);
    ship2Button->setIcon(icon2);
    ship2Button->setIconSize(ship2.size());
    ship2Button->resize(ship2.size());

    QPixmap rotatedShip22 = ship2.transformed(transform);
    ship22Button = new QPushButton(this);
    QIcon icon22(rotatedShip22);
    ship22Button->setIcon(icon22);
    ship22Button->setIconSize(rotatedShip22.size());
    ship22Button->resize(rotatedShip22.size());

    ship1Button = new QPushButton(this);
    QIcon icon1(ship1);
    ship1Button->setIcon(icon1);
    ship1Button->setIconSize(ship1.size());
    ship1Button->resize(ship1.size());

    clearButton = new QPushButton(this);
    QIcon icon6(clr);
    clearButton->setIcon(icon6);
    clearButton->setIconSize(clr.size());
    clearButton->resize(clr.size());

    randomButton = new QPushButton(this);
    QIcon icon7(rndm);
    randomButton->setIcon(icon7);
    randomButton->setIconSize(rndm.size());
    randomButton->resize(rndm.size());

    playButton = new QPushButton(this);
    QIcon iconPlay(play);
    playButton ->setIcon(iconPlay);
    playButton ->setIconSize(play.size());
    playButton ->resize(play.size());

    // Встановлення кнопок у певних точках
    ship5Button->move(600, 167);
    ship3Button->move(600, 224);
    ship2Button->move(600, 281);
    ship1Button->move(630, 336);

    ship55Button->move(800, 252);
    ship33Button->move(743, 308);
    ship22Button->move(684, 336);

    clearButton->move(716,222);

    randomButton->move(620,430);

    playButton->move(325,430);
    // Підключення сигналів і слотів
    connect(ship5Button, &QPushButton::clicked, this, &MainWindow_set::selectShip5);
    connect(ship3Button, &QPushButton::clicked, this, &MainWindow_set::selectShip3);
    connect(ship2Button, &QPushButton::clicked, this, &MainWindow_set::selectShip2);
    connect(ship1Button, &QPushButton::clicked, this, &MainWindow_set::selectShip1);

    connect(ship55Button, &QPushButton::clicked, this, &MainWindow_set::selectShip55);
    connect(ship33Button, &QPushButton::clicked, this, &MainWindow_set::selectShip33);
    connect(ship22Button, &QPushButton::clicked, this, &MainWindow_set::selectShip22);

    connect(clearButton, &QPushButton::clicked, this, &MainWindow_set::selectClear);
    connect(randomButton, &QPushButton::clicked, this, &MainWindow_set::selectRandom);
    connect(playButton, &QPushButton::clicked, [this, gameMode]() { this->selectPlay(gameMode); });

    // Підключення сигналів кліків по ігровому полю
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            QLabel* cell = new QLabel(this);
            cell->setFixedSize(30, 30);
            cell->setStyleSheet("QLabel { border: 1px solid black; }");
            cell->move(290 + j * 28, 140 + i * 28);
            cell->setAlignment(Qt::AlignCenter);
            cell->installEventFilter(this);  // Для обробки кліків по клітинках
            boardCells[i][j] = cell;
        }
    }
    if (gameMode ==0)
    {
        SET.bot_sett(board.player2, ship.ships2, board, ship);
    }
}

void MainWindow_set::selectShip55() {
    selectedShipType = Ship5;
    selectedDirection = 'V';
    if (currentPlayer == 1)
    {
        if (ship.ships1.pShips[4] == 0){
            QMessageBox::critical(this, "Помилка", "Кораблів цього типу не залишилося!");
        }
    }
    else
    {
        if (ship.ships2.pShips[4] == 0){
            QMessageBox::critical(this, "Помилка", "Кораблів цього типу не залишилося!");
        }
    }
}

void MainWindow_set::selectShip33() {
    selectedShipType = Ship3;
    selectedDirection = 'V';
    if (currentPlayer == 1)
    {
        if (ship.ships1.pShips[2] == 0){
            QMessageBox::critical(this, "Помилка", "Кораблів цього типу не залишилося!");
        }
    }
    else
    {
        if (ship.ships2.pShips[2] == 0){
            QMessageBox::critical(this, "Помилка", "Кораблів цього типу не залишилося!");
        }
    }
}

void MainWindow_set::selectShip22() {
    selectedShipType = Ship2;
    selectedDirection = 'V';
    if (currentPlayer == 1)
    {
        if (ship.ships1.pShips[1] == 0){
            QMessageBox::critical(this, "Помилка", "Кораблів цього типу не залишилося!");
        }
    }
    else
    {
        if (ship.ships2.pShips[1] == 0){
            QMessageBox::critical(this, "Помилка", "Кораблів цього типу не залишилося!");
        }
    }
}

void MainWindow_set::selectShip5() {
    selectedShipType = Ship5;
    selectedDirection = 'H';
    if (currentPlayer == 1)
    {
        if (ship.ships1.pShips[4] == 0){
            QMessageBox::critical(this, "Помилка", "Кораблів цього типу не залишилося!");
        }
    }
    else
    {
        if (ship.ships2.pShips[4] == 0){
            QMessageBox::critical(this, "Помилка", "Кораблів цього типу не залишилося!");
        }
    }
}

void MainWindow_set::selectShip3() {
    selectedShipType = Ship3;
    selectedDirection = 'H';
    if (currentPlayer == 1)
    {
        if (ship.ships1.pShips[2] == 0){
            QMessageBox::critical(this, "Помилка", "Кораблів цього типу не залишилося!");
        }
    }
    else
    {
        if (ship.ships2.pShips[2] == 0){
            QMessageBox::critical(this, "Помилка", "Кораблів цього типу не залишилося!");
        }
    }

}

void MainWindow_set::selectShip2() {
    selectedShipType = Ship2;
    selectedDirection = 'H';
    if (currentPlayer == 1)
    {
        if (ship.ships1.pShips[1] == 0){
            QMessageBox::critical(this, "Помилка", "Кораблів цього типу не залишилося!");
        }
    }
    else
    {
        if (ship.ships2.pShips[1] == 0){
            QMessageBox::critical(this, "Помилка", "Кораблів цього типу не залишилося!");
        }
    }
}

void MainWindow_set::selectShip1() {
    selectedShipType = Ship1;
    if (currentPlayer == 1)
    {
        if (ship.ships1.pShips[0] == 0){
            QMessageBox::critical(this, "Помилка", "Кораблів цього типу не залишилося!");
        }
    }
    else
    {
        if (ship.ships2.pShips[0] == 0){
            QMessageBox::critical(this, "Помилка", "Кораблів цього типу не залишилося!");
        }
    }
}

void MainWindow_set::selectClear() {
    if (currentPlayer ==1) {
        board.clearing(board.player1, ship.ships1, board, ship, ship.player1Ships);
    }
    else{
        board.clearing(board.player2, ship.ships2, board, ship, ship.player2Ships);
    }

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            boardCells[i][j]->setStyleSheet("QLabel { border: 1px solid black; }");
        }
    }
}

void MainWindow_set::selectPlay(int gameMode) {

    std::cout << "ship.player1Ships.size()  " << ship.player1Ships.size()  << std::endl;


        if (gameMode == 0 ) {
            if (ship.player1Ships.size() ==10){
                MainWindow2 *newWindow = new MainWindow2(&board, &ship, this, 0);
                this->close();
                newWindow->show();
            }
            else
            {
                QMessageBox::critical(this, "Помилка", "Не хитруй!");
            }
        }
        else if (gameMode == 2) {
            if (ship.player2Ships.size() ==10){
                MainWindow2 *newWindow = new MainWindow2(&board, &ship, this, true);
                this->close();
                newWindow->show();
            }
            else
            {
                QMessageBox::critical(this, "Помилка", "Не хитруй!");
            }
        }

        else if (gameMode == 1 && currentPlayer ==1) {
            if (ship.player1Ships.size() ==10){
                MainWindow_set *newWindow = new MainWindow_set(this, 2);
                this->close();
                newWindow->show();
            }
            else
            {
                QMessageBox::critical(this, "Помилка", "Не хитруй!");
            }
        }
}

void MainWindow_set::selectRandom() {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            boardCells[i][j]->setStyleSheet("QLabel { border: 1px solid black; }");
        }
    }

    if (currentPlayer == 1){
        SET.bot_sett(board.player1, ship.ships1, board, ship);

        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                if (0 < board.player1.intBoard[i][j] && board.player1.intBoard[i][j] < 6){
                    boardCells[i][j]->setStyleSheet("QLabel { background-color: white; border: 5px solid black; }");
                }
            }
        }
    }
    else{
        SET.bot_sett(board.player2, ship.ships2, board, ship);

        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                if (0 < board.player2.intBoard[i][j] && board.player2.intBoard[i][j] < 6){
                    boardCells[i][j]->setStyleSheet("QLabel { background-color: white; border: 5px solid black; }");
                }
            }
        }
    }
}

MainWindow_set::~MainWindow_set(){
    delete ui;
    delete ship5Button;
    delete ship3Button;
    delete ship2Button;
    delete ship1Button;
    delete ship55Button;
    delete ship33Button;
    delete ship22Button;
    delete clearButton;
    delete playButton;
}

// Обробка кліків по клітинках ігрового поля
bool MainWindow_set::eventFilter(QObject* watched, QEvent* event) {
    if (event->type() == QEvent::MouseButtonPress) {
        QLabel* clickedLabel = qobject_cast<QLabel*>(watched);
        if (clickedLabel) {
            QPoint pos = clickedLabel->pos();
            int row = (pos.y() - 140) / 28;
            // qDebug() << "Row = " << row ;
            // qDebug() << "pos.y()= " << pos.y() ;
            int col = (pos.x() - 290) / 28;
            // qDebug() << "Col = " << col ;
            // qDebug() << "pos.x()= " << pos.x() ;
            placeShip(row, col);
            return true;
        }
    }
    return QMainWindow::eventFilter(watched, event);
}

// Встановлення корабля на поле
void MainWindow_set::placeShip(int row, int col) {
    if (selectedShipType == None) return;
    int shipSize = 0;
    switch (selectedShipType) {
    case Ship1: shipSize = 1; break;
    case Ship2: shipSize = 2; break;
    case Ship3: shipSize = 3; break;
    case Ship5: shipSize = 5; break;
    default: return;
    }
    if (currentPlayer ==1)
    {
        if (!SET.canPlaceShip(shipSize, row, col, selectedDirection, board.player1.intBoard)) {
            qDebug() << "Cannot place ship at (" << row << "," << col << ") direction: " << selectedDirection;
            return;
        }
        std::string input = std::to_string(shipSize) + std::to_string(row) + std::to_string(col) + std::string(1, selectedDirection);

        if (SET.valid_set(1,input, ship.ships1.pShips, board.player1.intBoard, board.player1.charBoard, ship))
        {
            if (selectedDirection == 'H') {
                for (int i = 0; i < shipSize; ++i) {
                    boardCells[row][col + i]->setStyleSheet("QLabel { background-color: white; border: 5px solid black; }");
                }
            } else if (selectedDirection == 'V') {
                for (int i = 0; i < shipSize; ++i) {
                    boardCells[row + i][col]->setStyleSheet("QLabel { background-color: white; border: 5px solid black; }");
                }
            }
        }
    }
    else
    {
        if (!SET.canPlaceShip(shipSize, row, col, selectedDirection, board.player2.intBoard)) {
            qDebug() << "Cannot place ship at (" << row << "," << col << ") direction: " << selectedDirection;
            return;
        }
        std::string input = std::to_string(shipSize) + std::to_string(row) + std::to_string(col) + std::string(1, selectedDirection);
        // SET.sett(board.player1, ship.ships1, board, ship, input);

        if (SET.valid_set(2,input, ship.ships2.pShips, board.player2.intBoard, board.player2.charBoard, ship))
        {
            if (selectedDirection == 'H') {
                for (int i = 0; i < shipSize; ++i) {
                    boardCells[row][col + i]->setStyleSheet("QLabel { background-color: white; border: 5px solid black; }");
                }
            } else if (selectedDirection == 'V') {
                for (int i = 0; i < shipSize; ++i) {
                    boardCells[row + i][col]->setStyleSheet("QLabel { background-color: white; border: 5px solid black; }");
                }
            }
        }
    }

    // Скидання вибору корабля
    selectedShipType = None;
}
