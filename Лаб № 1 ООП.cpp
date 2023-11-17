#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <Windows.h>
#include <algorithm>

using namespace std;

class Ship
{
public:
    int length;
    string name;
    //bool isSunk;

    Ship(int shipType) //: isSunk(false)
    {
        switch (shipType)
        {
        case 1:
            length = 1;
            name = "Есмінець";
            break;
        case 2:
            length = 2;
            name = "Підводний човен";
            break;
        case 3:
            length = 3;
            name = "Крейсер";
            break;
        case 4:
            length = 4;
            name = "Авіаносець";
            break;
        default:
            length = 0;
            name = "Невідомий";
            break;
        }
    }
};

class Board
{
public:
    int size;
    vector<vector<char>> grid;

    Board(int boardSize) : size(boardSize)
    {
        grid.resize(size, vector<char>(size, '-'));
    }

    void displayBoard(const string& playerName)
    {
        cout << playerName << ":\n";

        cout << "    ";
        for (int i = 1; i <= size; i++)
        {
            cout << i << "  ";
        }
        cout << "\n";

        char rowLabel = 'A';
        for (int i = 0; i < size; i++)
        {
            cout << rowLabel << "   ";
            for (int j = 0; j < size; j++)
            {
                cout << grid[i][j] << "  ";
            }
            cout << "\n";
            rowLabel++;
        }
        cout << "\n";
    }

    bool canPlaceMoreShips(int shipType, int shipsOfSize1, int shipsOfSize2, int shipsOfSize3, int shipsOfSize4)
    {
        if ((shipType == 1 && shipsOfSize1 >= 4) ||
            (shipType == 2 && shipsOfSize2 >= 3) ||
            (shipType == 3 && shipsOfSize3 >= 2) ||
            (shipType == 4 && shipsOfSize4 >= 1))
        {
            return false;
        }
        return true;
    }

    bool valid_set(int shipType, int x, int y, char direction, int shipsOfSize1, int shipsOfSize2, int shipsOfSize3, int shipsOfSize4, bool isRandomPlacement)
    {
        if (shipType < 1 || shipType > 4)
        {
            if (!isRandomPlacement)
            {
                cout << "Недійсний тип судна. Будь ласка спробуйте ще раз." << endl;
            }
            return false;
        }

        Ship playerShip(shipType);

        int xCoordinate = toupper(x) - 'A';
        int yCoordinate = y - 1;

        if (xCoordinate < 0 || xCoordinate >= size || yCoordinate < 0 || yCoordinate >= size)
        {
            if (!isRandomPlacement)
            {
                cout << "Недійсні координати. Будь ласка спробуйте ще раз." << endl;
            }
            return false;
        }

        if (!canPlaceMoreShips(shipType, shipsOfSize1, shipsOfSize2, shipsOfSize3, shipsOfSize4))
        {
            if (!isRandomPlacement)
            {
                cout << "Ви не можете розмістити більше кораблів цього типу." << endl;
            }
            return false;
        }

        if (direction == 'H')
        {
            if (yCoordinate + playerShip.length > size)
            {
                if (!isRandomPlacement)
                {
                    cout << "Корабель не поміщається на дошці. Будь ласка спробуйте ще раз." << endl;
                }
                return false;
            }
        }
        else if (direction == 'V')
        {
            if (xCoordinate + playerShip.length > size)
            {
                if (!isRandomPlacement)
                {
                    cout << "Корабель не поміщається на дошці. Будь ласка спробуйте ще раз." << endl;
                }
                return false;
            }
        }
        else
        {
            if (!isRandomPlacement)
            {
                cout << "Неправильний напрямок розміщення корабля. Використовуйте «H» або «V»." << endl;
            }
            return false;
        }

        for (int i = 0; i < playerShip.length; i++)
        {
            if (direction == 'H' && grid[xCoordinate][yCoordinate + i] != '-')
            {
                if (!isRandomPlacement)
                {
                    cout << "Зіткнення з іншим кораблем. Будь ласка спробуйте ще раз." << endl;
                }
                return false;
            }
            else if (direction == 'V' && grid[xCoordinate + i][yCoordinate] != '-')
            {
                if (!isRandomPlacement)
                {
                    cout << "Зіткнення з іншим кораблем. Будь ласка спробуйте ще раз." << endl;
                }
                return false;
            }
        }

        if (isShipNearby(xCoordinate, yCoordinate))
        {
            if (!isRandomPlacement)
            {
                cout << "Корабель занадто близько до іншого корабля. Будь ласка спробуйте ще раз." << endl;
            }
            return false;
        }

        return true;
    }

    bool isShipNearby(int x, int y)
    {
        int neighborsX[] = { 0, 0, -1, 1, -1, -1, 1, 1 };
        int neighborsY[] = { -1, 1, 0, 0, 1, -1, 1, -1 };

        for (int i = 0; i < 8; ++i)
        {
            int newX = x + neighborsX[i];
            int newY = y + neighborsY[i];

            if (newX >= 0 && newX < size && newY >= 0 && newY < size && grid[newX][newY] == '#')
            {
                return true;
            }
        }

        return false;
    }

    bool placeShip(Ship& ship, int x, int y, char direction)
    {
        int shipLength = ship.length;

        if (direction == 'V')
        {
            if (x + shipLength > size)
            {
                cout << "Корабель не поміщається на дошці." << endl;
                return false;
            }

            for (int i = x; i < x + shipLength; i++)
            {
                if (grid[i][y] != '-' || isShipNearby(i, y))
                {
                    return false;
                }
            }

            for (int i = x; i < x + shipLength; i++)
            {
                grid[i][y] = '#';
            }
        }
        else if (direction == 'H')
        {
            if (y + shipLength > size)
            {
                cout << "Корабель не поміщається на дошці." << endl;
                return false;
            }

            for (int i = y; i < y + shipLength; i++)
            {
                if (grid[x][i] != '-' || isShipNearby(x, i))
                {
                    //cout << "Зіткнення з іншим кораблем або занадто близько до іншого корабля." << endl;
                    return false;
                }
            }

            for (int i = y; i < y + shipLength; i++)
            {
                grid[x][i] = '#';
            }
        }
        else
        {
            cout << "Недійсний напрямок розташування корабля (використовуйте «H» або «V»)." << endl;
            return false;
        }

        return true;
    }

    void placeShips(Board& board, int& shipsOfSize1, int& shipsOfSize2, int& shipsOfSize3, int& shipsOfSize4, bool isRandomPlacement)
    {
        while (shipsOfSize1 < 4 || shipsOfSize2 < 3 || shipsOfSize3 < 2 || shipsOfSize4 < 1)
        {
            int shipType;
            char x;
            int y;
            char direction;

            bool validPlacement = false;
            while (!validPlacement)
            {
                if (isRandomPlacement)
                {
                    shipType = randomInt(1, 4);
                    x = 'A' + randomInt(0, board.size - 1);
                    y = 1 + randomInt(0, board.size);
                    direction = (randomInt(0, 1) == 0) ? 'H' : 'V';
                }
                else
                {
                    cout << "Введіть тип судна (1-4), координати (наприклад, A1) і напрямок (H або V): ";
                    cin >> shipType >> x >> y >> direction;
                }

                validPlacement = valid_set(shipType, x, y, direction, shipsOfSize1, shipsOfSize2, shipsOfSize3, shipsOfSize4, isRandomPlacement);

                if (validPlacement)
                {
                    int xCoordinate = toupper(x) - 'A';
                    int yCoordinate = y - 1;

                    Ship playerShip(shipType);

                    if (!board.placeShip(playerShip, xCoordinate, yCoordinate, direction))
                    {
                        validPlacement = false;
                    }
                }
            }

            if (validPlacement)
            {
                if (!isRandomPlacement)
                {
                    cout << "Корабель розміщено успішно!" << endl;
                }

                if (shipType == 1) shipsOfSize1++;
                else if (shipType == 2) shipsOfSize2++;
                else if (shipType == 3) shipsOfSize3++;
                else if (shipType == 4) shipsOfSize4++;
            }
        }

        shipsOfSize1 = 0, shipsOfSize2 = 0, shipsOfSize3 = 0, shipsOfSize4 = 0;

        if (!isRandomPlacement)
        {
            cout << "Усі кораблі розміщені!" << endl;
        }
    }

    int randomInt(int min, int max)
    {
        return min + (rand() % (max - min + 1));
    }

    void displayHiddenBoard(const string& playerName)
    {
        cout << playerName << " (Прихована дошка):\n";

        // Вивести номери стовпців
        cout << "    ";
        for (int i = 1; i <= size; i++)
        {
            cout << i << "  ";
        }
        cout << "\n";

        char rowLabel = 'A';
        for (int i = 0; i < size; i++)
        {
            cout << rowLabel << "   ";
            for (int j = 0; j < size; j++)
            {
                cout << grid[i][j] << "  ";
            }
            cout << "\n";
            rowLabel++;
        }
        cout << "\n";
    }

    bool makeComputerMove(Board& opponentBoard, Board& hiddenBoard, string player, int& x, int& y)
    {
        cout << player << " - введіть координати для вистрілу (наприклад, 'А4'): ";
        string input;
        cin >> input;

        char symbol = input[0];
        int number = stoi(input.substr(1));

        if (symbol < 'A' || symbol > 'J' || number < 1 || number > 10)
        {
            cout << "Недійсні координати. Будь ласка, введіть ще раз." << endl;
            return makeComputerMove(opponentBoard, hiddenBoard, player, x, y);
        }

        x = input[0] - 'A';
        y = number - 1;

        if (hiddenBoard.grid[x][y] == 'X' || hiddenBoard.grid[x][y] == 'O')
        {
            cout << "Ви вже стріляли в цю клітину. Будь ласка, виберіть іншу." << endl;
            return makeComputerMove(opponentBoard, hiddenBoard, player, x, y);
        }

        char cell = opponentBoard.grid[x][y];
        if (cell == '#')
        {
            if (ShipDestructionCheck(opponentBoard, hiddenBoard, x, y) == true)
            {
                checkShip(opponentBoard, hiddenBoard, x, y);
            }

            hiddenBoard.grid[x][y] = 'X';

            return true;
        }
        else
        {
            hiddenBoard.grid[x][y] = 'O';
            return false;
        }
    }

    bool ShipDestructionCheck(Board& opponentBoard, Board& hiddenBoard, int x, int y)
    {
        int xCoordinate = x;
        int yCoordinate = y;

        for (int i = 1; i < 4; i++)
        {
            if (yCoordinate + i < opponentBoard.grid.size())
            {
                if (hiddenBoard.grid[xCoordinate][yCoordinate + i] == 'X')
                {
                    continue;
                }
                else if (opponentBoard.grid[xCoordinate][yCoordinate + i] == '#')
                {
                    return false;
                }
                else
                {
                    break;
                }
            }
        }

        for (int i = 1; i < 4; i++)
        {
            if (yCoordinate - i >= 0)
            {
                if (hiddenBoard.grid[xCoordinate][yCoordinate - i] == 'X')
                {
                    continue;
                }
                else if (opponentBoard.grid[xCoordinate][yCoordinate - i] == '#')
                {
                    return false;
                }
                else
                {
                    break;
                }
            }
        }

        for (int i = 1; i < 4; i++)
        {
            if (xCoordinate + i < opponentBoard.grid.size())
            {
                if (hiddenBoard.grid[xCoordinate + i][yCoordinate] == 'X')
                {
                    continue;
                }
                else if (opponentBoard.grid[xCoordinate + i][yCoordinate] == '#')
                {
                    return false;
                }
                else
                {
                    break;
                }
            }
        }

        for (int i = 1; i < 4; i++)
        {
            if (xCoordinate - i >= 0)
            {
                if (hiddenBoard.grid[xCoordinate - i][yCoordinate] == 'X')
                {
                    continue;
                }
                else if (opponentBoard.grid[xCoordinate - i][yCoordinate] == '#')
                {
                    return false;
                }
                else
                {
                    break;
                }
            }
        }

        return true;
    }

    void checkShip(Board& opponentBoard, Board& hiddenBoard, int x, int y)
    {
        if (opponentBoard.grid[x][y] != '#') {
            return;
        }

        int start_x = x;
        int start_y = y;
        int end_x = x;
        int end_y = y;

        while (start_y - 1 >= 0 && hiddenBoard.grid[x][start_y - 1] == 'X')
        {
            start_y--;
        }

        while (end_y + 1 < hiddenBoard.grid.size() && hiddenBoard.grid[x][end_y + 1] == 'X')
        {
            end_y++;
        }

        while (start_x - 1 >= 0 && hiddenBoard.grid[start_x - 1][y] == 'X')
        {
            start_x--;
        }

        while (end_x + 1 < hiddenBoard.grid.size() && hiddenBoard.grid[end_x + 1][y] == 'X')
        {
            end_x++;
        }

        for (int i = start_x - 1; i <= end_x + 1; i++)
        {
            for (int j = start_y - 1; j <= end_y + 1; j++)
            {
                if (i >= 0 && i < hiddenBoard.grid.size() && j >= 0 && j < hiddenBoard.grid[i].size() && hiddenBoard.grid[i][j] != 'X')
                {
                    hiddenBoard.grid[i][j] = 'O';
                }
            }
        }
    }

    bool allShipsSunk(const Board& mainBoard, const Board& hiddenBoard)
    {
        for (int i = 0; i < mainBoard.size; i++)
        {
            for (int j = 0; j < mainBoard.size; j++)
            {
                if ((mainBoard.grid[i][j] == '#' && hiddenBoard.grid[i][j] != 'X') ||
                    (hiddenBoard.grid[i][j] == '#' && mainBoard.grid[i][j] != 'X'))
                {
                    return false;
                }
            }
        }

        return true;
    }

    bool computer_moves(Board& opponentBoard, Board& hiddenBoard, string player)
    {
        int x, y;

        do
        {
            x = randomInt(0, hiddenBoard.size - 1);
            y = randomInt(0, hiddenBoard.size - 1);
        } while (hiddenBoard.grid[x][y] == 'X' || hiddenBoard.grid[x][y] == 'O');

        char cell = opponentBoard.grid[x][y];
        if (cell == '#')
        {
            hiddenBoard.grid[x][y] = 'X';

            if (ShipDestructionCheck(opponentBoard, hiddenBoard, x, y))
            {
                checkShip(opponentBoard, hiddenBoard, x, y);
            }
            else
            {
                makeSubsequentShots(opponentBoard, hiddenBoard, x, y);
            }

            return true;
        }
        else
        {
            hiddenBoard.grid[x][y] = 'O';
            return false;
        }
    }

    void makeSubsequentShots(Board& opponentBoard, Board& hiddenBoard, int x, int y)
    {
        int relativeX[] = { 0, 0, -1, 1 };
        int relativeY[] = { -1, 1, 0, 0 };

        for (int i = 0; i < 4; ++i)
        {
            int newX = x + relativeX[i];
            int newY = y + relativeY[i];

            if (newX >= 0 && newX < hiddenBoard.size && newY >= 0 && newY < hiddenBoard.size)
            {
                if (hiddenBoard.grid[newX][newY] != 'X' && hiddenBoard.grid[newX][newY] != 'O')
                {
                    char cell = opponentBoard.grid[newX][newY];
                    if (cell == '#')
                    {
                        hiddenBoard.grid[newX][newY] = 'X';

                        if (ShipDestructionCheck(opponentBoard, hiddenBoard, newX, newY))
                        {
                            checkShip(opponentBoard, hiddenBoard, newX, newY);
                        }
                    }
                    else
                    {
                        hiddenBoard.grid[newX][newY] = 'O';
                    }
                }
            }
        }
    }
};

int main()
{
    SetConsoleOutputCP(1251);
    srand(time(nullptr));

    int boardSize = 10, game_mode = 0, game_choice = 0;

    int shipsOfSize1 = 0, shipsOfSize2 = 0, shipsOfSize3 = 0, shipsOfSize4 = 0;

    Board player1Board(boardSize);
    Board player2Board(boardSize);
    Board player1HiddenBoard(boardSize);
    Board player2HiddenBoard(boardSize);

    cout << "---------------------------------------------Вітаємо Вас у грі 'Морський бій'-------------------------------------------" << endl << endl;

    cout << "Для початку оберіть режим гри:\n   1 - гравець проти гравця\n   2 - гравець проти комп'ютера" << endl;

<<<<<<< HEAD
    //while (true) 
    //{
      //  cin >> game_mode;

       // if (game_mode == 1) 
       // {
         //   game = false;

           // cout << "\nТепер оберіть як бажаєте заповнити ігрове поле, 1 - вручну, 2 - рандомно" << endl;
           // break; 
      //  }
       // else if (game_mode == 2)
       // {
         //   game = true;
            //break; 
       //}
       // else 
       //{
       //     cout << "Неправильне значення. Спробуйте ще раз." << endl;
       // }
   //}   
=======
    while (true)
    {
        cout << "Ваш вибір: ";
        cin >> game_mode;

        if (game_mode == 1 || game_mode == 2)
        {
            break;
        }
        else
        {
            cout << "Неправильне значення. Спробуйте ще раз." << endl;
        }
    }

    cout << "Тепер оберіть як бажаєте заповнити ігрове поле, 1 - вручну, 2 - рандомно" << endl;
    while (true)
    {
        cout << "Ваш вибір: ";
        cin >> game_choice;

        if (game_choice == 1 || game_choice == 2)
        {
            break;
        }
        else
        {
            cout << "Неправильне значення. Спробуйте ще раз." << endl;
        }
    }
>>>>>>> ad14c8291eb242b4383e2c1a369deb3ba555fd99

    cout << "        Розставте кораблі:" << endl;
    cout << " 1 - Авіаносець - розмір 4x1 (" << 1 << " шт.)" << endl;
    cout << " 2 - Крейсер - розмір 3x1 (" << 2 << " шт.)" << endl;
    cout << " 3 - Підводний човен - розмір 2x1 (" << 3 << " шт.)" << endl;
    cout << " 4 - Есмінець - розмір 1x1 (" << 4 << " шт.)" << endl << "\n";

    if (game_mode == 1)
    {
        if (game_choice == 1)
        {
            cout << "        Гравець 1: Розставте кораблі:" << endl;
            player1Board.placeShips(player1Board, shipsOfSize1, shipsOfSize2, shipsOfSize3, shipsOfSize4, false);
            player1Board.displayBoard("Гравець 1");

            cout << "        Гравець 2: Розставте кораблі:" << endl;
            player2Board.placeShips(player2Board, shipsOfSize1, shipsOfSize2, shipsOfSize3, shipsOfSize4, false);
            player2Board.displayBoard("Гравець 2");
        }
        else
        {
            cout << "        Гравець 1: Розставте кораблі:" << endl;
            player1Board.placeShips(player1Board, shipsOfSize1, shipsOfSize2, shipsOfSize3, shipsOfSize4, true);
            player1Board.displayBoard("Гравець 1");

<<<<<<< HEAD
    cout << "        Гравець 2: Розставте кораблі:" << endl;
    player2Board.placeShips(player2Board, shipsOfSize1, shipsOfSize2, shipsOfSize3, shipsOfSize4, true);
    player2Board.displayBoard("Гравець 2");
=======
            cout << "        Гравець 2: Розставте кораблі:" << endl;
            player2Board.placeShips(player2Board, shipsOfSize1, shipsOfSize2, shipsOfSize3, shipsOfSize4, true);
            player2Board.displayBoard("Гравець 2");
        }
    }
>>>>>>> ad14c8291eb242b4383e2c1a369deb3ba555fd99

    if (game_mode == 2)
    {
        if (game_choice == 1)
        {
            cout << "        Гравець 1: Розставте кораблі:" << endl;
            player1Board.placeShips(player1Board, shipsOfSize1, shipsOfSize2, shipsOfSize3, shipsOfSize4, false);
            player1Board.displayBoard("Гравець 1");
        }
        else
        {
            cout << "        Гравець 1: Розставте кораблі:" << endl;
            player1Board.placeShips(player1Board, shipsOfSize1, shipsOfSize2, shipsOfSize3, shipsOfSize4, true);
            player1Board.displayBoard("Гравець 1");
        }

        cout << "        Гравець 2: Розставте кораблі:" << endl;
        player2Board.placeShips(player2Board, shipsOfSize1, shipsOfSize2, shipsOfSize3, shipsOfSize4, true);
        player2Board.displayBoard("Гравець 2");
    }

    bool gameIsRunning = true;
    bool player1Turn = true;
    bool isComputerPlayer2 = true;

    while (gameIsRunning)
    {
        if (player1Turn)
        {
            int x, y;

            bool extraMove = false;

            do
            {
                bool isHit = player2Board.makeComputerMove(player2Board, player2HiddenBoard, "Гравець 1", x, y);

                player2HiddenBoard.displayHiddenBoard("Гравець 2");

                if (isHit)
                {
                    cout << "Гравець 1: Ви потрапили!" << endl;
                    extraMove = true;
                }
                else
                {
                    cout << "Гравець 1: Промах." << endl;
                    extraMove = false;
                }

                if (player2Board.allShipsSunk(player2Board, player2HiddenBoard))
                {
                    cout << "Гравець 1 переміг!" << endl;
                    gameIsRunning = false;
                    break;
                }
            } while (extraMove);
        }
        else
        {
            int x, y;

            bool extraMove = false;
            bool isHit;

            do
            {
                if (!player1Turn)
                {
                    if (game_mode == 1)
                    {

                        isHit = player1Board.makeComputerMove(player1Board, player1HiddenBoard, "Гравець 2", x, y);
                    }
                    else
                    {
                        isHit = player1Board.computer_moves(player1Board, player1HiddenBoard, "Гравець 2");
                    }

                    player1HiddenBoard.displayHiddenBoard("Гравець 1");

                    if (isHit)
                    {
                        cout << "Гравець 2: Ви потрапили!" << endl;
                        extraMove = true;
                    }
                    else
                    {
                        cout << "Гравець 2: Промах." << endl;
                        extraMove = false;
                    }
                }

                if (player1Board.allShipsSunk(player1Board, player1HiddenBoard))
                {
                    cout << "Гравець 2 переміг!" << endl;
                    gameIsRunning = false;
                    break;
                }
            } while (extraMove);
        }

        player1Turn = !player1Turn;
    }

    return 0;
}







