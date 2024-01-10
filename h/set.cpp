#include "set.h"
#include "ships.h"
#include <iostream>
#include <thread>


using std::string, std::cout, std::cin;

void convertInput(string input, int* ship_type, int* row, int* col, char* direction) {
    // ����������� ����� ���� � �����
    input[1] = toupper(input[1]);
    input[3] = toupper(input[3]);

    // ������� ������ ��� ���������� ������������
    *ship_type = input[0] - '0';
    *row = input[1] - 'A';
    *col = input[2] - '0';
    *direction = input[3];
}

bool setting::canPlaceShip(int shipType, int row, int col, char direction, int board[boardSize][boardSize]) {
    // ���� ��������� ����������� - ��������� ���������� ����, �� ������� �������
    if (direction == 'V'){
        for (int d = 0; d < shipType; d++) {
            if (board[row+d][col] != -1) // ���� � ������� �� ��������, �� ��������� false
                return false;
        }
        if (row + shipType > boardSize){ // ���� �������� �������� �� ��� �����
            return false;
        }
        return true;
    }

    // ���� ��������� ������������� - ���������� ������ ����
    for (int d = 0; d < shipType; d++) {
        if (board[row][col + d] != -1) // ���� � ������� �� ��������, �� ��������� false
            return false;
    }
    if (col + shipType > boardSize) { // ���� �������� �������� �� ��� �����
        return false;
    }
    return true;
}

string setting::retryInput() {
    string input;
    cout << "������ ����� ������: ";
    cin >> input;
    return input;
}
int setting::retryInt()
{
    int input;
    cout << "������ ��� ������: ";
    cin >> input;
    return input;
}

bool setting::valid_set(int num, string& input, int ships[5],
        int board[boardSize][boardSize], char board1[boardSize + 1][boardSize + 1], bool human, Ship &ship) {
    int row, col, ship_type;
    int HP = ship_type;
    char direction;
    std::vector<string> placement;

    convertInput(input, &ship_type, &row, &col, &direction);

    while (true) {
        // ���� ���������� 0 ������� ������� ����
        if (ships[ship_type - 1] == 0) {
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
                input = retryInput();
                convertInput(input, &ship_type, &row, &col, &direction);
            }
            // ���� ������ �������������� ���������, �� ������ ��������� 0 ��� �������� ���������
            else{
                return 0;
            }
        } else {
            break;
        }
    }

    // ��� ������������� ��������
    if ( direction == 'V'){
        // ������������ ���� ������� �������
        for (int i = col - 1; i <= col + 1; i++) {
            for (int j = row - 1; j <= row + ship_type; j++) {
                if (i >= 0 && i < boardSize && j >= 0 && j < boardSize ) {
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

        char letter = static_cast<char>('A' + row + d );
        string coordinate = letter + std::to_string(col );
        placement.push_back(coordinate);
        }


    }

    // ��� ��������������� ��������
    else{
        // ������������ ���� ������� �������
        for (int i = row - 1; i <= row + 1; i++) {
            for (int j = col - 1; j <= col + ship_type; j++) {
                if (i >= 0 && i < boardSize && j >= 0 && j < boardSize) {
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

           char letter = static_cast<char>('A' + row );
        string coordinate = letter + std::to_string(col + d);
        placement.push_back(coordinate);
        }

    }
    ships[ship_type - 1]--; // ��������� ���������� ������� �� ������ ���������

    ship.addShip(num, ship_type, placement, direction, HP , ship);

    return true;
}

void setting::sett(playerBoards &player, playerShips &ships, Board &board, Ship &ship){
    string input; int ship_type, row, col;  char direction;
    for (int r = 0; r < 10; r++) {
        do {
             system("cls");
            ship.printShips(ships);
            board.print_board(player.charBoard);
            ship.printVector(ship.player1Ships);

            cin >> input;
             system("cls");
              convertInput(input, &ship_type, &row, &col, &direction);
            if (direction != 'V' && direction != 'H'){
                cout << "������� ������" << '\n';
                cout << "������ �������� ��������" << '\n';
                std::this_thread::sleep_for(std::chrono::seconds(3));
            }
            if (ship_type < 1 || ship_type > 5 || ship_type ==4) {
                    cout << ship_type << '\n';
                cout << "������� ��� �������" << '\n';
                cout << "������ �������� ��������" << '\n';
                std::this_thread::sleep_for(std::chrono::seconds(3));
            }  else {
                valid_set(player.playerNumber, input, ships.pShips, player.intBoard, player.charBoard, 1, ship);
               system("cls");
            }

        // ���� ���������� ���� ������ �������� �������� �� ������� � ��������
        } while (ship_type < 1 || ship_type > 5 || (direction != 'V' && direction != 'H') );
    }
}

void setting::bot_sett(playerBoards &player, playerShips &ships,  Board &board, Ship &ship) {
    std::string input;
    int ship_type, row, col;

    do {
        // ����� �� 1 �� 5 �������������� �� ������ '1' �� '5'
        if (ships.pShips[4] != 0) {
            input = "5";
        } else if (ships.pShips[3] != 0) {
            input = "4";
        } else if (ships.pShips[2] != 0) {
            input = "3";
        } else if (ships.pShips[1] != 0) {
            input = "2";
        } else if (ships.pShips[0] != 0) {
            input = "1";
        }

        // ���������� ���� ���������
        input += static_cast<char>('A' + rand() % boardSize);  // ��������� ����� �� 'A' �� 'J'
        input += static_cast<char>((rand() % boardSize) + 48);  // ����� �� 0 �� 9 �������������� �� ������ '0' �� '9'

        int randomValue = std::rand() % 2;

        // ���������� ���� �������� �������
        if (randomValue == 0) {
            input += 'H';
        } else {
            input += 'V';
        }

        if (valid_set(ships.pNumber, input, ships.pShips, player.intBoard, player.charBoard, 0, ship) == 0) {
            // ���� ����������� �����������, ��������� ����
            continue;
        }

        // ���������, �� �� ������ ������� ���������
        bool allShipsPlacedCorrectly = true;
        for (int i = 0; i < 5; ++i) {
            if (ships.pShips[i] != 0) {
                allShipsPlacedCorrectly = false;
                break;
            }
        }

        // ���� �� ������ ������� ���������, ��������� ����
        if (allShipsPlacedCorrectly) {
            break;
        }
    } while (true);
}
