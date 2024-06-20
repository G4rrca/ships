#ifndef SET_H_INCLUDED
#define SET_H_INCLUDED

#include "Board.h"
#include "ships.h"

using std::string;

class setting{
public:

    // перевіряємо чи морабель вміщається на дошку
    bool canPlaceShip(int shipType, int row, int col, char direction, int intBoard[boardSize][boardSize]);

    // перевірка правильності постановки корабля, зокрема чи він доступний
    bool valid_set(int num, string& number, int pShips[5], int intBoard[boardSize][boardSize], char charBoard[boardSize+1][boardSize+1], Ship &ship );

    // встановлення кораблів
    void sett(playerBoards &player, playerShips &ships, Board &board, Ship &ship, string input);

    // випадкове встановлення кораблів
    void bot_sett(playerBoards &player, playerShips &ships, Board &board, Ship &ship);
};

#endif // SET_H_INCLUDED
