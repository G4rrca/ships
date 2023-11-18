#include <iostream>
#include <cstdlib> // for funk system()
#include <windows.h>
#include <thread>

using namespace std;

class Board {
public:
    int p1[5];
    int p2[5];

    int board1[10][10];
    char board11[11][11]; // дошки першого гравця
    int board2[10][10];
    char board22[11][11]; // дошки другого гравця
    Board(){
        p1[0] = 4; p2[0] = 4;
        p1[1] = 3; p2[1] = 3;
        p1[2] = 2; p2[2] = 2;
        p1[3] = 1; p2[3] = 1;
        p1[4] = 1; p2[4] = 1;

        board11[10][10] = 0;
        board22[10][10] = 0;

         for (int i = 0; i < 10; i++){ //+
            board11[i][10] = i + 65;
            board11[10][i] = i + 48;
        }
        for (int i = 0; i < 10; i++){ //+
            for (int j = 0; j < 10; j++){
                board11[i][j] = '-';
               }
        }
        for (int i = 0; i < 10; i++){ //+
            board22[i][10] = i + 65;
            board22[10][i] = i + 48;
        }
        for (int i = 0; i < 10; i++){ //+

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
     for (int j = 0; j < 1; j++){
            board2[0][0] = 5; board2[0][1] = 5; board2[0][2] = 5; board2[0][3] = 5; board2[0][4] = 5; board2[0][5] = 6; board2[0][6] = 1; board2[0][7] = 6; board2[0][8] = 2; board2[0][9] = 2;
            board2[1][0] = 6; board2[1][1] = 6; board2[1][2] = 6; board2[1][3] = 6; board2[1][4] = 6; board2[1][5] = 6; board2[1][6] = 6; board2[1][7] = 6; board2[1][8] = 6; board2[1][9] = 6;
            board2[2][0] = 4; board2[2][1] = 4; board2[2][2] = 4; board2[2][3] = 4; board2[2][4] = 6; board2[2][5] = 6; board2[2][6] = 6; board2[2][7] = 6; board2[2][8] = 6; board2[2][9] = 1;
            board2[3][0] = 6; board2[3][1] = 6; board2[3][2] = 6; board2[3][3] = 6; board2[3][4] = 6; board2[3][5] = 3; board2[3][6] = 3; board2[3][7] = 3; board2[3][8] = 6; board2[3][9] = 6;
            board2[4][0] = 1; board2[4][1] = 6; board2[4][2] = 1; board2[4][3] = 6; board2[4][4] = 6; board2[4][5] = 6; board2[4][6] = 6; board2[4][7] = 6; board2[4][8] = 6; board2[4][9] = 6;
            board2[5][0] = 6; board2[5][1] = 6; board2[5][2] = 6; board2[5][3] = 6; board2[5][4] = 2; board2[5][5] = 2; board2[5][6] = 6; board2[5][7] = 3; board2[5][8] = 3; board2[5][9] = 3;
            board2[6][0] = 2; board2[6][1] = 2; board2[6][2] = 6; board2[6][3] = 6; board2[6][4] = 6; board2[6][5] = 6; board2[6][6] = 6; board2[6][7] = 6; board2[6][8] = 6; board2[6][9] = 6;
            board2[7][0] = 6; board2[7][1] = 6; board2[7][2] = 6; board2[7][3] = 6; board2[7][4] = 6; board2[7][5] = -1; board2[7][6] = -1; board2[7][7] = -1; board2[7][8] = -1; board2[7][9] = -1;
            board2[8][0] = -1; board2[8][1] = -1; board2[8][2] = -1; board2[8][3] = -1; board2[8][4] = -1; board2[8][5] = -1; board2[8][6] = -1; board2[8][7] = -1; board2[8][8] = -1; board2[8][9] = -1;
            board2[9][0] = -1; board2[9][1] = -1; board2[9][2] = -1; board2[9][3] = -1; board2[9][4] = -1; board2[9][5] = -1; board2[9][6] = -1; board2[9][7] = -1; board2[9][8] = -1; board2[9][9] = -1;

            board1[0][0] = 5; board1[0][1] = 5; board1[0][2] = 5; board1[0][3] = 5; board1[0][4] = 5; board1[0][5] = 6; board1[0][6] = 1; board1[0][7] = 6; board1[0][8] = 2; board1[0][9] = 2;
            board1[1][0] = 6; board1[1][1] = 6; board1[1][2] = 6; board1[1][3] = 6; board1[1][4] = 6; board1[1][5] = 6; board1[1][6] = 6; board1[1][7] = 6; board1[1][8] = 6; board1[1][9] = 6;
            board1[2][0] = 4; board1[2][1] = 4; board1[2][2] = 4; board1[2][3] = 4; board1[2][4] = 6; board1[2][5] = 6; board1[2][6] = 6; board1[2][7] = 6; board1[2][8] = 6; board1[2][9] = 1;
            board1[3][0] = 6; board1[3][1] = 6; board1[3][2] = 6; board1[3][3] = 6; board1[3][4] = 6; board1[3][5] = 3; board1[3][6] = 3; board1[3][7] = 3; board1[3][8] = 6; board1[3][9] = 6;
            board1[4][0] = 1; board1[4][1] = 6; board1[4][2] = 1; board1[4][3] = 6; board1[4][4] = 6; board1[4][5] = 6; board1[4][6] = 6; board1[4][7] = 6; board1[4][8] = 6; board1[4][9] = 6;
            board1[5][0] = 6; board1[5][1] = 6; board1[5][2] = 6; board1[5][3] = 6; board1[5][4] = 2; board1[5][5] = 2; board1[5][6] = 6; board1[5][7] = 3; board1[5][8] = 3; board1[5][9] = 3;
            board1[6][0] = 2; board1[6][1] = 2; board1[6][2] = 6; board1[6][3] = 6; board1[6][4] = 6; board1[6][5] = 6; board1[6][6] = 6; board1[6][7] = 6; board1[6][8] = 6; board1[6][9] = 6;
            board1[7][0] = 6; board1[7][1] = 6; board1[7][2] = 6; board1[7][3] = 6; board1[7][4] = 6; board1[7][5] = -1; board1[7][6] = -1; board1[7][7] = -1; board1[7][8] = -1; board1[7][9] = -1;
            board1[8][0] = -1; board1[8][1] = -1; board1[8][2] = -1; board1[8][3] = -1; board1[8][4] = -1; board1[8][5] = -1; board1[8][6] = -1; board1[8][7] = -1; board1[8][8] = -1; board1[8][9] = -1;
            board1[9][0] = -1; board1[9][1] = -1; board1[9][2] = -1; board1[9][3] = -1; board1[9][4] = -1; board1[9][5] = -1; board1[9][6] = -1; board1[9][7] = -1; board1[9][8] = -1; board1[9][9] = -1;
    }
    }
  template <typename T, int Size>
    void print_board(T (&board)[Size][Size]) {
        for (int i = 0; i < Size; i++) {
            for (int j = 0; j < Size; j++) {
                 cout << board[i][j] << " ";
            }
             cout << endl;
        }
    }

};

class Game {
public:

bool canPlaceShip(int shipType, int row, int col, int board[10][10]) { //+
    if (col + shipType > 10) {
        return false;
    }
    for (int d = 0; d < shipType; d++) {
        if (board[row][col + d] != -1) return false;
    } return true;
}

string retryInput() { //+
    string number;
    cout << "Введіть число заново: ";
    cin >> number;
    return number;
}

bool valid_set(string number, int q1[5], int board[10][10], char board1[11][11]) { //+
    char ship_typ = number[0];
    char ro = number[1];
    char co = number[2];

    int row = ro - 'A' ;
    int col = co - '0';
    int ship_type = ship_typ - '0';

    while (true) {
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
            this_thread::sleep_for(chrono::seconds(3));
            cout << endl;
            return false;
        }

        if (!canPlaceShip(ship_type, row, col, board)) {
            number = retryInput();
             ship_typ = number[0];
            ro = number[1];
            co = number[2];

            row = ro - 'A';

            col = co - '0';

            ship_type = ship_typ - '0';
        } else {
            break;
        }
    }

    // Після успішної перевірки можна встановити корабель на дошці
    for (int i = row - 1; i <= row + 1; i++) {
        for (int j = col - 1; j <= col + ship_type; j++) {
            if (i >= 0 && i < 10 && j >= 0 && j < 10) {
                board[i][j] = 6; // Зона навколо корабля
            }
        }
    }

    // Встановлення самого корабля на дошці
    for (int d = 0; d < ship_type; d++) {
        board[row][col + d] = ship_type;
    }
    for (int d = 0; d < ship_type; d++) {
        board1[row][col + d] = '+';
    }


    q1[ship_type - 1]--;
    return true;  // Повернути true, оскільки корабель успішно розміщено
}

bool valid_move(string number, char board[11][11]){ //+
  number[0] = toupper(number[0]);
                char ro = number[0];
                char co = number[1];

                int row = ro - 'A';
                int col = co - '0';
                
    if (board[row][col] == '+' || board[row][col] == 'o' ){
        return 0;
    } else
        return 1;
}

void sett(int player, Board board){ //+
    string number; int board3[10][10]; char board33[11][11]; int ship_type; int ship[5];
    for (int r = 0; r < 11; r++) {
        do {
             if (player == 1) {
                memcpy(board3, board.board1, sizeof(board3));
                memcpy(board33, board.board11, sizeof(board33));
                memcpy(ship, board.p1, sizeof(ship));

            } else {
                memcpy(board3, board.board2, sizeof(board3));
                memcpy(board33, board.board22, sizeof(board33));
                memcpy(ship, board.p2, sizeof(ship));
            }

            for (int t = 0; t < 1; t++) {
                  "/n";
                cout << "        Гравець номер " << player << endl;
                cout << "        Розставте кораблі:" << endl;
                cout << " Авіаносець - розмір 5x1 (" << ship[4] << " шт.)" << endl;
                cout << " Баржа - розмір 4x1 (" << ship[3] << " шт.)" << endl;
                cout << " Крейсер - розмір 3x1 (" << ship[2] << " шт.)" << endl;
                cout << " Підводний човен - розмір 2x1 (" << ship[1] << " шт.)" << endl;
                cout << " Есмінець - розмір 1x1 (" << ship[0] << " шт.)" << endl << "\n";
                cout << " Кораблі розміщуються по горизонталі, введіть координату де буде розміщено лівий край судна " << endl;
            }
                board.print_board(board33);

                cin >> number;
                number[1] = toupper(number[1]);
                 char ship_typ = number[0];
                char ro = number[1];
                char co = number[2];


                // Трансформація букви у число
                int row = ro - 'A';

                // Трансформація цифри з char у int
                int col = co - '0';

                // Трансформація типу корабля з char у int
                ship_type = ship_typ - '0';


                if (ship_type < 1 || ship_type > 5) {
                    cout << "Невірний тип корабля" << endl;
                     cout << "Введіть коректне значення" << endl;
                     this_thread::sleep_for(chrono::seconds(3));
                     system("cls");

                }  else {

                valid_set(number, ship, board3, board33);
                system("cls");
                }


        } while (ship_type < 1 || ship_type > 5  );
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

bool zona( int row, int col, int board2[10][10], char board22[11][11]){
   int k = 1;
   int ship_type = board2[row][col];

    while (1==1){ // виконуємо поки не повернемо 0 чи 1
        if (k > 0){ // перевірка вправо, бо цікаво що стоїть правіше корабля
            if (col+k > 9){ // якщо правіше корабля є межа дошки то перевіряємо вліво
                k = -1; // це траба щоб перейти до перевірки вліво
                }
            else // якщо справа корабля не межа дошки перевіряємо що ж там є

                // яещо там не попадання (0) чи кінець корабля (6) (зона що додана при встановці корабля)
                if (board2[row][col+k] != 6  && board2[row][col+k] != 0){
                    return 0; // корабель не потоплено, а отже не треба його оточувати зоною
                }
                else if (board2[row][col+k] == 6){ // якщо справа зона додана при встановці
                    k = -1; // перевіряємо у ліву сторону
                }
                else // якщо ж там попадання у корабель
                    k++; // перевіряємо так само наступну клвтинку справа
                }
        else{ // перевірка вліво

            // якщо зліва від корабля межа дошки чи кінець корабля то обмежити корабель зоною
            if (col+k < 0 || board2[row][col+k] == 6){
                col = col + k ; // для зручності
                if (col > -1){ // якщо лівий край корабля не межує із краєм дошки
                    board2[row][col] = 6;
                    board22[row][col] = 'o';
                }
                if (col+ship_type +1 < 10){ // якщо правий край корабля не межує із краєм жошки
                    board2[row][col+ship_type +1] = 6;
                    board22[row][col+ ship_type +1] = 'o';
                }
                for (int i = 0; i != ship_type + 2; i++){ // оточуємо корабель смужкою зверху
                    if (row - 1 > -1){ // якщо зверху немає межі дошки
                        if (col + i > -1 && col + i < 10){
                            board2[row-1][col +i ] = 6;
                            board22[row-1][col +i] = 'o';
                        }
                    }
                    if (row + 1 < 10){ // оточуємо корабель смужкою знизу
                        if (col + i < 10 && col + i > -1){ // якщо знизу немає межі дошки
                            board2[row+1][col +i ] = 6;
                            board22[row+1][col +i] = 'o';
                        }
                    }
                }
                return 1; // малювання зони завершено
            }

            // якщо зліва не кінець зони, а частинка корабля в яку ще не попадали
            if (board2[row][col+k] != 6 && board2[row][col+k] != 0){
                return 0; // корабель не потоплено тому зону не малюємо
            }

            // якщо зліва є попадання в корабель перевіряємо ще одну клітинку
            else
                k--;
        }
    }
}

void chose(){
    int choose;
    cout << "_______________________________________________________________________" << endl;
    cout << "|     Введіть 1, щоб читати правила гри або 2 для її початку:         |" << endl;
    cout << "_______________________________________________________________________" << endl;
    cin >> choose;
    system("cls");
    if (choose != 1 && choose != 2){
        chose();
    }
    else if (choose == 1){
        cout << "   правила "<<endl;
    }
    else{
        cout<< "                     Бажаю приємної гри :) " << endl;
    }
    return;
}

void endgame(int board33[10][10], char board3[11][11]){ //+
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
        cout << "Вітаю, ти щойно потопив останній корабель суперника!" << endl;
        cout << "Гру завершено" << endl;
        exit(0);
    }
}

bool mov(int player, Board &board){
    string number; int board3[10][10]; char board33[11][11];  bool k = 0;
    if (player == 1) {
        memcpy(board3, board.board2, sizeof(board3));
        memcpy(board33, board.board22, sizeof(board33));
    } else {
        memcpy(board3, board.board1, sizeof(board3));
        memcpy(board33, board.board11, sizeof(board33));
    }
    cout << "Гравець " << player << ", ваш хід." << endl;
    board.print_board(board33);
    cout << "Введіть координати атаки (номер рядка і стовпця): ";
    cin >> number;


    // Перевірка правильності введених координат і взяття ходу
    while (valid_move(number, board33) == 0){
            cout << "Невірні координати. Спробуйте ще раз." << endl;
              number = retryInput();
        }
         system("cls");
         number[0] = toupper(number[0]);

            char ro = number[0];
            char co = number[1];
            int row = ro - 'A';
            int col = co - '0';

    if ((board3[row][col] == -1) || (board3[row][col] == 6 ) ){
        cout << "Промах!" << endl;
        board3[row][col] = 6;
        board33[row][col] = 'o'; // Ознака промаху на полі суперника
    } else {
        cout << "Попадання!" << endl;
        zona(row, col, board3, board33);
        board3[row][col] = 0; // Ознака попадання
        board33[row][col] = '+'; // Ознака попадання на полі суперника
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

};

void battle()
{
    Board board;
    Game func;
    func.chose();
    func.sett(1, board );
    func.sett(2, board );

    for (int k = 0; k != -1; k++){
        if ( k%2 != 0){
            func.mov(2, board);
        } else{
            func.mov(1, board);
        }
    }
}

int main() {
    SetConsoleOutputCP(1251);
    battle();
    return 0;
}
