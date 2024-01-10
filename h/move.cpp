#include "set.h"
#include "move.h"
#include <iostream>
#include <thread>

using std::string, std::cin, std::cout;

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
        if (row > -1){ // ���� ������ ���� ������� �� ���� �� ���� �����
            IntBoard[row][col] = 6;
            CharBoard[row][col] = 'o';
        }
        if (row+ shipType +1 < boardSize){
            IntBoard[row+ shipType +1][col] = 6;
            CharBoard[row+  shipType +1][col] = 'o';
        }
        for (int i = 0; i !=  shipType + 2; i++){
            if (col - 1 > -1){
                if (row + i < boardSize && row + i > -1 ){
                    IntBoard[row+i][col -1 ] = 6;
                    CharBoard[row+i][col -1] = 'o';
                }
            }
            if (col + 1 < boardSize ){
                if (row + i < boardSize && row + i > -1){
                    IntBoard[row+i][col +1 ] = 6;
                    CharBoard[row+i][col +1] = 'o';
                }
            }
        }
    }
    else{
        col--;
        if (col > -1){ // ���� ���� ���� ������� �� ���� �� ���� �����
            IntBoard[row][col] = 6;
            CharBoard[row][col] = 'o';
        }
        if (col+ shipType +1 < boardSize){ // ���� ������ ���� ������� �� ���� �� ���� �����
            IntBoard[row][col+ shipType +1] = 6;
            CharBoard[row][col+  shipType +1] = 'o';
        }
        for (int i = 0; i !=  shipType + 2; i++){ // ������� �������� ������� ������
            if (row - 1 > -1){ // ���� ������ ���� ��� �����
                if (col + i > -1 && col + i < boardSize){
                    IntBoard[row-1][col +i ] = 6;
                    CharBoard[row-1][col +i] = 'o';
                }
            }
            if (row + 1 < boardSize){ // ������� �������� ������� �����
                if (col + i < boardSize && col + i > -1){ // ���� ����� ���� ��� �����
                    IntBoard[row+1][col +i ] = 6;
                    CharBoard[row+1][col +i] = 'o';
                }
            }
        }
    }
}
bool moving::zona(string input, std::vector<typeShip> &playerShips, int IntBoard[boardSize][boardSize], char CharBoard[boardSize+1][boardSize+1] ) {
    for (auto &ship : playerShips) {
        for ( auto &coord : ship.placement) {
            // ��������� ����� ���������� ������� � �������� ���������
            if (coord == input) {
                // �������� HP �������
                ship.HP --;
                cout << "HP �������: " << ship.HP << "/" << ship.shipType << '\n' ;
                cout << "������: " << ship.direction << '\n'  ;
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

void moving::addPlus(){

}

bool moving::mov_cout(Board &board, std::vector<typeShip> &playerShips, int player, playerBoards &player1, playerBoards &player2){
    setting settings;
    string input;
    int shotType = 1;
    cout << "������� " << player << ", ��� ���." << '\n';
    cout << "����� ���������" << '\n';
    board.print_board(player2.charBoard);
    cout << "" << '\n';
    cout << "���� �����:" << '\n';
    board.print_board(player1.charBoard);

    cout << "������ ���������� ����� (����� ����� � �������): "<< '\n';
    cin >> input;

    // �������� ����������� �������� ��������� � ������ ����
    while (valid_move(input, player2.charBoard) == 0){
            cout << "����� ����������. ��������� �� ���." << '\n';
              input = settings.retryInput();
        }
    cout << "������ ��� �������: " << '\n';
    cin >> shotType;
    while (shotType < 1|| shotType > 5){
            cout << "������� ��� �������. ������ ����� �� 1 �� 4." << '\n';
              shotType = settings.retryInt();
        }
    switch (shotType) {
    case 1:
        mov(shotType, input, board, playerShips, player, player1, player2);
        break;
    case 2: // ������ ����� �����
        for (int i = 0; i < 10; i++) {
            input[1] = (i + 48);
            mov(shotType, input, board, playerShips, player, player1, player2);
        }
        break;
    case 3: // ������ ������ 3 �� 1
        for (int i = 0; i < 1; i++) {
            mov(shotType, input, board, playerShips, player, player1, player2);
            input[1] = input[1] - 1;
            mov(shotType, input, board, playerShips, player, player1, player2);
            input[1] = input[1] + 2;
            mov(shotType, input, board, playerShips, player, player1, player2);
        }
        break;
    case 4 : // ������ ���������
        mov(shotType, input, board, playerShips, player, player1, player2);
        input[1] = input[1] - 1;
        mov(shotType, input, board, playerShips, player, player1, player2);
        input[1] = input[1] + 2;
        mov(shotType, input, board, playerShips, player, player1, player2);

        input[0] = input[0] - 1;
        input[1] = input[1] - 1;
        mov(shotType, input, board, playerShips, player, player1, player2);

        input[1] = input[1] - 1;
        mov(shotType, input, board, playerShips, player, player1, player2);
        input[1] = input[1] + 2;
        mov(shotType, input, board, playerShips, player, player1, player2);

        input[0] = input[0] + 2;

        mov(shotType, input, board, playerShips, player, player1, player2);
        input[1] = input[1] - 1;
        mov(shotType, input, board, playerShips, player, player1, player2);
        input[1] = input[1] - 1;
        mov(shotType, input, board, playerShips, player, player1, player2);
        break;
    case 5: // ������ �������
        mov(shotType, input, board, playerShips, player, player1, player2);
        input[1] = input[1] - 1;
        mov(shotType, input, board, playerShips, player, player1, player2);
        input[1] = input[1] + 2;
        mov(shotType, input, board, playerShips, player, player1, player2);

        input[0] = input[0] - 1;
        input[1] = input[1] - 1;
        mov(shotType, input, board, playerShips, player, player1, player2);

        input[0] = input[0] + 2;
        mov(shotType, input, board, playerShips, player, player1, player2);
        break;
}

    if (endgame(player2.intBoard) == 1)
    {
        system("cls");
        cout << "����� ���������" << '\n';
        board.print_board(player2.charBoard);
        cout << "" << '\n';
        cout << "���� �����:" << '\n';
        board.print_board(player1.charBoard);
        cout << "" << '\n';
        cout << " ������� ����� " << player << " ������ " ;
        exit(30);
    }
      system("cls");

    }

void moving::bot_mov(Board &board, std::vector<typeShip> &playerShips, playerBoards &player1, bool shot, int prevHitRow, int prevHitCol) {
    string input;
    if (shot) {
        // ���� ��������� ��� ��� �������, ������� ����� ���������� �����
        int offset = 1;

        // ��������� �������� ���������� ������� �� ����� ��������� ��������� ���������
        int startRow = std::max(0, prevHitRow - offset);
        int endRow = std::min(9, prevHitRow + offset);
        int startCol = std::max(0, prevHitCol - offset);
        int endCol = std::min(9, prevHitCol + offset);

        // ��������� ���������� ��������� �� ����������� ��������
        int row = startRow + rand() % (endRow - startRow + 1);
        int col = startCol + rand() % (endCol - startCol + 1);

        input[0] = static_cast<char>('A' + row);
        input[1] = static_cast<char>('0' + col);
    } else {
        // ���� ��������� ��� ��� ��������, �������� �������� ����������, �� ��������
        input[0] = static_cast<char>('A' + rand() % 10);
        input[1] = static_cast<char>('0' + rand() % 10);
    }

    input[0] = toupper(input[0]);

    int row = input[0] - 'A';
    int col = input[1] - '0';

    if ((player1.intBoard[row][col] == -1) || (player1.intBoard[row][col] == 6)) {
        player1.intBoard[row][col] = 6;
        player1.charBoard[row][col] = 'o'; // ������ ������� �� ��� ���������
        shot = false; // Reset shot to false on a miss
    } else {
        zona(input, playerShips, player1.intBoard, player1.charBoard);
        player1.intBoard[row][col] = 0; // ������ ���������
        player1.charBoard[row][col] = '+'; // ������ ��������� �� ��� ���������
        shot = true;
        prevHitRow = row;
        prevHitCol = col;
        endgame(player1.intBoard );
    }

    if (shot){
        if (zona(input, playerShips, player1.intBoard, player1.charBoard) != 1){
            bot_mov(board , playerShips, player1, shot, prevHitRow, prevHitCol);
        }
        else
            bot_mov(board , playerShips, player1, 0, prevHitRow, prevHitCol);
    }
}

bool moving::mov(int shotType, string input, Board &board, std::vector<typeShip> &playerShips, int player, playerBoards &player1, playerBoards &player2){
    bool k = 0;
           input[0] = toupper(input[0]);
            int row = input[0] - 'A';
            int col = input[1] - '0';

    if (((input[0] >= 'A' && input[0] <= 'J') && (input[1] >= '0' && input[1] <= '9')) ==0 ) {
        return 0;
    }

    if ((player2.intBoard[row][col] == -1) || (player2.intBoard[row][col] == 6 ) ){
        player2.intBoard[row][col] = 6;
        player2.charBoard[row][col] = 'o'; // ������ ������� �� ��� ���������
    } else {

        zona(input, playerShips, player2.intBoard, player2.charBoard);
        player2.intBoard[row][col] = 0; // ������ ���������
        player2.charBoard[row][col] = '+'; // ������ ��������� �� ��� ���������
        k = 1;
    }
    if (shotType ==1)
    {
        if (k == 1)
            mov_cout(board, playerShips, player, player1, player2);
        }
}
