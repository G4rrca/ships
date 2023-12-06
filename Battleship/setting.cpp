#include "setting.h"
#include <iostream>
#include <thread>

using std::string, std::cout, std::cin;
bool setting::canPlaceShip(int shipType, int row, int col, char direction, int board[10][10]) {
    // �������� �� �������� �������� �� �����

    // ���� ��������� ����������� - ��������� ���������� ����, �� ������� �������
    if (direction == 'V'){
        for (int d = 0; d < shipType; d++) {
            if (board[row+d][col] != -1) // ���� � ������� �� ��������, �� ��������� false
                return false;
        }
        if (row + shipType > 10){ // ���� �������� �������� �� ��� �����
            return false;
        }
        return true;
    }

    // ���� ��������� ������������� - ���������� ������ ����
    for (int d = 0; d < shipType; d++) {
        if (board[row][col + d] != -1) // ���� � ������� �� ��������, �� ��������� false
            return false;
    }
    if (col + shipType > 10) { // ���� �������� �������� �� ��� �����
        return false;
    }
    return true;
}

string setting::retryInput() {
    string number;
    cout << "������ ����� ������: ";
    cin >> number;
    return number;
}

bool setting::valid_set(string& number, int q1[5], int board[10][10], char board1[11][11], bool human) {
    char ship_typ = number[0];  // ��� ������� = ������� ��������� ������� ��� ����������� �������
    char ro = number[1]; // ����� - ������ ������ (�����)
    char co = number[2]; // ������� - ����� ������ (�����)
    char direction = number[3]; // ������ - ��������� ������ (V �� H)

    // ����������� � ������� ��������
    int row = ro - 'A';
    int col = co - '0';
    int ship_type = ship_typ - '0';

    while (true) {
        // ���� ���������� 0 ������� ������� ����
        if (q1[ship_type - 1] == 0) {
            cout << "����������� ";
            switch (ship_type) {
                case 1:
                    cout << "�������";
                    break;
                case 2:
                    cout << "��������";
                    break;
                case 3:
                    cout << "��������";
                    break;
                case 4:
                    cout << "����";
                    break;
                case 5:
                    cout << "���������";
                    break;
            }
            '\n';
            return false;
        }

        if (!canPlaceShip(ship_type, row, col, direction, board)) { // ���� �������� ��������, ��
            if (human ==1){ //���� �������� ������������ �������

                // �������� �������� �����
                number = retryInput();

                // ����������� ����� ���� � �����
                number[1] = toupper(number[1]);
                number[3] = toupper(number[3]);

                // ������� ������ ��� ���������� ������������
                ship_typ = number[0];
                ro = number[1];  row = ro - 'A';
                co = number[2];  col = co - '0';
                direction = number[3];
                ship_type = ship_typ - '0';
            }

            // ���� ������ �������������� ���������, �� ������ ��������� 0 ��� �������� ���������
            else{
                return 0;
            }

        } else {
            break;
        }
    }

    // ��� �������������� ��������
    if ( direction == 'V'){
        // ������������ ���� ������� �������
        for (int i = col - 1; i <= col + 1; i++) {
            for (int j = row - 1; j <= row + ship_type; j++) {
                if (i >= 0 && i < 10 && j >= 0 && j < 10) {
                    board[j][i] = 6;
                }
            }
        }
        // ������������ ������ ������� �� ������
        for (int d = 0; d < ship_type; d++) {
            board[row+d][col] = ship_type;
        }
        for (int d = 0; d < ship_type; d++) {
            board1[row+d][col] = '+';
        }
    }

    // ��� ��������������� ��������
    else{
        // ������������ ���� ������� �������
        for (int i = row - 1; i <= row + 1; i++) {
            for (int j = col - 1; j <= col + ship_type; j++) {
                if (i >= 0 && i < 10 && j >= 0 && j < 10) {
                    board[i][j] = 6;
                }
            }
        }
        // ������������ ������ ������� �� ������
        for (int d = 0; d < ship_type; d++) {
            board[row][col + d] = ship_type;
        }
        for (int d = 0; d < ship_type; d++) {
            board1[row][col + d] = '+';
        }
    }
    q1[ship_type - 1]--; // ��������� ���������� ������� �� ������ ���������
    return true;
}

void setting::sett(int player, Board &board){
    string number; int board3[10][10]; char board33[11][11]; int ship_type; int ship[5]; char direction;
    for (int r = 0; r < 10; r++) {
        do {
            // ��� ������� ��������� �� �������� ������, �������������� ��������� ����� �������� �� ������ ������
             if (player == 1) {
                memcpy(board3, board.board1, sizeof(board3));
                memcpy(board33, board.board11, sizeof(board33));
                memcpy(ship, board.p1, sizeof(ship));

            } else {
                memcpy(board3, board.board2, sizeof(board3));
                memcpy(board33, board.board22, sizeof(board33));
                memcpy(ship, board.p2, sizeof(ship));
            }
             system("cls");
            for (int t = 0; t < 1; t++) {
                  "/n";
                cout << "        ������� ����� " << player << "/n";
                cout << "        ��������� ������:" << "/n";
                cout << " ��������� - ����� 5x1 (" << ship[4] << " ��.)" << "/n";
                cout << " ������� - ����� 3x1 (" << ship[2] << " ��.)" << "/n";
                cout << " ϳ������� ����� - ����� 2x1 (" << ship[1] << " ��.)" << "/n";
                cout << " ������� - ����� 1x1 (" << ship[0] << " ��.)" << "/n" << "\n";
                cout << " ������ ����������� �� ����������, ������ ���������� �� ���� �������� ���� ���� ����� " << "/n";
            }
            board.print_board(board33);
            cin >> number;
             system("cls");

            number[1] = toupper(number[1]);
            number[3] = toupper(number[3]);
            direction = number[3];

            if (direction != 'V' && direction != 'H')
            {
                cout << "������� ������" << "/n";
                cout << "������ �������� ��������" << "/n";
                std::this_thread::sleep_for(std::chrono::seconds(3));
            }
            if (ship_type < 1 || ship_type > 5 || ship_type ==4) {
                cout << "������� ��� �������" << "/n";
                cout << "������ �������� ��������" << "/n";
                std::this_thread::sleep_for(std::chrono::seconds(3));
            }  else {
                valid_set(number, ship, board3, board33, 1);
                system("cls");
            }

        // ���� ���������� ���� ������ �������� �������� �� ������� � ��������
        } while (ship_type < 1 || ship_type > 5 || (direction != 'V' && direction != 'H') );

        // ���������� ��������� ��� ����� � ������� ��� ������� �����
         if (player == 1) {
                memcpy(board.board1, board3,  sizeof(board.board1));
                memcpy(board.board11, board33,  sizeof(board.board11));
                memcpy(board.p1, ship, sizeof(board.p1));
            } else {
                memcpy(board.board2, board3,  sizeof(board.board2));
                memcpy(board.board22, board33,  sizeof(board.board22));
                memcpy(board.p2, ship, sizeof(board.p2));
        }
    }
}

void setting::bot_sett(int player, Board &board) {
    string number;
    int board3[10][10];
    char board33[11][11];
    int ship_type;
    int ship[5];

    if (player == 1) {
        memcpy(board3, board.board1, sizeof(board3));
        memcpy(board33, board.board11, sizeof(board33));
        memcpy(ship, board.p1, sizeof(ship));
    } else {
        memcpy(board3, board.board2, sizeof(board3));
        memcpy(board33, board.board22, sizeof(board33));
        memcpy(ship, board.p2, sizeof(ship));
    }
    int iterations = 0;
    do {

        // ����� �� 1 �� 5 �������������� �� ������ '1' �� '5'
        if (ship[4] != 0) {
            number[0] = static_cast<char>(53);
        } else if (ship[3] != 0) {
            number[0] = static_cast<char>(52);
        } else if (ship[2] != 0) {
            number[0] = static_cast<char>(51);
        } else if (ship[1] != 0) {
            number[0] = static_cast<char>(50);
        } else if (ship[0] != 0) {
            number[0] = static_cast<char>(49);
        }

        // ���������� ���� ���������
        number[1] = static_cast<char>('A' + rand() % 10);  // ��������� ����� �� 'A' �� 'J'
        number[2] = static_cast<char>((rand() % 10) + 48);  // ����� �� 0 �� 9 �������������� �� ������ '0' �� '9'

        int randomValue = std::rand() % 2;

        // ���������� ���� �������� �������
        if (randomValue == 0) {
            number[3] = 'H';
        } else {
            number[3] = 'V';
        }

        // ������������� ����� � �����
        int row = number[1] - 'A';

        // ������������� ����� � char � int
        int col = number[2] - '0';

        // ������������� ���� ������� � char � int
        ship_type = number[0] - '0';
         iterations++;
        if (valid_set(number, ship, board3, board33, 0) == 0) {
            // ���� ����������� �����������, ��������� ����

            continue;
        }

        // ���������, �� �� ������ ������� ���������
        bool allShipsPlacedCorrectly = true;
        for (int i = 0; i < 5; ++i) {
            if (ship[i] != 0) {
                allShipsPlacedCorrectly = false;
                break;
            }
        }

        // ���� �� ������ ������� ���������, ��������� ����
        if (allShipsPlacedCorrectly) {
            break;
        }

    } while (true);
//    cout << "Iterations: " << iterations << '\n';
     if (player == 1) {
        memcpy(board.board1, board3,  sizeof(board.board1));
        memcpy(board.board11, board33,  sizeof(board.board11));
        memcpy(board.p1, ship, sizeof(board.p1));
    } else {
        memcpy(board.board2, board3,  sizeof(board.board2));
        memcpy(board.board22, board33,  sizeof(board.board22));
        memcpy(board.p2, ship, sizeof(board.p2));
    }
}
