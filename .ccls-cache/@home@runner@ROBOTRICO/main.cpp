#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

const int BOARD_SIZE = 16;
const int CENTER_SIZE = 2;
const char EMPTY = ' ';
const char WALL = '#';
const char ROBOT = 'R';
const char OBJECTIVE = 'O';

std::vector<std::vector<char>> board(BOARD_SIZE, std::vector<char>(BOARD_SIZE, EMPTY));

void addWall(int row, int col)
{
    board[row][col] = WALL;
}

void addRandomWalls()
{
    for (int i = 1; i < BOARD_SIZE - 1; ++i)
    {
        int randomCol = rand() % (BOARD_SIZE - 2) + 1;
        int randomRow = rand() % (BOARD_SIZE - 2) + 1;

        if (board[randomRow][randomCol] == EMPTY)
        {
            addWall(randomRow, randomCol);
        }
    }
}

void addAngle(int row, int col)
{
    addWall(row, col);
    addWall(row, col + 1);
    addWall(row + 1, col);
    addWall(row + 1, col + 1);
}

void addRandomAngles()
{
    for (int i = 1; i < BOARD_SIZE / 2; ++i)
    {
        int randomCol = rand() % (BOARD_SIZE / 2 - 1) + 1;
        int randomRow = rand() % (BOARD_SIZE / 2 - 1) + 1;

        if (board[randomRow][randomCol] == EMPTY)
        {
            addAngle(randomRow, randomCol);
        }
    }
}

void addRobots()
{
    for (int i = 0; i < 4; ++i)
    {
        int randomCol = rand() % (BOARD_SIZE - 2) + 1;
        int randomRow = rand() % (BOARD_SIZE - 2) + 1;

        if (board[randomRow][randomCol] == EMPTY)
        {
            board[randomRow][randomCol] = ROBOT;
        }
        else
        {
            --i; // Retry placing the robot
        }
    }
}

void addObjective()
{
    for (int row = 1; row < BOARD_SIZE / 2; ++row)
    {
        for (int col = 1; col < BOARD_SIZE / 2; ++col)
        {
            if (board[row][col] == EMPTY &&
                board[row][col + 1] == WALL &&
                board[row + 1][col] == WALL &&
                board[row + 1][col + 1] == WALL)
            {
                board[row][col] = OBJECTIVE;
                return;
            }
        }
    }
}

void printBoard()
{
    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        for (int col = 0; col < BOARD_SIZE; ++col)
        {
            std::cout << board[row][col] << ' ';
        }
        std::cout << std::endl;
    }
}

int main()
{
    std::srand(static_cast<unsigned>(std::time(0)));

    // Adding borders
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        addWall(0, i);
        addWall(BOARD_SIZE - 1, i);
        addWall(i, 0);
        addWall(i, BOARD_SIZE - 1);
    }

    // Adding center area
    for (int row = BOARD_SIZE / 2 - CENTER_SIZE; row <= BOARD_SIZE / 2 + CENTER_SIZE; ++row)
    {
        for (int col = BOARD_SIZE / 2 - CENTER_SIZE; col <= BOARD_SIZE / 2 + CENTER_SIZE; ++col)
        {
            board[row][col] = WALL;
        }
    }

    addRandomWalls();
    addRandomAngles();
    addRobots();
    addObjective();

    printBoard();

    return 0;
}
