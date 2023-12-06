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
    cout << "---------------------------------------------³���� ��� � �� '�������� ��'-------------------------------------------"<< '\n';
        do{
            cout << "                                  ������ 1, ��� ������ ������� ��� ��� 2 ��� �� �������: "<< '\n';
            cout << " "<< '\n';
            cin >> choose;
        if (choose != 1 && choose != 2){
            cout << "������ ��������, ������ 1 �� 2"<< '\n';
            }

      } while (choose != 1 && choose != 2);
    system("cls");
    if (choose == 1){
        cout << "1. �� ���������� ������? "<< '\n';
        cout << "   ������� ������ 4 �������: "<< '\n';
        cout << "     1-�� �� ��� ������� (1, 2, 3 ��� 5)"<< '\n';
        cout << "     2-�� �� �����, �� ������� �� ������������� ����������"<< '\n';
        cout << "     3-�� �� �����, �� ������� �� ����������� ����������"<< '\n';
        cout << "     4-�� �� �����, �� ������� �� ������ ������� 'V'(������������)"<< '\n';
        cout << "     �� 'H' - ��������������"<< '\n';
        cout << ""<< '\n';
        cout << "2. �� ���������� ����"<< '\n';
        cout << "   ������� ������ ��� �������, ����� �� ����� ����������"<< '\n';
        cout << "   ��� ���������� ���� �� ������ ������� ������ ���� ���������"<< '\n';
        cout << ""<< '\n';
        cout << "������ ���� ���� ������ ��� ������ ���"<< '\n';
        cin >> start;
    }

    system("cls");

    cout << "��� ������� ������ ����� ���:\n   1 - ������� ����� ������\n   2 - ������� ����� ����'�����"<< '\n';
    while (true){
        cin >> choose;
        if (choose == 1){
                system("cls");
                game = 1;
            do{
                cout << "\n������� 1: ������ �� ������ ��������� ������ ����, 1 - ������, 2 - ��������"<< '\n';
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

                        cout << "���� ���������� ��������� - ������ 1, ���� � - �� 0"<< '\n';
                        cin >> choice;
                        system("cls");

                    }while (choice != 1);
                }
            } while (choose != 1 && choose !=2);
             do{
                 cout << "\n������� 2: ������ �� ������ ��������� ������ ����, 1 - ������, 2 - ��������"<< '\n';
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

                        cout << "���� ���������� ��������� - ������ 1, ���� � - �� 0"<< '\n';
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
                cout << "������ �� ������ ��������� ������ ����, 1 - ������, 2 - ��������"<< '\n';
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

                        cout << "���� ���������� ��������� - ������ 1, ���� � - �� 0"<< '\n';
                        cin >> choice;
                        system("cls");

                    }while (choice != 1);
                }
            } while (choose != 1 && choose !=2);
            cout << "\n����� ������ �� ������ ��������� ������ ����, 1 - ������, 2 - ��������"<< '\n';

            break;
        }
        else{
            cout << "����������� ��������. ��������� �� ���."<< '\n';
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
