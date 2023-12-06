#ifndef MOVING_H
#define MOVING_H
#include "Board.h"

class moving{
    public:
        void minuss(Board &board);
        bool mov(int player, Board &board);
        void bot_mov(int player, Board &board, bool shot, int prevHitRow, int prevHitCol);
        bool valid_move(std::string number, char board[11][11]);
        bool zona( int row, int col, int board2[10][10], char board22[11][11]);
        void endgame(int board33[10][10], char board3[11][11]);
};
#endif
