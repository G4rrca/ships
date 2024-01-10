#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
#include "ships.h"
#include <iostream>
const int boardSize = 10;

struct playerBoards {
    int intBoard[boardSize][boardSize];
    char charBoard[boardSize + 1][boardSize + 1];
    int playerNumber;

    playerBoards();
};

class Board {
public:
    playerBoards player1; playerBoards player2;
    Board();
    template <typename T, int Size> // ������� ��� ������������� �������� �������, � ���� ��� ���� �������� ����-��� �����
    void print_board(T (&board)[Size][Size]); // ��������� ����� �� �����
    void clearing(playerBoards &player, playerShips &pShips, Board &board, Ship &ship); // �������� (�������� �� ���������� �������) �����, ����� ��� ���������� �������������
    void minuss(Board &board); // ����� �������� ��� ���������� ����� ��������� �� ����������� ������� (��� �� ������������ ������)
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

#endif // BOARD_H_INCLUDED
