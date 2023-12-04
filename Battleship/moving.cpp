#include "setting.h"
#include "moving.h"
#include <iostream>
#include <thread>

using std::string, std::cin, std::cout;

bool moving::valid_move(string number, char board[11][11]){
    number[0] = toupper(number[0]);
    char ro = number[0];
    char co = number[1];
    int row = ro - 'A';
    int col = co - '0';
    if (number.length() != 2)
    {
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

    while (1==1){ // виконуємо поки не повернемо 0 чи 1

         if (board22[row+1][col] == '+' || board22[row-1][col] == '+' || (0 < board2[row+1][col] && board2[row+1][col] < 6) || (0 < board2[row-1][col] && board2[row-1][col] < 6)) {
            k = 10;
        }

        if (k > 0 && k < 10){ // перевірка вправо, бо цікаво що стоїть правіше корабля

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
        else if (k < 0) { // перевірка вліво

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
        else {
            k = 1;
            while (1==1){

                  if (k > 0){ // перевірка вниз
            if (row+k > 9){ // якщо внизу корабля є межа дошки то перевіряємо вверх
                k = -1; // це траба щоб перейти до перевірки вверх
                }
            else // якщо знизу корабля не межа дошки перевіряємо що ж там є

                // якщо там не попадання (0) чи кінець корабля (6) (зона що додана при встановці корабля)
                if (board2[row+k][col] != 6  && board2[row+k][col] != 0){
                    return 0; // корабель не потоплено
                }
                else if (board2[row+k][col] == 6){ // якщо знизу зона додана при встановці
                    k = -1; // перевіряємо у ліву сторону
                }
                else // якщо ж там попадання у корабель
                    k++; // перевіряємо так само наступну клвтинку справа
                }
        else if (k < 0) { // перевірка вліво

            // якщо зверху від корабля межа дошки чи кінець корабля то обмежити корабель зоною
            if (row+k < 0 || board2[row+k][col] == 6){
                row = row + k ; // для зручності
                if (row > -1){ // якщо верхній край корабля не межує із краєм дошки
                    board2[row][col] = 6;
                    board22[row][col] = 'o';
                }
                if (row+ship_type +1 < 10){ // якщо нижній край корабля не межує із краєм жошки
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

void moving::endgame(int board33[10][10], char board3[11][11]){
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
             cout << '\n';
        }
        cout << "Вітаю, ти щойно потопив останній корабель суперника!" << '\n';
        cout << "Гру завершено" << '\n';
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
    cout << "Гравець " << player << ", ваш хід." << '\n';
    cout << "Дошка суперника" << '\n';
    board.print_board(board33);
    cout << "" << '\n';
//    board.print_board(board3);
//      cout << "" << '\n';

    cout << "Твоя дошка:" << '\n';
    board.print_board(board44);
//      cout << "" << '\n';
//    board.print_board(board4);
//      cout << "" << '\n';

    cout << "Введіть координати атаки (букву рядка і стовпця): ";
    cin >> number;

    // Перевірка правильності введених координат і взяття ходу
    while (valid_move(number, board33) == 0){
            cout << "Невірні координати. Спробуйте ще раз." << '\n';
              number = settings.retryInput();
        }
      system("cls");
         number[0] = toupper(number[0]);

            char ro = number[0];
            char co = number[1];
            int row = ro - 'A';
            int col = co - '0';

    if ((board3[row][col] == -1) || (board3[row][col] == 6 ) ){
        board3[row][col] = 6;
        board33[row][col] = 'o'; // Ознака промаху на полі суперника
    } else {
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
        board3[row][col] = 6;
        board33[row][col] = 'o'; // Ознака промаху на полі суперника
        shot = false; // Reset shot to false on a miss
    } else {
        zona(row, col, board3, board33);
        board3[row][col] = 0; // Ознака попадання
        board33[row][col] = '+'; // Ознака попадання на полі суперника
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
        if (zona(row, col, board3, board33) != 1){
            bot_mov(player, board, shot, prevHitRow, prevHitCol);
        }
        else
            bot_mov(player, board, 0, prevHitRow, prevHitCol);
    }

}



