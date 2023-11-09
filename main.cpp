#include <iostream>
#include <cstdlib> // for funk system()
#include <windows.h>
#include <thread>

using namespace std;

// ������ �� �y�������� ������� ��������� �������
int p1[5];
int p2[5];

void print_board(char board12[11][11]){ //+ ����� ������ �����
    for (int i = 0; i < 11; i++){
        cout << "";
        for (int j = 0; j < 11; j++){
            cout << board12[i][j] << " ";
        }
        cout << endl;
    }
}

void print_board2(int board[10][10]){ //+ ����� �������� ��������� �����
    for (int i = 0; i < 10; i++){
        cout << "";
        for (int j = 0; j < 10; j++){
            cout << board [i][j] << " ";
        }
        cout << endl;
    }
}

// ������� ��� ��������, �� ������� ��������� ��������
bool canPlaceShip(int number, int shipType, int row, int col, int board[10][10]) { //+
    if (col + shipType > 10) {
        return false;
    }
    for (int d = 0; d < shipType; d++) {
        if (board[row][col + d] != -1) return false;
    } return true;
}

// ������� ��� ���������� �������� ����� number
int retryInput() { //+
    int number;
    cout << "������ ����� ������: ";
    cin >> number;
    return number;
}

bool valid_set(int& number, int q[5], int board[10][10], char board1[11][11]) { //+
    int ship_type = (number - (number % 10) - ((number - number % 10) / 10) % 10) / 100;
    int row = ((number - number % 10) / 10) % 10;
    int col = number % 10;

    while (true) {
        if (p1[ship_type - 1] == 0) {
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
            this_thread::sleep_for(chrono::seconds(3));
            cout << endl;
            return false;
        }

        if (!canPlaceShip(number, ship_type, row, col, board)) {
            number = retryInput();
            ship_type = (number - (number % 10) - ((number - number % 10) / 10) % 10) / 100;
            row = ((number - number % 10) / 10) % 10;
            col = number % 10;
        } else {
            break;
        }
    }

    // ϳ��� ������ �������� ����� ���������� �������� �� �����
    for (int i = row - 1; i <= row + 1; i++) {
        for (int j = col - 1; j <= col + ship_type; j++) {
            if (i >= 0 && i < 10 && j >= 0 && j < 10) {
                board[i][j] = 6; // ���� ������� �������
            }
        }
    }

    // ������������ ������ ������� �� �����
    for (int d = 0; d < ship_type; d++) {
        board[row][col + d] = ship_type;
    }
    for (int d = 0; d < ship_type; d++) {
        board1[row][col + d] = '+';
    }


    cout << p1[ship_type - 1] << endl;
    p1[ship_type - 1]--;
    return true;  // ��������� true, ������� �������� ������ ��������
}

bool valid_move(int number, char board[11][11]){ //+
    int row = ((number - number % 10) / 10) % 10;
    int col = number % 10;

    if (board[row][col] == '+' || board[row][col] == 'o' )
    {
        return 0;
    }

    else
        return 1;
}

bool endgame(int board12[10][10]){ //+

    int moves;
     for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            if (board12[i][j] == 1 ||  board12[i][j] == 2 || board12[i][j] == 3 || board12[i][j] == 4 || board12[i][j] == 5 )
                moves ++;
        }
    }
    if (moves == 0){
        cout << "��� ���������" << endl; return 1;
    }
    else
        return 0;
}

void sett(int p1[5], int board1[10][10], char board11[11][11], int palyer){ //+
    int number;

    int ship_type;
    for (int r = 0; r < 12; r++) {
        do {

            for (int t = 0; t < 1; t++) {
                  "/n";
                cout << "        ��������� ������:" << endl;
                cout << " ��������� - ����� 5x1 (" << p1[4] << " ��.)" << endl;
                cout << " ����� - ����� 4x1 (" << p1[3] << " ��.)" << endl;
                cout << " ������� - ����� 3x1 (" << p1[2] << " ��.)" << endl;
                cout << " ϳ������� ����� - ����� 2x1 (" << p1[1] << " ��.)" << endl;
                cout << " ������� - ����� 1x1 (" << p1[0] << " ��.)" << endl << "\n";
                cout << " ������ ����������� �� ����������, ������ ���������� �� ���� �������� ���� ���� ����� " << endl;
            }

            print_board(board11);
            cin >> number;
            ship_type = (number - (number % 10) - ((number - number % 10) % 100)) / 100;

            if (ship_type < 1 || ship_type > 5) {
                cout << "������� ��� �������" << endl;
                 cout << "������ �������� ��������" << endl;
                 this_thread::sleep_for(chrono::seconds(3));
                 system("cls");

            } else {

                valid_set(number, p1, board1, board11);
               system("cls");
            }
        } while (ship_type < 1 || ship_type > 5  );
    }

}

bool zona( int row, int col, int board2[10][10], char board22[11][11])
{
   int k = 1;
   int ship_type = board2[row][col];

    while (1==1){ // �������� ���� �� ��������� 0 �� 1
        if (k > 0){ // �������� ������, �� ������ �� ����� ������ �������
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
        else{ // �������� ����

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

            // ���r� ���� � ��������� � �������� ���������� �� ���� �������
            else
                k--;
        }
    }
}

void movee(int board2[10][10], char board22[11][11], char board11[11][11], int player) {
//     system("cls");
    // ��������� ��d�� ���������
    print_board2(board2);
    cout << "������� " << player << ", ��� ���." << endl;
   cout << "���� ����:" << endl;
    print_board(board11);
    cout << "���� ���������:" << endl;
    print_board(board22);

    int number;
    cout << "������ ���������� ����� (����� ����� � �������): ";
    cin >> number;

    // �������� ����������� �������� ��������� � ������ ����
     while (valid_move(number, board22) == 0){
            cout << "������ ����������. ��������� �� ���." << endl;
              number = retryInput();
        }
        int row = (number - number % 10) / 10;
        int col = number % 10;

        if ((board2[row][col] == -1) || (board2[row][col] == 6 ) ){
            cout << "������!" << endl;
            board2[row][col] = 6;
            board22[row][col] = 'o'; // ������ ������� �� ��� ���������
        } else {
            cout << "���������!" << endl;
            int ship_type = board2[row][col];

            zona(row, col, board2, board22);

            board2[row][col] = 0; // ������ ���������
            board22[row][col] = '+'; // ������ ��������� �� ��� ���������
            movee(board2, board22, board11, player);
        }
}

void chose(){
    int choose;
    cout << "_______________________________________________________________________" << endl;
    cout << "|     ������ 1, ��� ������ ������� ��� ��� 2 ��� �� �������:         |" << endl;
    cout << "_______________________________________________________________________" << endl;
     cin >> choose;
      system("cls");
     if (choose != 1 && choose != 2){
        chose();
     }
     else if (choose == 1){
        cout << "   ������� "<<endl;
    }
    else{
         cout<< "                     ����� ������ ��� :) " << endl;
    }
    return;
}

int main(){
    SetConsoleOutputCP(1251);
    int board1[10][10]; char board11[11][11];
    int board2[10][10]; char board22[11][11];
    int number;
//    chose();

        for (int i = 0; i < 10; i++){ //+
            board11[i][10] = i + 48;
            board11[10][i] = i + 48;
        }
        for (int i = 0; i < 10; i++){ //+
            for (int j = 0; j < 10; j++){
                board11[i][j] = '-';
               }
        }
        for (int i = 0; i < 10; i++){ //+
            board22[i][10] = i + 48;
            board22[10][i] = i + 48;
        }
        for (int i = 0; i < 10; i++){ //+

            for (int j = 0; j < 10; j++){
                board22[i][j] = '-';
            }
        }
        board11[10][10] = 0;
        board22[10][10] = 0;

        p1[0] = 4; p2[0] = 4;
        p1[1] = 3; p2[1] = 3;
        p1[2] = 3; p2[2] = 3;
        p1[3] = 1; p2[3] = 1;
        p1[4] = 1; p2[4] = 1;

        for (int i = 0; i< 10; i++){
            for (int j =  0; j< 10; j++){
                board1[i][j] = -1;
                board2[i][j] = -1;
            }
        }

//        sett(p1, board1, board11, 1 );
//        sett(p2, board2, board22, 2 );
        for (int j = 0; j < 1; j++)
        {
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
        for (int k = 0; k != -1; k++)
        {
            if ( k%2 != 0){
                movee(board1, board11, board22, 2);
               endgame(board2);
            }
            else{
                movee(board2, board22, board11, 1);
                endgame(board1);
            }
        }
}
