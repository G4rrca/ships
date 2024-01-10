#ifndef SET_H_INCLUDED
#define SET_H_INCLUDED

#include "Board.h"
#include "ships.h"


using std::string;

class setting{
    public:

    // ���������� �� �������� �������� �� �����
    bool canPlaceShip(int shipType, int row, int col, char direction, int intBoard[boardSize][boardSize]);

    // �������� ������� ������
    string retryInput();

    int retryInt();

    // �������� ����������� ���������� �������, ������� �� �� ���������
    bool valid_set(int num, string& number, int pShips[5], int intBoard[boardSize][boardSize], char charBoard[boardSize+1][boardSize+1], bool human, Ship &ship );

    // ������������ �������
    void sett(playerBoards &player, playerShips &ships, Board &board, Ship &ship);

    // ��������� ������������ �������
    void bot_sett(playerBoards &player, playerShips &ships, Board &board, Ship &ship);
};

#endif // SET_H_INCLUDED
