#ifndef BOARD_H
#define BOARD_H

#include <iostream>

class Board {
public:
    int p1[5]; // кораблі першого гравця
    int p2[5]; // кораблі другого гравця

    int board1[10][10]; // ігрова дошка із цифрами першого гравця
    int board2[10][10]; // ігрова дошка із цифрами другого гравця
    char board11[11][11]; // ігрова дошка першого гравця для інтерфейсу
    char board22[11][11]; // ігрова дошка другого гравця для інтерфейсу

    Board();
    template <typename T, int Size> // потрібно для вдосконалення наступної функції, а саме щоб вона виводила будь-яку дошку
    void print_board(T (&board)[Size][Size]); // виведення дошки на екран
    void clearing(int player, Board &board); // очищення (скидання до дефолтного вигляду) дошки, треба при повторному автозаповненні
    void minuss(Board &board); // перед початком гри інтерфейсні дошки приводить до початкового вигляду (щоб не показувалися кораблі)
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
