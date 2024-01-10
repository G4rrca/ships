#ifndef SHIPS_H_INCLUDED
#define SHIPS_H_INCLUDED
#include <iostream>
#include <vector>


using std::string;

struct playerShips{
    int pNumber;
    int pShips[5];
    playerShips();
};

struct typeShip {
    int shipType;
    std::vector<string> placement;
    char direction;
    int HP;
};

class Ship{
public:
        playerShips ships1;
        playerShips ships2;
        Ship();
    std::vector<typeShip> player1Ships;
    std::vector<typeShip> player2Ships;
    void addShip(int player, int shipType, std::vector<string> placement, char direction, int HP , Ship &ship);
    void printShips(playerShips ships );
    void printVector (std::vector<typeShip>& ships);

};



#endif // SHIPS_H_INCLUDED
