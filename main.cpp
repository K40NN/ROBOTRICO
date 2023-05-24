#include <iostream>
#include <cstdlib>
#include <ctime>

const int BOARD_SIZE = 16;

void generateBoard() {
    char board[BOARD_SIZE][BOARD_SIZE];

    // Initialize the board with empty spaces
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = ' ';
        }
    }

    // Place the outer walls
    for (int i = 0; i < BOARD_SIZE; i++) {
        board[0][i] = '-';
        board[BOARD_SIZE - 1][i] = '-';
        board[i][0] = '|';
        board[i][BOARD_SIZE - 1] = '|';
    }

    // Place the walls in the middle square
    for (int i = 6; i < 10; i++) {
        board[6][i] = '-';
        board[9][i] = '-';
        board[i][6] = '|';
        board[i][9] = '|';
    }

    // Generate the walls and angles in each quadrant
    srand(time(0));
    for (int quadrant = 0; quadrant < 4; quadrant++) {
        // Place two outer walls (one horizontal, one vertical)
        int outerWallX = (quadrant % 2 == 0) ? 1 : BOARD_SIZE - 2;
        int outerWallY = (quadrant < 2) ? 1 : BOARD_SIZE - 2;
        board[outerWallX][outerWallY] = (quadrant % 2 == 0) ? '-' : '|';

        // Place four angles
        for (int angle = 0; angle < 4; angle++) {
            int angleX, angleY;
            do {
                angleX = (quadrant % 2 == 0) ? rand() % 4 + 2 : rand() % 4 + 10;
                angleY = (quadrant < 2) ? rand() % 4 + 2 : rand() % 4 + 10;
            } while (board[angleX][angleY] != ' ' || board[angleX - 1][angleY] != ' ' ||
                     board[angleX][angleY - 1] != ' ' || board[angleX - 1][angleY - 1] != ' ');

            board[angleX][angleY] = (angle % 2 == 0) ? '-' : '|';
            board[angleX - 1][angleY] = (angle % 2 == 0) ? '-' : '|';
            board[angleX][angleY - 1] = (angle % 2 == 0) ? '-' : '|';
            board[angleX - 1][angleY - 1] = (angle % 2 == 0) ? '-' : '|';
        }
    }

    // Place the additional angle in a randomly chosen quadrant
    int additionalAngleQuadrant = rand() % 4;
    int additionalAngleX, additionalAngleY;
    do {
        additionalAngleX = (additionalAngleQuadrant % 2 == 0) ? rand() % 4 + 2 : rand() % 4 + 10;
        additionalAngleY = (additionalAngleQuadrant < 2) ? rand() % 4 + 2 : rand() % 4 + 10;
    } while (board[additionalAngleX][additionalAngleY] != ' ' || board[additionalAngleX - 1][additionalAngleY] != ' ' ||
             board[additionalAngleX][additionalAngleY - 1] != ' ' || board[additionalAngleX - 1][additionalAngleY - 1] != ' ');

    board[additionalAngleX][additionalAngleY] = '-';
    board[additionalAngleX - 1][additionalAngleY] = '-';
    board[additionalAngleX][additionalAngleY - 1] = '|';
    board[additionalAngleX - 1][additionalAngleY - 1] = '|';

    // Place the robots randomly
    char robots[] = { 'R', 'G', 'B', 'Y' };
    for (int i = 0; i < 4; i++) {
        int robotX, robotY;
        do {
            robotX = rand() % (BOARD_SIZE - 4) + 2;
            robotY = rand() % (BOARD_SIZE - 4) + 2;
        } while (board[robotX][robotY] != ' ');

        board[robotX][robotY] = robots[i];
    }

    // Print the board
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            std::cout << board[i][j];
        }
        std::cout << std::endl;
    }
}

int main() {
    generateBoard();
    return 0;
}
