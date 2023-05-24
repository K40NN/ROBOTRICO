#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

const int BOARD_SIZE = 16;

class Cell {
public:
    char symbol;

    Cell() : symbol(' ') {}
};

class Wall {
public:
    bool isHorizontal;

    Wall(bool horizontal) : isHorizontal(horizontal) {}
};

class Board {
private:
    std::vector<std::vector<Cell>> cells;

public:
    Board() {
        cells.resize(BOARD_SIZE, std::vector<Cell>(BOARD_SIZE));
    }

    void initialize() {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                cells[i][j].symbol = ' ';
            }
        }
    }

    void placeWall(int x, int y, const Wall& wall) {
        if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
            if (wall.isHorizontal) {
                cells[x][y].symbol = '-';
                cells[x + 1][y].symbol = '-';
            } else {
                cells[x][y].symbol = '|';
                cells[x][y + 1].symbol = '|';
            }
        }
    }

    void placeCell(int x, int y, char symbol) {
        if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
            cells[x][y].symbol = symbol;
        }
    }

    const std::vector<std::vector<Cell>>& getCells() const {
        return cells;
    }

    void print() const {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                std::cout << cells[i][j].symbol;
            }
            std::cout << std::endl;
        }
    }
};

void generateBoard(Board& board) {
    board.initialize();

    // Place the outer walls
    for (int i = 0; i < BOARD_SIZE; i++) {
        board.placeWall(0, i, Wall(true));
        board.placeWall(BOARD_SIZE - 1, i, Wall(true));
        board.placeWall(i, 0, Wall(false));
        board.placeWall(i, BOARD_SIZE - 1, Wall(false));
    }

    // Place the walls in the middle square
    for (int i = 6; i < 10; i++) {
        board.placeWall(6, i, Wall(true));
        board.placeWall(9, i, Wall(true));
        board.placeWall(i, 6, Wall(false));
        board.placeWall(i, 9, Wall(false));
    }

    // Generate the walls and angles in each quadrant
    srand(time(0));
    for (int quadrant = 0; quadrant < 4; quadrant++) {
        // Place two outer walls (one horizontal, one vertical)
        int outerWallX = (quadrant % 2 == 0) ? 1 : BOARD_SIZE - 2;
        int outerWallY = (quadrant < 2) ? 1 : BOARD_SIZE - 2;
        board.placeWall(outerWallX, outerWallY, Wall(quadrant % 2 == 0));
        board.placeWall((quadrant % 2 == 0) ? outerWallX + 1 : outerWallX - 1, outerWallY, Wall(quadrant % 2 == 0));

        // Place four angles (two walls each)
        for (int angle = 0; angle < 4; angle++) {
            int angleX, angleY;
            do {
                angleX = (quadrant % 2 == 0) ? rand() % 4 + 2 : rand() % 4 + 10;
                angleY = (quadrant < 2) ? rand() % 4 + 2 : rand() % 4 + 10;
            } while (board.getCells()[angleX][angleY].symbol != ' ' || board.getCells()[angleX - 1][angleY].symbol != ' ' ||
                     board.getCells()[angleX][angleY - 1].symbol != ' ' || board.getCells()[angleX - 1][angleY - 1].symbol != ' ');

            board.placeWall(angleX, angleY, Wall(angle % 2 == 0));
            board.placeWall(angleX - 1, angleY, Wall(angle % 2 == 0));
            board.placeWall(angleX, angleY - 1, Wall(angle % 2 == 0));
            board.placeWall(angleX - 1, angleY - 1, Wall(angle % 2 == 0));
        }
    }

    // Place the additional angle in a randomly chosen quadrant
    int additionalAngleQuadrant = rand() % 4;
    int additionalAngleX, additionalAngleY;
    do {
        additionalAngleX = (additionalAngleQuadrant % 2 == 0) ? rand() % 4 + 2 : rand() % 4 + 10;
        additionalAngleY = (additionalAngleQuadrant < 2) ? rand() % 4 + 2 : rand() % 4 + 10;
    } while (board.getCells()[additionalAngleX][additionalAngleY].symbol != ' ' || board.getCells()[additionalAngleX - 1][additionalAngleY].symbol != ' ' ||
             board.getCells()[additionalAngleX][additionalAngleY - 1].symbol != ' ' || board.getCells()[additionalAngleX - 1][additionalAngleY - 1].symbol != ' ');

    board.placeWall(additionalAngleX, additionalAngleY, Wall(true));
    board.placeWall(additionalAngleX - 1, additionalAngleY, Wall(true));
    board.placeWall(additionalAngleX, additionalAngleY - 1, Wall(false));
    board.placeWall(additionalAngleX - 1, additionalAngleY - 1, Wall(false));

    // Place the robots randomly
    char robots[] = { 'R', 'G', 'B', 'Y' };
    for (int i = 0; i < 4; i++) {
        int robotX, robotY;
        do {
            robotX = rand() % (BOARD_SIZE - 4) + 2;
            robotY = rand() % (BOARD_SIZE - 4) + 2;
        } while (board.getCells()[robotX][robotY].symbol != ' ');

        board.placeCell(robotX, robotY, robots[i]);
    }
}

int main() {
    Board board;
    generateBoard(board);
    board.print();

    return 0;
}
