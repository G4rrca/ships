#include "board.h"
#include "ships.h"
playerBoards::playerBoards() {
    for (int i = 0; i < boardSize; i++) {
        charBoard[i][boardSize] = static_cast<char>(i + 65);
        charBoard[boardSize][i] = static_cast<char>(i + 48);
    }
    charBoard[boardSize][boardSize] = 0; // правий нижній кут інтерфейсної дошки - пусте місце

    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            charBoard[i][j] = '-';
            intBoard[i][j] = -1;
        }
    }
}

Board::Board() {
    playerBoards player1;
    player1.playerNumber = 1;
    playerBoards player2;
    player2.playerNumber = 2;
}

void Board::setCharCell(int player, int x, int y, char value) {
    if (player == 1) {
        player1.charBoard[x][y] = value;
    } else {
        player2.charBoard[x][y] = value;
    }
}

void Board::setIntCell(int player, int x, int y, int value) {
    if (player == 1) {
        player1.intBoard[x][y] = value;
    } else {
        player2.intBoard[x][y] = value;
    }
}

int Board::getIntCell(int player, int x, int y) const {
    if (player == 1) {
        return player1.intBoard[x][y];
    } else {
        return player2.intBoard[x][y];
    }
}

const playerBoards& Board::getPlayerBoard(int player) const {
    if (player == 1) {
        return player1;
    } else {
        return player2;
    }
}

void Board::clearing(playerBoards &player, playerShips &Ships, Board &board, Ship &ships, std::vector<typeShip>& playerShips) {
    // Оновлення дошок до дефолтного значення для подальшої встановки
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            player.intBoard[i][j] = -1;
            player.charBoard[i][j] = '-';
        }
    }

    Ships.pShips[0] = 4;
    Ships.pShips[1] = 3;
    Ships.pShips[2] = 2;
    Ships.pShips[3] = 0;
    Ships.pShips[4] = 1;

    playerShips.clear();
}




