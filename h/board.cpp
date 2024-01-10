#include "board.h"
#include "ships.h"

#include <iostream>

playerBoards::playerBoards() {
        // Заповнення буквами і цифрами
        for (int i = 0; i < boardSize; i++) {
            charBoard[i][boardSize] = static_cast<char>(i + 65);
            charBoard[boardSize][i] = static_cast<char>(i + 48);
        }
        charBoard[boardSize][boardSize] = 0; // правий нижній кут інтерфейсної дошки - пусте місце

        // Заповнення решти інтерфейсної дошки
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

void Board::clearing(playerBoards &player, playerShips &Ships, Board &board, Ship &ship){
    // оновлення дошок до дефолтного значення для подальшої встановки
     for (int i = 0; i < boardSize; i++){
        for (int j = 0; j < boardSize; j++){
                player.intBoard[i][j] = -1;
                player.charBoard[i][j] = '-';

        }
    }
    Ships.pShips[0] = 4;
    Ships.pShips[1] = 3;
    Ships.pShips[2] = 2;
    Ships.pShips[3] = 0;
    Ships.pShips[4] = 1;
}

void Board::minuss( Board &board){
   for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            player1.charBoard[i][j] = '-';
            player2.charBoard[i][j] = '-';

        }
    }
}



