#include "set.h"
#include "move.h"
#include <iostream>
#include "ships.h"
#include <set>

using std::string, std::cin, std::cout;
Ship Sship;
bool moving::valid_move(string input, char board[boardSize+1][boardSize+1]){
    input [0] = toupper(input[0]);
    int row = input[0] - 'A';
    int col = input[1] - '0';

    if (input.length() != 2){
        return 0;
    }
    if (board[row][col] == '+' || board[row][col] == 'o' ){
        return 0;
    } else
        return 1;
}
void moving::addZona(string input, char direction, int shipType, int IntBoard[boardSize][boardSize], char CharBoard[boardSize+1][boardSize+1] ){
    int row = input[0] - 'A';
    int col = input[1] - '0';
    if (direction== 'V'){
        row--;
        if (row > -1){ // якщо верхній край корабля не межує із краєм дошки
            IntBoard[row][col] = 7;
            CharBoard[row][col] = 'o';
        }
        if (row+ shipType +1 < boardSize){
            IntBoard[row+ shipType +1][col] = 7;
            CharBoard[row+  shipType +1][col] = 'o';
        }
        for (int i = 0; i !=  shipType + 2; i++){
            if (col - 1 > -1){
                if (row + i < boardSize && row + i > -1 ){
                    IntBoard[row+i][col -1 ] = 7;
                    CharBoard[row+i][col -1] = 'o';
                }
            }
            if (col + 1 < boardSize ){
                if (row + i < boardSize && row + i > -1){
                    IntBoard[row+i][col +1 ] = 7;
                    CharBoard[row+i][col +1] = 'o';
                }
            }
        }
    }
    else{
        col--;
        if (col > -1){ // якщо лівий край корабля не межує із краєм дошки
            IntBoard[row][col] = 7;
            CharBoard[row][col] = 'o';
        }
        if (col+ shipType +1 < boardSize){ // якщо правий край корабля не межує із краєм жошки
            IntBoard[row][col+ shipType +1] = 7;
            CharBoard[row][col+  shipType +1] = 'o';
        }
        for (int i = 0; i !=  shipType + 2; i++){ // оточуємо корабель смужкою зверху
            if (row - 1 > -1){ // якщо зверху немає межі дошки
                if (col + i > -1 && col + i < boardSize){
                    IntBoard[row-1][col +i ] = 7;
                    CharBoard[row-1][col +i] = 'o';
                }
            }
            if (row + 1 < boardSize){ // оточуємо корабель смужкою знизу
                if (col + i < boardSize && col + i > -1){ // якщо знизу немає межі дошки
                    IntBoard[row+1][col +i ] = 7;
                    CharBoard[row+1][col +i] = 'o';
                }
            }
        }
    }
}
bool moving::zona(string input, std::vector<typeShip> &playerShips, int IntBoard[boardSize][boardSize], char CharBoard[boardSize+1][boardSize+1] ) {
    for (auto &ship : playerShips) {
        for ( auto &coord : ship.placement) {
            if (coord == input) {
                ship.HP --;
                string coor = ship.placement[0];
                if (ship.HP == 0){
                    addZona(coor, ship.direction, ship.shipType, IntBoard, CharBoard);
                    return true;
                }
                return false;
            }
        }
    }
}

bool moving::endgame(int board33[boardSize][boardSize]){

    int moves = 0;

    for (int i = 0; i < boardSize; i++){
        for (int j = 0; j < boardSize; j++){
            if (board33[i][j] == 1 ||  board33[i][j] == 2 || board33[i][j] == 3 || board33[i][j] == 4 || board33[i][j] == 5 )
                moves ++;
        }
    }
    if (moves == 0){
        return 1;
    }
    return 0;
}


int moving::mov_cout(Board &board, std::vector<typeShip> &playerShips, int player,
                      playerBoards &player1, playerBoards &player2, int shotType, string input){
    int res;
    if (endgame(player2.intBoard) == 1)
    {
        return 3;
    }
    switch (shotType) {
    case 1:
        res = mov(input, board, playerShips, player, player1, player2);
        if ( res == 1)
            return 1;
        else if (res == 0)
            return 0;
        else
            return -1;
    case 2: // постріл цілий рядок
        res = mov(input, board, playerShips, player, player1, player2);
        if (res == -1){
            return -1;
        }
        for (int i = 0; i < 10; i++) {
            input[1] = (i + 48);
            if (mov(input, board, playerShips, player, player1, player2) == 1)
                return 1;
        }
        return 0;
    case 3: // постріл смужка 3 на 1
        for (int i = 0; i < 1; i++) {
            res = mov(input, board, playerShips, player, player1, player2);
            if (res == -1){
                return -1;
            }

            input[1] = input[1] - 1;
            if (mov(input, board, playerShips, player, player1, player2) == true)
                return 1;

            input[1] = input[1] + 2;
            if (mov(input, board, playerShips, player, player1, player2) == true)
                return 1;
        }
        return 0;
    case 4 : // постріл квадратом
        res = mov(input, board, playerShips, player, player1, player2);
        if (res == -1){
            return -1;
        }

        input[1] = input[1] - 1;
        if (mov( input, board, playerShips, player, player1, player2) == true)
            return 1;
        input[1] = input[1] + 2;
        if (mov(input, board, playerShips, player, player1, player2) == true)
            return 1;

        input[0] = input[0] - 1;
        input[1] = input[1] - 1;
        if (mov(input, board, playerShips, player, player1, player2) == true)
            return 1;

        input[1] = input[1] - 1;
        if (mov(input, board, playerShips, player, player1, player2) == true)
            return 1;
        input[1] = input[1] + 2;
        if (mov(input, board, playerShips, player, player1, player2) == true)
            return 1;

        input[0] = input[0] + 2;

        if (mov(input, board, playerShips, player, player1, player2) == true)
            return 1;
        input[1] = input[1] - 1;
        if (mov(input, board, playerShips, player, player1, player2) == true)
            return 1;
        input[1] = input[1] - 1;
        if (mov(input, board, playerShips, player, player1, player2) == true)
            return 1;
        return 0;
    case 5: // постріл хрестом
        res = mov(input, board, playerShips, player, player1, player2);
        if (res == -1){
            return -1;
        }

        input[1] = input[1] - 1;
        if (mov(input, board, playerShips, player, player1, player2) == true)
            return 1;

        input[1] = input[1] + 2;
        if (mov(input, board, playerShips, player, player1, player2) == true)
            return 1;

        input[0] = input[0] - 1;
        input[1] = input[1] - 1;
        if (mov(input, board, playerShips, player, player1, player2) == true)
            return 1;

        input[0] = input[0] + 2;
        if (mov(input, board, playerShips, player, player1, player2) == true)
            return 1;

        return 0;
    }
}

void moving::bot_mov(Board &board, std::vector<typeShip> &playerShips, playerBoards &player1, bool shot, int prevHitRow, int prevHitCol) {
    static std::set<std::pair<int, int>> checkedCoordinates; // Відстеження перевірених координат

    string input(2, ' ');

    if (shot) {
        // Якщо попередній хід був влучним, звузимо радіус наступного удару
        int offset = 1;

        // Зменшення діапазону випадкових значень на основі попередніх координат попадання
        int startRow = std::max(0, prevHitRow - offset);
        int endRow = std::min(9, prevHitRow + offset);
        int startCol = std::max(0, prevHitCol - offset);
        int endCol = std::min(9, prevHitCol + offset);

        // Генерація випадкових координат із урахуванням звуження
        int row = startRow + rand() % (endRow - startRow + 1);
        int col = startCol + rand() % (endCol - startCol + 1);

        input[0] = static_cast<char>('A' + row);
        input[1] = static_cast<char>('0' + col);
    } else {
        // Якщо попередній хід був промахом, генеруємо випадкові координати, як зазвичай
        input[0] = static_cast<char>('A' + rand() % 10);
        input[1] = static_cast<char>('0' + rand() % 10);
    }

    int row = input[0] - 'A';
    int col = input[1] - '0';

    if ((player1.intBoard[row][col] == -1) || (player1.intBoard[row][col] == 6)) {
        player1.intBoard[row][col] = 7;
        player1.charBoard[row][col] = 'o'; // Ознака промаху на полі суперника
        shot = false; // Reset shot to 0 on a miss
    } else if (player1.intBoard[row][col] < 6 && player1.intBoard[row][col] >0 ) {


        player1.intBoard[row][col] = 0; // Ознака попадання
        player1.charBoard[row][col] = '+'; // Ознака попадання на полі суперника
        shot = 1;
        prevHitRow = row;
        prevHitCol = col;
        endgame(player1.intBoard );
    }
    else if (player1.intBoard[row][col] == 0 || player1.intBoard[row][col] == 7)
    {
        shot = 0;
    }

    if (shot){
        if (zona(input, playerShips, player1.intBoard, player1.charBoard) != 1){
            bot_mov(board , playerShips, player1, shot, prevHitRow, prevHitCol);
        }
        else
            bot_mov(board , playerShips, player1, 0, prevHitRow, prevHitCol);
    }
}

int moving::mov(string input, Board &board, std::vector<typeShip> &playerShips, int player, playerBoards &player1, playerBoards &player2){
    input[0] = toupper(input[0]);
    int row = input[0] - 'A';
    int col = input[1] - '0';

    if ((player2.intBoard[row][col] == -1) || (player2.intBoard[row][col] == 6 ) ){
        player2.intBoard[row][col] = 7;
        player2.charBoard[row][col] = 'o'; // Ознака промаху на полі суперника
        return 0;
    }
    else if ((player2.intBoard[row][col] == 0) || (player2.intBoard[row][col] == 7 )){
        return -1;
    }
    else {
        zona(input, playerShips, player2.intBoard, player2.charBoard);

        player2.intBoard[row][col] = 0; // Ознака попадання
        player2.charBoard[row][col] = '+'; // Ознака попадання на полі суперника
        return 1;
    }
}
