#include <iostream>
#include <thread>
#include <windows.h>
#include "game.h"
#include "board.h"
#include "ships.h"
#include "set.h"
#include "move.h"

using std::cout, std::cin;

void battle(){
    Board board;
    Ship ship;
    moving MOVE;
    setting SET;
    Game GAME;

    int choose;
    bool choice = 0;
    char start;
    bool game = 0;
    cout << "---------------------------------------------Вітаємо Вас у грі 'Морський бій'-------------------------------------------"<< '\n';
        do{
            cout << "                                  Введіть 1, щоб читати правила гри або 2 для її початку: "<< '\n';
            cin >> choose;
            if (choose != 1 && choose != 2){
                cout << "Невірне значення, введіть 1 чи 2"<< '\n';
                }
        } while (choose != 1 && choose != 2);
   system("cls");
    if (choose == 1){
       GAME.printRules();
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
                    SET.sett(board.player1, ship.ships1, board, ship);
                }
                else if (choose ==2){
                    do{
                        board.clearing(board.player1, ship.ships1, board, ship);
                        SET.bot_sett(board.player1, ship.ships1, board, ship);

                        board.print_board(board.player1.charBoard);

                       ship.printVector(ship.player1Ships);




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
                    SET.sett(board.player2, ship.ships2, board, ship);
                }
                else if (choose ==2){
                    do{
                        board.clearing(board.player2, ship.ships2, board, ship);
                        SET.bot_sett(board.player2, ship.ships2, board, ship);

                        board.print_board(board.player2.charBoard);


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
                    SET.sett(board.player1, ship.ships1, board, ship);
                }
                else if (choose ==2){
                    do{
                        board.clearing(board.player1, ship.ships1, board, ship);
                        SET.bot_sett(board.player1, ship.ships1, board, ship);
                        board.print_board(board.player1.charBoard);
                        cout << "Якщо подобається розміщення - введіть 1, якщо ні - то 0"<< '\n';
                        cin >> choice;
                       system("cls");
                    }while (choice != 1);
                }
            } while (choose != 1 && choose !=2);
            break;
        }
        else{
            cout << "Неправильне значення. Спробуйте ще раз."<< '\n';
        }
   }

if (game == 0){
        SET.bot_sett(board.player2, ship.ships2, board, ship);
        board.minuss(board);
     for (int k = 0; k != -1; k++){
        if ( k%2 != 0){
            MOVE.bot_mov(board, ship.player2Ships, board.player2, 0, 0, 0);
        } else{
            MOVE.mov_cout(board, ship.player1Ships, 1,  board.player2, board.player1);
        }
    }
}
else{
    board.minuss(board);
     for (int k = 0; k != -1; k++){
        if ( k%2 != 0){
             MOVE.mov_cout(board, ship.player2Ships, 2, board.player1, board.player2);
        } else{
            MOVE.mov_cout(board, ship.player1Ships, 1, board.player2, board.player1);
        }
    }
}
}

int main() {
    srand(static_cast<unsigned int>(std::time(0)));
    SetConsoleOutputCP(1251);

    battle();
}
