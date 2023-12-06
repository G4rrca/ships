#include <iostream>
#include <cstdlib> // for funk system()
#include <windows.h>
#include <thread>
#include "Board.h"
#include "setting.h"
#include "moving.h"

using std::cout, std::cin;

void battle(){
    Board board;
    moving MOVE;
    setting SET;
    int choose;
    bool choice = 0;
    char start;
    bool game = 0;
    cout << "---------------------------------------------Вітаємо Вас у грі 'Морський бій'-------------------------------------------"<< '\n';
        do{
            cout << "                                  Введіть 1, щоб читати правила гри або 2 для її початку: "<< '\n';
            cout << " "<< '\n';
            cin >> choose;
        if (choose != 1 && choose != 2){
            cout << "Невірне значення, введіть 1 чи 2"<< '\n';
            }

      } while (choose != 1 && choose != 2);
    system("cls");
    if (choose == 1){
        cout << "1. Як розміщувати кораблі? "<< '\n';
        cout << "   Потрібно ввести 4 символи: "<< '\n';
        cout << "     1-ий це тип корабля (1, 2, 3 або 5)"<< '\n';
        cout << "     2-ий це буква, що відповідає за горизонтальну координату"<< '\n';
        cout << "     3-ій це цифра, що відповідає за вертикальну координату"<< '\n';
        cout << "     4-ий це буква, що відповідає за напрям корабля 'V'(вертикальний)"<< '\n';
        cout << "     чи 'H' - горизонтальний"<< '\n';
        cout << ""<< '\n';
        cout << "2. Як здійснювати ходи"<< '\n';
        cout << "   Потрібно ввести два символи, букву та цифру координати"<< '\n';
        cout << "   Гра закінчиться коли усі кораблі якогось гравця буде потоплено"<< '\n';
        cout << ""<< '\n';
        cout << "Введіть будь який символ щоб почати гру"<< '\n';
        cin >> start;
    }

    system("cls");

    cout << "Для початку оберіть режим гри:\n   1 - гравець проти гравця\n   2 - гравець проти комп'ютера"<< '\n';
    while (true){
        cin >> choose;
        if (choose == 1){
                system("cls");
                game = 1;
            do{
                cout << "\nГравець 1: оберіть як бажаєте заповнити ігрове поле, 1 - вручну, 2 - рандомно"<< '\n';
                cin >> choose;
                system("cls");
                if (choose ==1){
                    SET.sett(1, board);
                }
                else if (choose ==2){
                    do{
                        board.clearing(1, board);
                        SET.bot_sett(1, board);

                        board.print_board(board.board11);

                        cout << "Якщо подобається розміщення - введіть 1, якщо ні - то 0"<< '\n';
                        cin >> choice;
                        system("cls");

                    }while (choice != 1);
                }
            } while (choose != 1 && choose !=2);
             do{
                 cout << "\nГравець 2: оберіть як бажаєте заповнити ігрове поле, 1 - вручну, 2 - рандомно"<< '\n';
                cin >> choose;
                 system("cls");
                if (choose ==1){
                    SET.sett(2, board);
                }
                else if (choose ==2){
                    do{
                        board.clearing(2, board);
                        SET.bot_sett(2, board);

                        board.print_board(board.board22);

                        cout << "Якщо подобається розміщення - введіть 1, якщо ні - то 0"<< '\n';
                        cin >> choice;
                        system("cls");

                    }while (choice != 1);
                }
            } while (choose != 1 && choose !=2);
                break;
        }
        else if (choose == 2){
            system("cls");
            do{
                cout << "Оберіть як бажаєте заповнити ігрове поле, 1 - вручну, 2 - рандомно"<< '\n';
                cin >> choose;
                 system("cls");
                if (choose ==1){
                    SET.sett(1, board);
                }
                else if (choose ==2){
                    do{
                        board.clearing(1, board);
                        SET.bot_sett(1, board);

                        board.print_board(board.board11);

                        cout << "Якщо подобається розміщення - введіть 1, якщо ні - то 0"<< '\n';
                        cin >> choice;
                        system("cls");

                    }while (choice != 1);
                }
            } while (choose != 1 && choose !=2);
            cout << "\nТепер оберіть як бажаєте заповнити ігрове поле, 1 - вручну, 2 - рандомно"<< '\n';

            break;
        }
        else{
            cout << "Неправильне значення. Спробуйте ще раз."<< '\n';
        }
   }

    system("cls");


    if (game == 0){
        SET.bot_sett(2, board);
        board.minuss(board);

     for (int k = 0; k != -1; k++){
        if ( k%2 != 0){
            MOVE.bot_mov(2, board, 0, 0, 0);
        } else{
            MOVE.mov(1, board);
        }
    }
}
else{
    board.minuss(board);
     for (int k = 0; k != -1; k++){
        if ( k%2 != 0){
            MOVE.mov(2, board);
        } else{
            MOVE.mov(1, board);
        }
    }
}

}
int main() {
    srand(static_cast<unsigned int>(std::time(0)));
    SetConsoleOutputCP(1251);
    battle();
}
