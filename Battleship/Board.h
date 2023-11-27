#ifndef BOARD_H
#define BOARD_H

#include <iostream>

class Board {
public:
    int p1[5];
    int p2[5];

    int board1[10][10];
    char board11[11][11]; // дошки першого гравця
    int board2[10][10];
    char board22[11][11]; // дошки другого гравця

    Board();
    template <typename T, int Size>
    void print_board(T (&board)[Size][Size]);
    void clearing(int player, Board &board);
    void minuss(Board &board);
};

// Визначення шаблону функції print_board
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
