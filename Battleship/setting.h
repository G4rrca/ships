#ifndef SETTING_H
#define SETTING_H
#include "Board.h"

#include <iostream>
using namespace std;
class setting

{
    public:
    bool canPlaceShip(int shipType, int row, int col, char direction, int board[10][10]);
    string retryInput();
    bool valid_set(string& number, int q1[5], int board[10][10], char board1[11][11], bool human);

    void sett(int player, Board &board);
    void bot_sett(int player, Board &board);
};

#endif
