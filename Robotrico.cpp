#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int getNumberOfPlayers() {
    int numberOfPlayers;
    printf("Entrez le nombre de joueurs pour Ricochet Robot: ");
    scanf("%d", &numberOfPlayers);
    return numberOfPlayers;
}


#define BOARD_SIZE 16
#define NUM_ANGLES 17
#define NUM_EXT_WALLS 8
#define NUM_TILES 17

void generateBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    int i, j;

    // Placez les murs autour de la grille, ainsi que les murs qui forment le carré du milieu
    for (i = 0; i < BOARD_SIZE; i++) {
        board[0][i] = '#';
        board[BOARD_SIZE - 1][i] = '#';
        board[i][0] = '#';
        board[i][BOARD_SIZE - 1] = '#';
        if (i >= BOARD_SIZE / 4 && i < BOARD_SIZE * 3 / 4) {
            board[BOARD_SIZE / 2][i] = '#';
            board[i][BOARD_SIZE / 2] = '#';
        }
    }

    // Sur chaque quart, placez aléatoirement deux murs extérieurs, un côté vertical et un côté horizontal
    srand(time(NULL));
    for (i = 0; i < 4; i++) {
        int x1 = rand() % (BOARD_SIZE / 2);
        int y1 = rand() % (BOARD_SIZE / 2);
        int x2 = rand() % (BOARD_SIZE / 2);
        int y2 = rand() % (BOARD_SIZE / 2);
        if (i == 1 || i == 3) {
            x1 += BOARD_SIZE / 2;
            x2 += BOARD_SIZE / 2;
        }
        if (i == 2 || i == 3) {
            y1 += BOARD_SIZE / 2;
            y2 += BOARD_SIZE / 2;
        }
        board[x1][y1] = '#';
        board[x2][y2] = '#';
    }

    // Sur chaque quart, placez 4 "angles" constitués de deux murs chacun
    for (i = 0; i < NUM_ANGLES - 1; i++) {
        int x, y;
        do {
            x = rand() % (BOARD_SIZE / 2 - 2) + 1;
            y = rand() % (BOARD_SIZE / 2 - 2) + 1;
            if (i >= NUM_ANGLES / 4 * 3) {
                x += BOARD_SIZE / 2;
            }
            if (i >= NUM_ANGLES / 4 * 2) {
                y += BOARD_SIZE / 2;
            }
        } while(board[x][y] == '#' || board[x-1][y] == '#' || board[x+1][y] == '#' || board[x][y-1] == '#' || board[x][y+1] == '#');
        board[x][y] = '#';
        if (rand() % 2 == 0) {
            if (rand() % 2 == 0) {
                board[x-1][y] = '#';
            } else {
                board[x+1][y] = '#';
            }
        } else {
            if (rand() % 2 == 0) {
                board[x][y-1] = '#';
            } else {
                board[x][y+1] = '#';
            }
        }
    }

    // Ajoutez un nouvel "angle" de deux murs placé dans un des quarts choisi aléatoirement
    int x, y;
    do {
        x = rand() % (BOARD_SIZE - 4) + 2;
        y = rand() % (BOARD_SIZE - 4) + 2;
    } while(board[x][y] == '#' || board[x-1][y] == '#' || board[x+1][y] == '#' || board[x][y-1] == '#' || board[x][y+1] == '#');
    board[x][y] = '#';
    if (rand() % 2 == 0) {
        if (rand() % 2 == 0) {
            board[x-1][y] = '#';
        } else {
            board[x+1][y] = '#';
        }
    } else {
        if (rand() % 2 == 0) {
            board[x][y-1] = '#';
        } else {
            board[x][y+1] = '#';
        }
    }

    // Placez les 4 robots de manière aléatoire
    for (i = 0; i < 4; i++) {
        do {
            x = rand() % BOARD_SIZE;
            y = rand() % BOARD_SIZE;
        } while(board[x][y] != ' ');
        board[x][y] = 'A' + i;
    }
}

void displayBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

int selectNewTile() {
    srand(time(NULL));
    return rand() % NUM_TILES;
}