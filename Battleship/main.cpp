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
    cout << "---------------------------------------------³���� ��� � �� '�������� ��'-------------------------------------------" << endl << endl;

        do{
            cout << "                                  ������ 1, ��� ������ ������� ��� ��� 2 ��� �� �������: " << endl;
            cout << " " << endl;
            cin >> choose;

            if (choose != 1 && choose != 2){
            cout << "������ ��������, ������ 1 �� 2" << endl;
            }

      } while (choose != 1 && choose != 2);
system("cls");
    if (choose == 1){
        cout << "1. �� ���������� ������? " << endl;
        cout << "   ������� ������ 4 �������: " << endl;
        cout << "     1-�� �� ��� ������� (1, 2, 3 ��� 5)" << endl;
        cout << "     2-�� �� �����, �� ������� �� ������������� ����������" << endl;
        cout << "     3-�� �� �����, �� ������� �� ����������� ����������" << endl;
        cout << "     4-�� �� �����, �� ������� �� ������ ������� 'V'(������������)" << endl;
        cout << "     �� 'H' - ��������������" << endl;
        cout << "" << endl;
        cout << "2. �� ���������� ����" << endl;
        cout << "   ������� ������ ��� �������, ����� �� ����� ����������" << endl;
        cout << "   ��� ���������� ���� �� ������ ������� ������ ���� ���������" << endl;
        cout << "" << endl;
        cout << "������ ���� ���� ������ ��� ������ ���" << endl;
        cin >> start;
    }





 system("cls");

    cout << "��� ������� ������ ����� ���:\n   1 - ������� ����� ������\n   2 - ������� ����� ����'�����" << endl;
    while (true){
        cin >> choose;
        if (choose == 1){
                system("cls");
                game = 1;
            do
            {
                 cout << "\n������� 1: ������ �� ������ ��������� ������ ����, 1 - ������, 2 - ��������" << endl;
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

                        cout << "���� ���������� ��������� - ������ 1, ���� � - �� 0" << endl;
                        cin >> choice;
                        system("cls");

                    }while (choice != 1);


                }


            } while (choose != 1 && choose !=2);
             do
            {
                 cout << "\n������� 2: ������ �� ������ ��������� ������ ����, 1 - ������, 2 - ��������" << endl;
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

                        cout << "���� ���������� ��������� - ������ 1, ���� � - �� 0" << endl;
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
                 cout << "\n������ �� ������ ��������� ������ ����, 1 - ������, 2 - ��������" << endl;
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

                        cout << "���� ���������� ��������� - ������ 1, ���� � - �� 0" << endl;
                        cin >> choice;
                        system("cls");

                    }while (choice != 1);


                }


            } while (choose != 1 && choose !=2);
            cout << "\n����� ������ �� ������ ��������� ������ ����, 1 - ������, 2 - ��������" << endl;

            break;
       }
        else
       {
            cout << "����������� ��������. ��������� �� ���." << endl;
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
