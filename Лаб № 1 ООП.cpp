#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <ctime>

using namespace std;

class Ship
{
public:
    int length;
    string name;
    bool isSunk;

    Ship(int shipType) : isSunk(false)
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
    //vector<vector<char>> grid1;

    Board(int boardSize) : size(boardSize)
    {
        grid.resize(size, vector<char>(size, '-'));
        //grid1.resize(size, vector<char>(size, '-'));
    }

    void displayBoard(const string& playerName)
    {
        cout << playerName << ":\n";
        // Print the header row with numbers
        cout << "    ";
        for (int i = 1; i <= size; i++)
        {
            cout << i << "  ";
        }
        cout << "\n";

        // Print the board with letter labels at the top
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
        // Check if the shipType is valid
        if (shipType < 1 || shipType > 4) 
        {
            if (!isRandomPlacement)
            {
                cout << "Недійсний тип судна. Будь ласка спробуйте ще раз." << endl;                
            }
            return false;
        }

        Ship playerShip(shipType);

        // Convert letter coordinate to index (A->0, B->1, ..., J->9)
        int xCoordinate = toupper(x) - 'A';
        int yCoordinate = y - 1;

        // Check if coordinates are within the board
        if (xCoordinate < 0 || xCoordinate >= size || yCoordinate < 0 || yCoordinate >= size) 
        {
            if (!isRandomPlacement)
            {
                cout << "Недійсні координати. Будь ласка спробуйте ще раз." << endl;                
            }
            return false;
        }

        // Check if the allowed number of each ship type has been reached
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

        // Check if there is a collision with other ships
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
        // Перевірте, чи є корабель в сусідніх клітинах (вгорі, внизу, ліворуч, праворуч, по діагоналі)
        for (int dx = -1; dx <= 1; dx++)
        {
            for (int dy = -1; dy <= 1; dy++)
            {
                int newX = x + dx;
                int newY = y + dy;

                if (newX >= 0 && newX < size && newY >= 0 && newY < size)
                {
                    if (grid[newX][newY] == '#')
                    {
                        return true;
                    }
                }
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
                if (grid[i][y] != '-')
                {
                    cout << "Зіткнення з іншим кораблем." << endl;
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
                if (grid[x][i] != '-')
                {
                    cout << "Зіткнення з іншим кораблем." << endl;
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
        // Запитайте користувача про координати вистрілу
        cout << player << " - введіть координати для вистрілу (наприклад, 'А4'): ";
        string input;
        cin >> input;

        // Перевірте, чи введено правильний формат (наприклад, 'А4')
        if (input.length() != 2 || input[0] < 'A' || input[0] > 'J' || !isdigit(input[1]))
        {
            cout << "Недійсні координати. Будь ласка, введіть ще раз." << endl;
            return makeComputerMove(opponentBoard, hiddenBoard, player, x, y);
        }

        // Конвертуємо буквенну координату в числову
        x = input[0] - 'A';
        y = input[1] - '0' - 1;

        // Перевіримо, чи вже стріляли в цю клітину на прихованій дошці
        if (hiddenBoard.grid[x][y] == 'X' || hiddenBoard.grid[x][y] == 'O')
        {
            cout << "Ви вже стріляли в цю клітину. Будь ласка, виберіть іншу." << endl;
            return makeComputerMove(opponentBoard, hiddenBoard, player, x, y);
        }

        // Виконуємо вистріл на основній дошці опонента
        char cell = opponentBoard.grid[x][y];
        if (cell == '#')
        {
            // Корабель опонента потрапив
            hiddenBoard.grid[x][y] = 'X';  // Позначаємо попадання 'X' на прихованій дошці
            //cout << "Попадання!" << endl;
            return true;  // Повертаємо true, щоб показати, що потрапили
        }
        else
        {
            // Промах
            hiddenBoard.grid[x][y] = 'O';  // Позначаємо промах 'O' на прихованій дошці
            //cout << "Промах." << endl;
            return false;  // Повертаємо false, щоб показати, що промахнулися
        }
    }

    bool allShipsSunk()
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (grid[i][j] == '#')
                {
                    // Якщо знайдено непотоплений корабель, то повертаємо false
                    return false;
                }
            }
        }

        // Якщо не знайдено непотоплених кораблів, то повертаємо true
        return true;
    }
};

int main()
{
    SetConsoleOutputCP(1251);
    srand(time(nullptr));

    int boardSize = 10, game_mode = 0;
    bool game;

    Board player1Board(boardSize);
    Board player2Board(boardSize);
    Board player1HiddenBoard(boardSize);
    Board player2HiddenBoard(boardSize);

    cout << "---------------------------------------------Вітаємо Вас у грі 'Морський бій'-------------------------------------------" << endl << endl;
    cout << "Для початку оберіть режим гри:\n   1 - гравець проти гравця\n   2 - гравець проти комп'ютера" << endl;

    while (true) 
    {
        cin >> game_mode;

        if (game_mode == 1) 
        {
            game = false;

            cout << "\nТепер оберіть як бажаєте заповнити ігрове поле, 1 - вручну, 2 - рандомно" << endl;
            break; 
        }
        else if (game_mode == 2)
        {
            game = true;
            break; 
        }
        else 
        {
            cout << "Неправильне значення. Спробуйте ще раз." << endl;
        }
    }   

    cout << "        Розставте кораблі:" << endl;
    cout << " 1 - Авіаносець - розмір 4x1 (" << 1 << " шт.)" << endl;
    cout << " 2 - Крейсер - розмір 3x1 (" << 2 << " шт.)" << endl;
    cout << " 3 - Підводний човен - розмір 2x1 (" << 3 << " шт.)" << endl;
    cout << " 4 - Есмінець - розмір 1x1 (" << 4 << " шт.)" << endl << "\n";

    int shipsOfSize1 = 0, shipsOfSize2 = 0, shipsOfSize3 = 0, shipsOfSize4 = 0;

    cout << "        Гравець 1: Розставте кораблі:" << endl;
    player1Board.placeShips(player1Board, shipsOfSize1, shipsOfSize2, shipsOfSize3, shipsOfSize4, true);
    player1Board.displayBoard("Гравець 1");

    cout << "        Гравець 2: Розставте кораблі:" << endl;
    player2Board.placeShips(player2Board, shipsOfSize1, shipsOfSize2, shipsOfSize3, shipsOfSize4, game);
    player2Board.displayBoard("Гравець 2");

    //player1HiddenBoard.grid1[6][4] = 'X';
    //player1HiddenBoard.displayHiddenBoard("player 1");

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
                // Викличте метод makeComputerMove та передайте координати вистрілу
                bool isHit = player2Board.makeComputerMove(player2Board, player2HiddenBoard, "Гравець 1", x, y);

                // Гравець 1 робить вистріл
                player2HiddenBoard.displayHiddenBoard("Гравець 2");  // Показується приховане поле гравця 2 
                //player2Board.displayBoard("Гравець 2");

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

                // Перевірка на завершення гри, якщо всі кораблі одного з гравців потоплені
                if (player2Board.allShipsSunk())
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

            do
            {
                if (!player1Turn)
                {
                    // Викличте метод makeComputerMove для комп'ютерного гравця
                    bool isHit = player1Board.makeComputerMove(player1Board, player1HiddenBoard, "Гравець 2", x, y);

                    // Гравець 2 (гравець або комп'ютер) робить вистріл
                    player1HiddenBoard.displayHiddenBoard("Гравець 1");  // Показується приховане поле гравця 1

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

                // Перевірка на завершення гри, якщо всі кораблі одного з гравців потоплені
                if (player1Board.allShipsSunk())
                {
                    cout << "Гравець 2 переміг!" << endl;
                    gameIsRunning = false;
                    break;
                }
            } while (extraMove);
        }

        // Перемикаємо хід гравців
        player1Turn = !player1Turn;
    }

    return 0;
}

