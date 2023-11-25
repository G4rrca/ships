#include "Board.h"
#include <iostream>

using namespace std;

Board::Board() {
     p1[0] = 4; p2[0] = 4;
        p1[1] = 3; p2[1] = 3;
        p1[2] = 2; p2[2] = 2;
        p1[3] = 0; p2[3] = 0;
        p1[4] = 1; p2[4] = 1;

        board11[10][10] = 0;
        board22[10][10] = 0;

         for (int i = 0; i < 10; i++){
            board11[i][10] = i + 65;
            board11[10][i] = i + 48;
        }
        for (int i = 0; i < 10; i++){
            for (int j = 0; j < 10; j++){
                board11[i][j] = '-';
               }
        }
        for (int i = 0; i < 10; i++){
            board22[i][10] = i + 65;
            board22[10][i] = i + 48;
        }
        for (int i = 0; i < 10; i++){
            for (int j = 0; j < 10; j++){
                board22[i][j] = '-';
            }
        }
        for (int i = 0; i< 10; i++){
            for (int j =  0; j< 10; j++){
                board1[i][j] = -1;
                board2[i][j] = -1;
            }
        }
}



