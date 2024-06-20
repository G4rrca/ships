#ifndef MOVE_H_INCLUDED
#define MOVE_H_INCLUDED
#include "board.h"

class moving{
public:
    int mov_cout(Board &board, std::vector<typeShip> &playerShips,int player, playerBoards &player1, playerBoards &player2, int shotType, string input);
    int mov(string input, Board &board, std::vector<typeShip> &playerShips, int player, playerBoards &player1, playerBoards &player2);
    void bot_mov(Board &board, std::vector<typeShip> &playerShips, playerBoards &player1, bool shot, int prevHitRow, int prevHitCol);
    bool valid_move(string input, char board[boardSize+1][boardSize+1]);
    void addZona(string input, char direction, int shipType, int IntBoard[boardSize][boardSize], char CharBoard[boardSize+1][boardSize+1]);
    bool zona(string input, std::vector<typeShip> &playerShips, int IntBoard[boardSize][boardSize], char CharBoard[boardSize+1][boardSize+1]  );
    bool endgame(int tempIntBoard[boardSize][boardSize] );
};

#endif // MOVE_H_INCLUDED
