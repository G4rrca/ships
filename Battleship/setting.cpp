#include "setting.h"
#include <iostream>
#include <thread>

using std::string, std::cout, std::cin;
bool setting::canPlaceShip(int shipType, int row, int col, char direction, int board[10][10]) {
    // перевірка чи корабель вміщається на дошку

    // якщо розміження пертикальне - послідовно перевіряємо вниз, на довжину корабля
    if (direction == 'V'){
        for (int d = 0; d < shipType; d++) {
            if (board[row+d][col] != -1) // якщо у клітинці не порожньо, то повертаємо false
                return false;
        }
        if (row + shipType > 10){ // якщо корабель виходить за межі дошки
            return false;
        }
        return true;
    }

    // якщо розміження горизонтальне - перевіряємо правий край
    for (int d = 0; d < shipType; d++) {
        if (board[row][col + d] != -1) // якщо у клітинці не порожньо, то повертаємо false
            return false;
    }
    if (col + shipType > 10) { // якщо корабель виходить за межі дошки
        return false;
    }
    return true;
}

string setting::retryInput() {
    string number;
    cout << "Введіть число заново: ";
    cin >> number;
    return number;
}

bool setting::valid_set(string& number, int q1[5], int board[10][10], char board1[11][11], bool human) {
    char ship_typ = number[0];  // тип корабля = першому введеному значенні при встановленні корабля
    char ro = number[1]; // рядок - другий символ (буква)
    char co = number[2]; // колонка - третій символ (цифра)
    char direction = number[3]; // напрям - четвертий символ (V чи H)

    // переведення у числове значення
    int row = ro - 'A';
    int col = co - '0';
    int ship_type = ship_typ - '0';

    while (true) {
        // якщо залишилося 0 кораблів якогось типу
        if (q1[ship_type - 1] == 0) {
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

                // повторне введення числа
                number = retryInput();

                // конвертація малих букв у великі
                number[1] = toupper(number[1]);
                number[3] = toupper(number[3]);

                // перепис змінних для подальшого використання
                ship_typ = number[0];
                ro = number[1];  row = ro - 'A';
                co = number[2];  col = co - '0';
                direction = number[3];
                ship_type = ship_typ - '0';
            }

            // якщо кораблі встановлюються випадково, то просто повеннути 0 для повторної генерації
            else{
                return 0;
            }

        } else {
            break;
        }
    }

    // при вельтикальному розміщенні
    if ( direction == 'V'){
        // Встановлення зони навколо корабля
        for (int i = col - 1; i <= col + 1; i++) {
            for (int j = row - 1; j <= row + ship_type; j++) {
                if (i >= 0 && i < 10 && j >= 0 && j < 10) {
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
        }
    }

    // при горизонтальному розміщенні
    else{
        // Встановлення зони навколо корабля
        for (int i = row - 1; i <= row + 1; i++) {
            for (int j = col - 1; j <= col + ship_type; j++) {
                if (i >= 0 && i < 10 && j >= 0 && j < 10) {
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
        }
    }
    q1[ship_type - 1]--; // вилучення розміщеного корабля із списку доступних
    return true;
}

void setting::sett(int player, Board &board){
    string number; int board3[10][10]; char board33[11][11]; int ship_type; int ship[5]; char direction;
    for (int r = 0; r < 10; r++) {
        do {
            // щоб функція працювала із потрібною дошкою, відбуватиметься копіювання даних відповідно до номеру гравця
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
                cout << "        Гравець номер " << player << "/n";
                cout << "        Розставте кораблі:" << "/n";
                cout << " Авіаносець - розмір 5x1 (" << ship[4] << " шт.)" << "/n";
                cout << " Крейсер - розмір 3x1 (" << ship[2] << " шт.)" << "/n";
                cout << " Підводний човен - розмір 2x1 (" << ship[1] << " шт.)" << "/n";
                cout << " Есмінець - розмір 1x1 (" << ship[0] << " шт.)" << "/n" << "\n";
                cout << " Кораблі розміщуються по горизонталі, введіть координату де буде розміщено лівий край судна " << "/n";
            }
            board.print_board(board33);
            cin >> number;
             system("cls");

            number[1] = toupper(number[1]);
            number[3] = toupper(number[3]);
            direction = number[3];

            if (direction != 'V' && direction != 'H')
            {
                cout << "Невірний напрям" << "/n";
                cout << "Введіть коректне значення" << "/n";
                std::this_thread::sleep_for(std::chrono::seconds(3));
            }
            if (ship_type < 1 || ship_type > 5 || ship_type ==4) {
                cout << "Невірний тип корабля" << "/n";
                cout << "Введіть коректне значення" << "/n";
                std::this_thread::sleep_for(std::chrono::seconds(3));
            }  else {
                valid_set(number, ship, board3, board33, 1);
                system("cls");
            }

        // цикл відбувається поки введені значення напрямку та корабля є валідними
        } while (ship_type < 1 || ship_type > 5 || (direction != 'V' && direction != 'H') );

        // переносимо редаговані дані назад у створені для гравців дошки
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

        // число від 1 до 5 перетворюється на символ '1' до '5'
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

        // випадковий вибір координат
        number[1] = static_cast<char>('A' + rand() % 10);  // випадкова буква від 'A' до 'J'
        number[2] = static_cast<char>((rand() % 10) + 48);  // число від 0 до 9 перетворюється на символ '0' до '9'

        int randomValue = std::rand() % 2;

        // випадковий вибір напрямку корабля
        if (randomValue == 0) {
            number[3] = 'H';
        } else {
            number[3] = 'V';
        }

        // Трансформація букви у число
        int row = number[1] - 'A';

        // Трансформація цифри з char у int
        int col = number[2] - '0';

        // Трансформація типу корабля з char у int
        ship_type = number[0] - '0';
         iterations++;
        if (valid_set(number, ship, board3, board33, 0) == 0) {
            // Якщо розстановка неправильна, повторити цикл

            continue;
        }

        // Перевірити, чи всі кораблі розміщені правильно
        bool allShipsPlacedCorrectly = true;
        for (int i = 0; i < 5; ++i) {
            if (ship[i] != 0) {
                allShipsPlacedCorrectly = false;
                break;
            }
        }

        // Якщо всі кораблі розміщені правильно, завершити цикл
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
