#ifndef BOARD_H
#define BOARD_H
#include "ships.h"
#include <iostream>
const int boardSize = 10;

struct playerBoards {
    char charBoard[boardSize + 1][boardSize + 1]; // +1 for labels
    int intBoard[boardSize][boardSize];
    int playerNumber;
    playerBoards();
};

class Board {
public:
    Board();
    void setCharCell(int player, int x, int y, char value);
    void setIntCell(int player, int x, int y, int value);
    int getIntCell(int player, int x, int y) const;
    template <typename T, int Size>
    void print_board(T (&board)[Size][Size]);
    const playerBoards& getPlayerBoard(int player) const;
    void clearing(playerBoards &player, playerShips &pShips, Board &board, Ship &ship,  std::vector<typeShip>& playerShips);

    playerBoards player1;
    playerBoards player2;
};

template <typename T, int Size>
void Board::print_board(T (&board)[Size][Size]) {
    for (int i = 0; i < Size; i++) {
        for (int j = 0; j < Size; j++) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

#endif // BOARD_H
