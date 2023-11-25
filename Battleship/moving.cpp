#include "setting.h"
#include "moving.h"
#include <iostream>
#include <thread>

using namespace std;

bool moving::valid_move(string number, char board[11][11]){ //+
    number[0] = toupper(number[0]);
    char ro = number[0];
    char co = number[1];
    int row = ro - 'A';
    int col = co - '0';
    if (number.length() != 2){
        return 0;
    }

    if (board[row][col] == '+' || board[row][col] == 'o' ){
        return 0;
    } else
        return 1;
}

bool moving::zona( int row, int col, int board2[10][10], char board22[11][11]){
 int k = 1;
   int ship_type = board2[row][col];

    while (1==1){ // �������� ���� �� ��������� 0 �� 1

         if (board22[row+1][col] == '+' || board22[row-1][col] == '+' || (0 < board2[row+1][col] && board2[row+1][col] < 6) || (0 < board2[row-1][col] && board2[row-1][col] < 6)) {
            cout << "board22[row+1][col] = " << board22[row+1][col] << endl;
            cout << "board22[row-1][col] = " << board22[row-1][col] << endl;
             cout << "board2[row+1][col] = " << board2[row+1][col] << endl;
            cout << "board2[row-1][col] = " << board2[row-1][col] << endl;


            k = 10;
        }

        if (k > 0 && k < 10){ // �������� ������, �� ������ �� ����� ������ �������

            if (col+k > 9){ // ���� ������ ������� � ���� ����� �� ���������� ����
                k = -1; // �� ����� ��� ������� �� �������� ����
                }
            else // ���� ������ ������� �� ���� ����� ���������� �� � ��� �

                // ���� ��� �� ��������� (0) �� ����� ������� (6) (���� �� ������ ��� ��������� �������)
                if (board2[row][col+k] != 6  && board2[row][col+k] != 0){
                    return 0; // �������� �� ���������, � ���� �� ����� ���� ��������� �����
                }
                else if (board2[row][col+k] == 6){ // ���� ������ ���� ������ ��� ���������
                    k = -1; // ���������� � ��� �������
                }
                else // ���� � ��� ��������� � ��������
                    k++; // ���������� ��� ���� �������� �������� ������
                }
        else if (k < 0) { // �������� ����

            // ���� ���� �� ������� ���� ����� �� ����� ������� �� �������� �������� �����
            if (col+k < 0 || board2[row][col+k] == 6){
                col = col + k ; // ��� ��������
                if (col > -1){ // ���� ���� ���� ������� �� ���� �� ���� �����
                    board2[row][col] = 6;
                    board22[row][col] = 'o';
                }
                if (col+ship_type +1 < 10){ // ���� ������ ���� ������� �� ���� �� ���� �����
                    board2[row][col+ship_type +1] = 6;
                    board22[row][col+ ship_type +1] = 'o';
                }
                for (int i = 0; i != ship_type + 2; i++){ // ������� �������� ������� ������
                    if (row - 1 > -1){ // ���� ������ ���� ��� �����
                        if (col + i > -1 && col + i < 10){
                            board2[row-1][col +i ] = 6;
                            board22[row-1][col +i] = 'o';
                        }
                    }
                    if (row + 1 < 10){ // ������� �������� ������� �����
                        if (col + i < 10 && col + i > -1){ // ���� ����� ���� ��� �����
                            board2[row+1][col +i ] = 6;
                            board22[row+1][col +i] = 'o';
                        }
                    }
                }
                return 1; // ��������� ���� ���������
            }

            // ���� ���� �� ����� ����, � �������� ������� � ��� �� �� ��������
            if (board2[row][col+k] != 6 && board2[row][col+k] != 0){
                return 0; // �������� �� ��������� ���� ���� �� �������
            }

            // ���� ���� � ��������� � �������� ���������� �� ���� �������
            else
                k--;
        }
        else {
            k = 1;
            while (1==1){

                  if (k > 0){ // �������� ����
            if (row+k > 9){ // ���� ����� ������� � ���� ����� �� ���������� �����
                k = -1; // �� ����� ��� ������� �� �������� �����
                }
            else // ���� ����� ������� �� ���� ����� ���������� �� � ��� �

                // ���� ��� �� ��������� (0) �� ����� ������� (6) (���� �� ������ ��� ��������� �������)
                if (board2[row+k][col] != 6  && board2[row+k][col] != 0){
                    return 0; // �������� �� ���������
                }
                else if (board2[row+k][col] == 6){ // ���� ����� ���� ������ ��� ���������
                    k = -1; // ���������� � ��� �������
                }
                else // ���� � ��� ��������� � ��������
                    k++; // ���������� ��� ���� �������� �������� ������
                }
        else if (k < 0) { // �������� ����

            // ���� ������ �� ������� ���� ����� �� ����� ������� �� �������� �������� �����
            if (row+k < 0 || board2[row+k][col] == 6){
                row = row + k ; // ��� ��������
                if (row > -1){ // ���� ������� ���� ������� �� ���� �� ���� �����
                    board2[row][col] = 6;
                    board22[row][col] = 'o';
                }
                if (row+ship_type +1 < 10){ // ���� ������ ���� ������� �� ���� �� ���� �����
                    board2[row+ship_type +1][col] = 6;
                    board22[row+ ship_type +1][col] = 'o';
                }
                for (int i = 0; i != ship_type + 2; i++){
                    if (col - 1 > -1){
                        if (row + i < 10   && row + i > -1  ){
                            board2[row+i][col -1 ] = 6;
                            board22[row+i][col -1] = 'o';
                        }
                    }
                    if (col + 1 < 10 ){
                        if (row + i < 10  && row + i > -1 ){
                            board2[row+i][col +1 ] = 6;
                            board22[row+i][col +1] = 'o';
                        }
                    }
                }
                return 1;
            }
            if (board2[row+k][col] != 6 && board2[row+k][col] != 0){
                return 0;
            }
            else
                k--;
        }
            }
        }
    }

}

void moving::endgame(int board33[10][10], char board3[11][11]){ //+
    int moves = 0;
     for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            if (board33[i][j] == 1 ||  board33[i][j] == 2 || board33[i][j] == 3 || board33[i][j] == 4 || board33[i][j] == 5 )
                moves ++;
        }
    }
    if (moves == 0){
         for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 11; j++) {
                 cout << board3[i][j] << " ";
            }
             cout << endl;
        }
        cout << "³���, �� ����� ������� �������� �������� ���������!" << endl;
        cout << "��� ���������" << endl;
        exit(0);
    }
}

bool moving::mov(int player, Board &board){
    setting settings;
    string number; int board3[10][10]; char board33[11][11]; char board44[11][11]; int board4[10][10];  bool k = 0;
    if (player == 1) {
        memcpy(board3, board.board2, sizeof(board3));
        memcpy(board4, board.board1, sizeof(board4));
        memcpy(board33, board.board22, sizeof(board33));
        memcpy(board44, board.board11, sizeof(board44));

    } else {
        memcpy(board4, board.board2, sizeof(board4));
        memcpy(board3, board.board1, sizeof(board3));
        memcpy(board33, board.board11, sizeof(board33));
        memcpy(board44, board.board22, sizeof(board44));
    }
    cout << "������� " << player << ", ��� ���." << endl;
    cout << "����� ���������" << endl;
    board.print_board(board33);
    cout << "" << endl;
//    board.print_board(board3);
//      cout << "" << endl;

    cout << "���� �����:" << endl;
    board.print_board(board44);
//      cout << "" << endl;
//    board.print_board(board4);
//      cout << "" << endl;

    cout << "������ ���������� ����� (����� ����� � �������): ";
    cin >> number;


    // �������� ����������� �������� ��������� � ������ ����
    while (valid_move(number, board33) == 0){
            cout << "������ ����������. ��������� �� ���." << endl;
              number = settings.retryInput();
        }
      system("cls");
         number[0] = toupper(number[0]);

            char ro = number[0];
            char co = number[1];
            int row = ro - 'A';
            int col = co - '0';

    if ((board3[row][col] == -1) || (board3[row][col] == 6 ) ){
        cout << "������!" << endl;
        board3[row][col] = 6;
        board33[row][col] = 'o'; // ������ ������� �� ��� ���������
    } else {
        cout << "���������!" << endl;
        zona(row, col, board3, board33);
        board3[row][col] = 0; // ������ ���������
        board33[row][col] = '+'; // ������ ��������� �� ��� ���������
        k = 1;
        endgame(board3, board33);
    }

    if (player == 1) {
        memcpy(board.board2, board3,  sizeof(board3));
        memcpy(board.board22, board33,  sizeof(board33));
    } else {
        memcpy(board.board1, board3,  sizeof(board3));
        memcpy(board.board11, board33,  sizeof(board33));
    }
    if (k == 1)
        mov(player,board);
    }

void moving::bot_mov(int player, Board &board, bool shot, int prevHitRow, int prevHitCol) {
    string number;
    int board3[10][10];
    char board33[11][11];

    if (player == 1) {
        memcpy(board3, board.board2, sizeof(board3));
        memcpy(board33, board.board22, sizeof(board33));
    } else {
        memcpy(board3, board.board1, sizeof(board3));
        memcpy(board33, board.board11, sizeof(board33));
    }

    if (shot) {
        // If the previous shot was a hit, narrow down the next shot
        int offset = 1;

        // Reduce the range of random values based on the previous hit coordinates
        int startRow = std::max(0, prevHitRow - offset);
        int endRow = std::min(9, prevHitRow + offset);
        int startCol = std::max(0, prevHitCol - offset);
        int endCol = std::min(9, prevHitCol + offset);

        // Generate random coordinates within the narrowed range
        int row = startRow + rand() % (endRow - startRow + 1);
        int col = startCol + rand() % (endCol - startCol + 1);

        number[0] = static_cast<char>('A' + row);
        number[1] = static_cast<char>('0' + col);
    } else {
        // If the previous shot was a miss, generate random coordinates as usual
        number[0] = static_cast<char>('A' + rand() % 10);
        number[1] = static_cast<char>('0' + rand() % 10);
    }

    number[0] = toupper(number[0]);

    int row = number[0] - 'A';
    int col = number[1] - '0';

    if ((board3[row][col] == -1) || (board3[row][col] == 6)) {
        cout << "������!" << endl;
        board3[row][col] = 6;
        board33[row][col] = 'o'; // ������ ������� �� ��� ���������
        shot = false; // Reset shot to false on a miss
    } else {
        cout << "���������!" << endl;
        zona(row, col, board3, board33);
        board3[row][col] = 0; // ������ ���������
        board33[row][col] = '+'; // ������ ��������� �� ��� ���������
        shot = true;
        prevHitRow = row;
        prevHitCol = col;
        endgame(board3, board33);
    }

    if (player == 1) {
        memcpy(board.board2, board3, sizeof(board3));
        memcpy(board.board22, board33, sizeof(board33));
    } else {
        memcpy(board.board1, board3, sizeof(board3));
        memcpy(board.board11, board33, sizeof(board33));
    }

    if (shot)
    {
        if (zona(row, col, board3, board33) != 1)
        {
            bot_mov(player, board, shot, prevHitRow, prevHitCol);
        }
        else
            bot_mov(player, board, 0, prevHitRow, prevHitCol);
    }

}

void moving::minuss(Board &board){
     for (int i = 0; i < 10; i++){ //+
            for (int j = 0; j < 10; j++){
                board.board11[i][j] = '-';
                board.board22[i][j] = '-';
               }
        }
}
