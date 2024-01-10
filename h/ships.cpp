#include "ships.h"
#include "set.h"
using std::cout ;
   playerShips::playerShips()
    {
        pShips[0] = 4;
        pShips[1] = 3;
        pShips[2] = 2;
        pShips[3] = 0;
        pShips[4] = 1;
    }
    Ship::Ship()
    {
        ships1.pNumber = 1;
        ships2.pNumber = 2;
    }

void Ship::addShip(int player, int shiptype, std::vector<string> coordinates, char directionn, int HP, Ship &ship) {
    typeShip newShip;
    newShip.shipType = shiptype;
    newShip.placement = coordinates;
    newShip.direction = directionn;
    newShip.HP = shiptype;


    if (player == 1) {
        player1Ships.push_back(newShip);
    } else
        player2Ships.push_back(newShip);
 }

 void Ship::printShips(playerShips ships) {
    "/n";
        cout << "        Гравець номер " << ships.pNumber << '\n';
        cout << "        Розставте кораблі:" << '\n';
        cout << " Авіаносець - розмір 5x1 (" << ships.pShips[4] << " шт.)" << '\n';
        cout << " Крейсер - розмір 3x1 (" << ships.pShips[2] << " шт.)" << '\n';
        cout << " Підводний човен - розмір 2x1 (" << ships.pShips[1] << " шт.)" << '\n';
        cout << " Есмінець - розмір 1x1 (" << ships.pShips[0] << " шт.)" << '\n' << '\n';
        cout << " Кораблі розміщуються по горизонталі, введіть координату де буде розміщено лівий край судна " << '\n';
    }

void Ship::printVector(std::vector<typeShip>& ships){
    for (const auto& ship : ships) {
        std::cout << "Ship Type: " << ship.shipType << std::endl;
        std::cout << "Placement: ";
        for (const auto& coord : ship.placement) {
            std::cout << coord << " ";
        }
        std::cout << std::endl;
        std::cout << "Direction: " << (ship.direction == 'V' ? "Vertical" : "Horizontal") << std::endl;
        std::cout << "HP: " << ship.HP << "/" << ship.shipType << std::endl;
        std::cout << "Is Sunk: " << (ship.HP == 0 ? "Yes" : "No") << std::endl;
        std::cout << std::endl;
    }
}


