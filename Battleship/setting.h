#ifndef SETTING_H
#define SETTING_H
#include "Board.h"

using std::string;

class setting{
    public:

    // перевіряємо чи морабель вміщається на дошку
    bool canPlaceShip(int shipType, int row, int col, char direction, int board[10][10]);

    // повторне введеня вибору
    string retryInput();

    // перевірка правильності постановки корабля, зокрема чи він доступний
    bool valid_set(string& number, int q1[5], int board[10][10], char board1[11][11], bool human);

    // встановлення кораблів
    void sett(int player, Board &board);

    // випадкове встановлення кораблів
    void bot_sett(int player, Board &board);
};
#endif
