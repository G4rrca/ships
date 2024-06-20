#include "set.h"
#include "ships.h"
#include <iostream>
#include <QDebug>

using std::string, std::cout, std::cin, std::endl;

void convertInput(string input, int* ship_type, int* row, int* col, char* direction) {
    // конвертація малих букв у великі
    input[1] = toupper(input[1]);
    input[3] = toupper(input[3]);

    // перепис змінних для подальшого використання
    *ship_type = input[0] - '0';
    *row = input[1] - 'A';
    *col = input[2] - '0';
    *direction = input[3];
}

bool setting::canPlaceShip(int shipType, int row, int col, char direction, int board[boardSize][boardSize]) {
    // якщо розміження пертикальне - послідовно перевіряємо вниз, на довжину корабля
    if (direction == 'V'){
        for (int d = 0; d < shipType; d++) {
            if (board[row+d][col] != -1) // якщо у клітинці не порожньо, то повертаємо false
                return false;
        }
        if (row + shipType > boardSize){ // якщо корабель виходить за межі дошки
            return false;
        }
        return true;
    }

    // якщо розміження горизонтальне - перевіряємо правий край
    for (int d = 0; d < shipType; d++) {
        if (board[row][col + d] != -1) // якщо у клітинці не порожньо, то повертаємо false
            return false;
    }
    if (col + shipType > boardSize) { // якщо корабель виходить за межі дошки
        return false;
    }
    return true;
}


bool setting::valid_set(int num, string& input, int ships[5],
    int board[boardSize][boardSize], char board1[boardSize + 1][boardSize + 1], Ship &ship) {
    int row = input[1] - '0';
    int col = input[2] - '0' ;
    int ship_type = input[0] - '0';
    char direction = input[3] ;

    std::vector<string> placement;
    if (ships[ship_type - 1] == 0) {
        cout << "Not enough ";
        switch (ship_type) {
        case 1:
            cout << "esminci"<< endl;
            break;
        case 2:
            cout << "underwater"<< endl;
            break;
        case 3:
            cout << "cruiser"<< endl;
            break;
        case 4:
            cout << "ssas" << endl;
            break;
        case 5:
            cout << "planeship" << endl;
            break;
        }
        return false;
    }
    if (!canPlaceShip(ship_type, row, col, direction, board)) { // якщо корабель вміщається, то
        return 0;
    }

    // при вертикальному розміщенні
    if ( direction == 'V'){
        // Встановлення зони навколо корабля
        for (int i = col - 1; i <= col + 1; i++) {
            for (int j = row - 1; j <= row + ship_type; j++) {
                if (i >= 0 && i < boardSize && j >= 0 && j < boardSize ) {
                    board[j][i] = 6;
                }
            }
        }
        // Встановлення самого корабля на дошках
        for (int d = 0; d < ship_type; d++) {
            board[row+d][col] = ship_type;
        }
        for (int d = 0; d < ship_type; d++) {
            board1[row+d][col] = '+';
            char letter = static_cast<char>('A' + row+d);
            string coordinate = letter + std::to_string(col);
            placement.push_back(coordinate);
        }
    }
    else{
        // Встановлення зони навколо корабля
        for (int i = row - 1; i <= row + 1; i++) {
            for (int j = col - 1; j <= col + ship_type; j++) {
                if (i >= 0 && i < boardSize && j >= 0 && j < boardSize) {
                    board[i][j] = 6;
                }
            }
        }
        // Встановлення самого корабля на дошках
        for (int d = 0; d < ship_type; d++) {
            board[row][col + d] = ship_type;
        }
        for (int d = 0; d < ship_type; d++) {
            board1[row][col + d] = '+';
            char letter = static_cast<char>('A' + row );
            string coordinate = letter + std::to_string(col+d);
            placement.push_back(coordinate);
        }

    }
    ships[ship_type - 1]--;

    ship.addShip(num, ship_type, placement, direction, ship);

    return true;
}

void setting::sett(playerBoards &player, playerShips &ships, Board &board, Ship &ship, string input){
    valid_set(player.playerNumber, input, ships.pShips, player.intBoard, player.charBoard, ship);
}

void setting::bot_sett(playerBoards &player, playerShips &ships,  Board &board, Ship &ship) {
    std::string input;

    do {
        // число від 1 до 5 перетворюється на символ '1' до '5'
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

        // випадковий вибір координат

        input += static_cast<char>((rand() % boardSize) + 48);  // число від 0 до 9 перетворюється на символ '0' до '9'
        input += static_cast<char>((rand() % boardSize) + 48);
        int randomValue = std::rand() % 2;

        // випадковий вибір напрямку корабля
        if (randomValue == 0) {
            input += 'H';
        } else {
            input += 'V';
        }

        if (valid_set(ships.pNumber, input, ships.pShips, player.intBoard, player.charBoard, ship) == 0) {
            continue;
        }

        // Перевірити, чи всі кораблі розміщені правильно
        bool allShipsPlacedCorrectly = true;
        for (int i = 0; i < 5; ++i) {
            if (ships.pShips[i] != 0) {
                allShipsPlacedCorrectly = false;
                break;
            }
        }

        // Якщо всі кораблі розміщені правильно, завершити цикл
        if (allShipsPlacedCorrectly) {
            break;
        }
    } while (true);
}
