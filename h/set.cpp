#include "set.h"
#include "ships.h"
#include <iostream>
#include <thread>


using std::string, std::cout, std::cin;

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

string setting::retryInput() {
    string input;
    cout << "Введіть число заново: ";
    cin >> input;
    return input;
}
int setting::retryInt()
{
    int input;
    cout << "Введіть тип заново: ";
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
        // якщо залишилося 0 кораблів якогось типу
        if (ships[ship_type - 1] == 0) {
            cout << "Недостатньо ";
            switch (ship_type) {
                case 1:
                    cout << "есмінців";
                    break;
                case 2:
                    cout << "підводних";
                    break;
                case 3:
                    cout << "крейсерів";
                    break;
                case 4:
                    cout << "барж";
                    break;
                case 5:
                    cout << "авіаносців";
                    break;
            }
            '\n';
            return false;
        }

        if (!canPlaceShip(ship_type, row, col, direction, board)) { // якщо корабель вміщається, то
            if (human ==1){ //якщо введення здійснювалося людиною
                input = retryInput();
                convertInput(input, &ship_type, &row, &col, &direction);
            }
            // якщо кораблі встановлюються випадково, то просто повеннути 0 для повторної генерації
            else{
                return 0;
            }
        } else {
            break;
        }
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

        char letter = static_cast<char>('A' + row + d );
        string coordinate = letter + std::to_string(col );
        placement.push_back(coordinate);
        }


    }

    // при горизонтальному розміщенні
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
        string coordinate = letter + std::to_string(col + d);
        placement.push_back(coordinate);
        }

    }
    ships[ship_type - 1]--; // вилучення розміщеного корабля із списку доступних

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
                cout << "Невірний напрям" << '\n';
                cout << "Введіть коректне значення" << '\n';
                std::this_thread::sleep_for(std::chrono::seconds(3));
            }
            if (ship_type < 1 || ship_type > 5 || ship_type ==4) {
                    cout << ship_type << '\n';
                cout << "Невірний тип корабля" << '\n';
                cout << "Введіть коректне значення" << '\n';
                std::this_thread::sleep_for(std::chrono::seconds(3));
            }  else {
                valid_set(player.playerNumber, input, ships.pShips, player.intBoard, player.charBoard, 1, ship);
               system("cls");
            }

        // цикл відбувається поки введені значення напрямку та корабля є валідними
        } while (ship_type < 1 || ship_type > 5 || (direction != 'V' && direction != 'H') );
    }
}

void setting::bot_sett(playerBoards &player, playerShips &ships,  Board &board, Ship &ship) {
    std::string input;
    int ship_type, row, col;

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
        input += static_cast<char>('A' + rand() % boardSize);  // випадкова буква від 'A' до 'J'
        input += static_cast<char>((rand() % boardSize) + 48);  // число від 0 до 9 перетворюється на символ '0' до '9'

        int randomValue = std::rand() % 2;

        // випадковий вибір напрямку корабля
        if (randomValue == 0) {
            input += 'H';
        } else {
            input += 'V';
        }

        if (valid_set(ships.pNumber, input, ships.pShips, player.intBoard, player.charBoard, 0, ship) == 0) {
            // Якщо розстановка неправильна, повторити цикл
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
