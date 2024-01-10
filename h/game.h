#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <iostream>
#include <thread>
#include <windows.h>
#include "game.h"
#include "board.h"
#include "ships.h"
#include "set.h"
#include "move.h"



using std::string;

class Game {
public:
    Board board;
    Ship ship;
    moving MOVE;
    setting SET;
void printRules();
    bool gameMode;  // 0 for player vs player, 1 for player vs computer
};
//public:
//    Game() : gameMode(false) {}
//
//
//
//    void printRulesOrStart();
//
//    int chooseGameMode() {
//        int choose;
//        std::cout << "Для початку оберіть режим гри:\n   1 - гравець проти гравця\n   2 - гравець проти комп'ютера" << '\n';
//        while (true) {
//            std::cin >> choose;
//            if (choose == 1 || choose == 2) {
//                system("cls");
//                gameMode = (choose == 1);
//                break;
//            } else {
//                std::cout << "Неправильне значення. Спробуйте ще раз." << '\n';
//            }
//        }
//    }
//
//    void playGame() {
//        if (gameMode) {
//            // Player vs Computer
//            // Add your logic here
//        } else {
//            // Player vs Player
//            // Add your logic here
//        }
//    }
//
//    void run() {
//        printWelcomeMessage();
//        printRulesOrStart();
//        chooseGameMode();
//        playGame();
//    }
//};
//

#endif // GAME_H_INCLUDED
