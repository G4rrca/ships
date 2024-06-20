#include "ui_mainwindow2.h"
#include "mainwindow_game.h"
#include <QMessageBox>
#include "mainwindow.h"
#include <QDebug>
#include <QMouseEvent>
#include "move.h"

Board board1;
Ship ship1;
moving MOVE;

MainWindow2::MainWindow2(Board* board, Ship* ship, QWidget *parent, bool gameMode) :
    QMainWindow(parent),
    ui(new Ui::MainWindow2),
    board1(board),
    ship1(ship),
    shotType(shotType),
    gameMode(gameMode)
{

    ui->setupUi(this);
    this->resize(1000, 564);

    QPixmap bkgnd("C:\\Users\\DEll\\Documents\\battleship\\img\\background1000x574.png");
    QPixmap bkgn2("C:\\Users\\DEll\\Documents\\battleship\\img\\backgroundTWO.png");
    hlf = QPixmap("C:\\Users\\DEll\\Documents\\battleship\\img\\half28x28.png");
    fll = QPixmap("C:\\Users\\DEll\\Documents\\battleship\\img\\full28x28.png");
    shp = QPixmap("C:\\Users\\DEll\\Documents\\battleship\\img\\ship28x28.png");
    dt = QPixmap("C:\\Users\\DEll\\Documents\\battleship\\img\\dot28x28.png");
    shot1 = QPixmap("C:\\Users\\DEll\\Documents\\battleship\\img\\shot1.png");
    shot2 = QPixmap("C:\\Users\\DEll\\Documents\\battleship\\img\\shot2.png");
    shot3 = QPixmap("C:\\Users\\DEll\\Documents\\battleship\\img\\shot3.png");
    shot4 = QPixmap("C:\\Users\\DEll\\Documents\\battleship\\img\\shot4.png");
    shot5 = QPixmap("C:\\Users\\DEll\\Documents\\battleship\\img\\shot5.png");


    turnLabel = new QLabel(this);
    turnLabel->setGeometry(400, 26, 300, 100);
    QFont font("Arial", 26, QFont::Bold);
    turnLabel->setFont(font);
    if (gameMode == 0) {
        turnLabel->setText("");
    } else {
        turnLabel->setText("");
    }
    if (gameMode ==0)
    {
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Window, bkgnd);
        this->setPalette(palette);
    }
    else
    {
        bkgn2 = bkgn2.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Window, bkgn2);
        this->setPalette(palette);
    }

    shotType = 1;
    createButtons();
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            QLabel* cell1 = new QLabel(this);
            cell1->setFixedSize(30, 30);
            cell1->setStyleSheet("QLabel { border: 1px solid black; }");
            cell1->move(147 + j * 28, 140 + i * 28);
            cell1->setAlignment(Qt::AlignCenter);
            cell1->installEventFilter(this);
            boardCells1[i][j] = cell1;

        }
    }
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            QLabel* cell2 = new QLabel(this);
            cell2->setFixedSize(30, 30);
            cell2->setStyleSheet("QLabel { border: 1px solid black; }");
            cell2->move(577 + j * 28, 140 + i * 28);
            cell2->setAlignment(Qt::AlignCenter);
            cell2->installEventFilter(this);
            boardCells2[i][j] = cell2;
        }
    }
    if (player == 1){
        turnLabel->setText("Turn: Player 1");
    }
    else
        turnLabel->setText("Turn: Player 2");
}

void MainWindow2::createButtons() {
    shot1Button = new QPushButton(this);
    shot2Button = new QPushButton(this);
    shot3Button = new QPushButton(this);
    shot4Button = new QPushButton(this);
    shot5Button = new QPushButton(this);

    shot1Button->setIcon(QIcon(shot1));
    shot2Button->setIcon(QIcon(shot2));
    shot3Button->setIcon(QIcon(shot3));
    shot4Button->setIcon(QIcon(shot4));
    shot5Button->setIcon(QIcon(shot5));

    shot1Button->setIconSize(shot1.size());
    shot2Button->setIconSize(shot2.size());
    shot3Button->setIconSize(shot3.size());
    shot4Button->setIconSize(shot4.size());
    shot5Button->setIconSize(shot5.size());

    shot1Button->resize(shot1.size());
    shot2Button->resize(shot2.size());
    shot3Button->resize(shot3.size());
    shot4Button->resize(shot4.size());
    shot5Button->resize(shot5.size());

    shot1Button->move(455, 112);
    shot2Button->move(455, 197);
    shot3Button->move(455, 280);
    shot4Button->move(455, 364);
    shot5Button->move(455, 448);

    connect(shot1Button, &QPushButton::clicked, this, &MainWindow2::selectShot1);
    connect(shot2Button, &QPushButton::clicked, this, &MainWindow2::selectShot2);
    connect(shot3Button, &QPushButton::clicked, this, &MainWindow2::selectShot3);
    connect(shot4Button, &QPushButton::clicked, this, &MainWindow2::selectShot4);
    connect(shot5Button, &QPushButton::clicked, this, &MainWindow2::selectShot5);
}

MainWindow2::~MainWindow2() {
    delete ui;
}

void MainWindow2::selectShot1() {
    qDebug() << "Shot 1 selected";
    shotType = 1;
}

void MainWindow2::selectShot2() {
    qDebug() << "Shot 2 selected";
    shotType = 2;
}

void MainWindow2::selectShot3() {
    qDebug() << "Shot 3 selected";
    shotType = 3;
}

void MainWindow2::selectShot4() {
    qDebug() << "Shot 4 selected";
    shotType = 4;
}

void MainWindow2::selectShot5() {
    qDebug() << "Shot 5 selected";
    shotType = 5;
}

bool MainWindow2::eventFilter(QObject* watched, QEvent* event) {
    if (event->type() == QEvent::MouseButtonPress) {
        QLabel* clickedLabel = qobject_cast<QLabel*>(watched);
        if (clickedLabel) {
            QPoint pos = clickedLabel->pos();
            int row = (pos.y() - 140) / 28;
            int col = (pos.x() - 147) / 28;

            if (col > 10)
            {
                col = col - 15;
            }
            // qDebug() << "Row = " << row;
            // qDebug() << "Col = " << col;

            if (row < 10 && col < 10) {
                updateBoard(row, col, gameMode);
            }

            return true;
        }
    }
    return QMainWindow::eventFilter(watched, event);
}

void MainWindow2::updateBoard(int row, int col, bool gameMode) {
    string input;

    char rowChar = 'A' + row;

    input += rowChar;
    input += std::to_string(col);

    if (!gameMode) {
        int result = MOVE.mov_cout(*board1, ship1->player2Ships, 1, board1->player1, board1->player2, shotType, input);
        if (result == 0) {
            MOVE.bot_mov(*board1, ship1->player1Ships, board1->player1, 0, 0, 0);
        }
        else if (result == 3) {
            // Виведення повідомлення про перемогу гравця 1
            QMessageBox::information(this, "Гру завершено", "Всі кораблі збито!");
            board1->clearing(board1->player1, ship1->ships1, *board1, *ship1, ship1->player1Ships);
            board1->clearing(board1->player2, ship1->ships2, *board1, *ship1, ship1->player2Ships);
            // Закриття поточного вікна MainWindow2
            this->close();
            // Відкриття головного вікна MainWindow
            MainWindow *mainWindow = new MainWindow();
            mainWindow->show();
            return;
        }
        // std::cout << "" << std::endl;
        // board1->print_board(board1->player1.charBoard);
        // board1->print_board(board1->player1.intBoard);
        // std::cout << "" << std::endl;
    }
    else {
        if (player == 1){
            int result = MOVE.mov_cout(*board1, ship1->player2Ships, 1, board1->player1, board1->player2, shotType, input);
            if (result == 0){
                player=2;
                turnLabel->setText("Turn: Player 2");
            }
            else if (result == 3) {
                QMessageBox::information(this, "Гру завершено", "Всі кораблі збито!");
                board1->clearing(board1->player1, ship1->ships1, *board1, *ship1, ship1->player1Ships);
                board1->clearing(board1->player2, ship1->ships2, *board1, *ship1, ship1->player2Ships);
                // Закриття поточного вікна MainWindow2
                this->close();
                // Відкриття головного вікна MainWindow
                MainWindow *mainWindow = new MainWindow();
                mainWindow->show();
                return;
            }
        }
        else{
            int result = MOVE.mov_cout(*board1, ship1->player1Ships, 2, board1->player2, board1->player1, shotType, input);

            if (result == 0){
                player=1;
                turnLabel->setText("Turn: Player 1");
            }
            else if (result == 3) {
                QMessageBox::information(this, "Гру завершено", "Всі кораблі збито!");
                board1->clearing(board1->player1, ship1->ships1, *board1, *ship1, ship1->player1Ships);
                board1->clearing(board1->player2, ship1->ships2, *board1, *ship1, ship1->player2Ships);

                this->close();

                MainWindow *mainWindow = new MainWindow();
                mainWindow->show();
                return;
            }

        }
    }

    for (int i=0; i <10; i++){
        for (int j = 0; j < 10; j++){
            if (board1->player2.intBoard[i][j] == 0) {
                QLabel* cell1 = boardCells1[i][j];
                if (cell1) {
                    cell1->setPixmap(hlf);
                }
            } else if (board1->player2.intBoard[i][j]== 7) {
                QLabel* cell1 = boardCells1[i][j];
                if (cell1) {
                    cell1->setPixmap(dt);
                }
            }
        }
    }
    for (int i=0; i <10; i++){
        for (int j = 0; j < 10; j++){
            if (board1->player1.intBoard[i][j] == 0) {
                QLabel* cell1 = boardCells2[i][j];
                if (cell1) {
                    cell1->setPixmap(hlf);
                }
            } else if (board1->player1.intBoard[i][j]== 7) {
                QLabel* cell1 = boardCells2[i][j];
                if (cell1) {
                    cell1->setPixmap(dt);
                }
            }
        }
    }
}
