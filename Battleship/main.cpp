#include <iostream>
#include <cstdlib> // for funk system()
#include <windows.h>
#include <thread>
#include "Board.h"
#include "setting.h"
#include "moving.h"

using namespace std;


void battle()
{
      Board board;
       moving func;
       setting func2;
    int choose;
    bool choice;
    char start;
    bool game =0;
    cout << "---------------------------------------------Вітаємо Вас у грі 'Морський бій'-------------------------------------------" << endl << endl;

        do{
            cout << "                                  Введіть 1, щоб читати правила гри або 2 для її початку: " << endl;
            cout << " " << endl;
            cin >> choose;

            if (choose != 1 && choose != 2){
            cout << "Невірне значення, введіть 1 чи 2" << endl;
            }

      } while (choose != 1 && choose != 2);
system("cls");
    if (choose == 1){
        cout << "1. Як розміщувати кораблі? " << endl;
        cout << "   Потрібно ввести 4 символи: " << endl;
        cout << "     1-ий це тип корабля (1, 2, 3 або 5)" << endl;
        cout << "     2-ий це буква, що відповідає за горизонтальну координату" << endl;
        cout << "     3-ій це цифра, що відповідає за вертикальну координату" << endl;
        cout << "     4-ий це буква, що відповідає за напрям корабля 'V'(вертикальний)" << endl;
        cout << "     чи 'H' - горизонтальний" << endl;
        cout << "" << endl;
        cout << "2. Як здійснювати ходи" << endl;
        cout << "   Потрібно ввести два символи, букву та цифру координати" << endl;
        cout << "   Гра закінчиться коли усі кораблі якогось гравця буде потоплено" << endl;
        cout << "" << endl;
        cout << "Введіть будь який символ щоб почати гру" << endl;
        cin >> start;
    }





 system("cls");

    cout << "Для початку оберіть режим гри:\n   1 - гравець проти гравця\n   2 - гравець проти комп'ютера" << endl;
    while (true){
        cin >> choose;
        if (choose == 1){
                system("cls");
                game = 1;
            do
            {
                 cout << "\nГравець 1: оберіть як бажаєте заповнити ігрове поле, 1 - вручну, 2 - рандомно" << endl;
                cin >> choose;
                if (choose ==1)
                {
                    func2.sett(1, board);
                }
                else if (choose ==2)
                {
                    do
                    {
                            func2.bot_sett(1, board);
                            system("cls");
                        board.print_board(board.board11);

                        cout << "Якщо подобається розміщення - введіть 1, якщо ні - то 0" << endl;
                        cin >> choice;
                        system("cls");

                    }while (choice != 1);


                }


            } while (choose != 1 && choose !=2);
             do
            {
                 cout << "\nГравець 2: оберіть як бажаєте заповнити ігрове поле, 1 - вручну, 2 - рандомно" << endl;
                cin >> choose;
                if (choose ==1)
                {
                    func2.sett(2, board);
                }
                else if (choose ==2)
                {
                    do
                    {
                            func2.bot_sett(2, board);
                            system("cls");
                        board.print_board(board.board11);

                        cout << "Якщо подобається розміщення - введіть 1, якщо ні - то 0" << endl;
                        cin >> choice;
                        system("cls");

                    }while (choice != 1);


                }


            } while (choose != 1 && choose !=2);


            break;
        }
        else if (choose == 2)
        {
            system("cls");
              do
            {
                 cout << "\nОберіть як бажаєте заповнити ігрове поле, 1 - вручну, 2 - рандомно" << endl;
                cin >> choose;
                if (choose ==1)
                {
                    func2.sett(1, board);
                }
                else if (choose ==2)
                {
                    do
                    {
                        func2.bot_sett(1, board);
                        system("cls");
                        board.print_board(board.board11);

                        cout << "Якщо подобається розміщення - введіть 1, якщо ні - то 0" << endl;
                        cin >> choice;
                        system("cls");

                    }while (choice != 1);


                }


            } while (choose != 1 && choose !=2);
            cout << "\nТепер оберіть як бажаєте заповнити ігрове поле, 1 - вручну, 2 - рандомно" << endl;

            break;
       }
        else
       {
            cout << "Неправильне значення. Спробуйте ще раз." << endl;
        }
   }

    system("cls");


    if (game == 0)
{
    func2.bot_sett(2, board);
    func.minuss(board);

     for (int k = 0; k != -1; k++){
        if ( k%2 != 0){
            func.bot_mov(2, board, 0, 0, 0);
        } else{
            func.mov(1, board);
        }
    }
}
else
{
    func.minuss(board);
     for (int k = 0; k != -1; k++){
        if ( k%2 != 0){
            func.mov(2, board);
        } else{
            func.mov(1, board);
        }
    }

}


}
int main() {
    srand(static_cast<unsigned int>(std::time(0)));
    SetConsoleOutputCP(1251);
    battle();
}
