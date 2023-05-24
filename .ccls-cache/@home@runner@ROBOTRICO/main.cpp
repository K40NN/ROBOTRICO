#include <iostream>
#include <vector>
#include <random>

// Définition de la classe Cell représentant une case du plateau
class Cell {
public:
    bool hasHorizontalWall;
    bool hasVerticalWall;
    bool hasRobot;

    Cell() : hasHorizontalWall(false), hasVerticalWall(false), hasRobot(false) {}
};

// Définition de la classe GameBoard représentant le plateau de jeu
class GameBoard {
public:
    static const int SIZE = 16;
    std::vector<std::vector<Cell>> board;

    GameBoard() {
        board.resize(SIZE, std::vector<Cell>(SIZE));
    }

    void display() const {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                std::cout << "+";
                std::cout << (board[i][j].hasHorizontalWall ? "-" : " ");
            }
            std::cout << "+\n";
            for (int j = 0; j < SIZE; j++) {
                std::cout << (board[i][j].hasVerticalWall ? "|" : " ");
                std::cout << (board[i][j].hasRobot ? "R" : " ");
            }
            std::cout << "|\n";
        }
        for (int j = 0; j < SIZE; j++) {
            std::cout << "+-";
        }
        std::cout << "+\n";
    }

    void generateBoard() {
        generateOuterWalls();
        generateInnerWalls();
        placeRobots();
    }

private:
    std::random_device rd;
    std::mt19937 rng{ rd() };

    void generateOuterWalls() {
        for (int i = 0; i < SIZE; i++) {
            board[0][i].hasHorizontalWall = true;
            board[SIZE - 1][i].hasHorizontalWall = true;
            board[i][0].hasVerticalWall = true;
            board[i][SIZE - 1].hasVerticalWall = true;
        }
    }

    void generateInnerWalls() {
        generateQuadrantWalls(0, 0);
        generateQuadrantWalls(0, SIZE / 2);
        generateQuadrantWalls(SIZE / 2, 0);
        generateQuadrantWalls(SIZE / 2, SIZE / 2);
        generateRandomAngle();
    }

    void generateQuadrantWalls(int startX, int startY) {
        generateRandomOuterWall(startX, startY);
        generateRandomOuterWall(startX, startY + SIZE / 2);
        generateRandomOuterWall(startX + SIZE / 2, startY);
        generateRandomOuterWall(startX + SIZE / 2, startY + SIZE / 2);
        generateRandomAngle(startX, startY);
        generateRandomAngle(startX, startY + SIZE / 2);
        generateRandomAngle(startX + SIZE / 2, startY);
        generateRandomAngle(startX + SIZE / 2, startY + SIZE / 2);
    }

    void generateRandomOuterWall(int x, int y) {
        std::uniform_int_distribution<int> dist(0, 1);
        board[x][y].hasHorizontalWall = dist(rng) == 1;
        board[x][y].hasVerticalWall = dist(rng) == 1;
    }

    void generateRandomAngle(int startX = 0, int startY = 0) {
        std::uniform_int_distribution<int> distX(startX + 1, startX + SIZE / 2 - 2);
        std::uniform_int_distribution<int> distY(startY + 1, startY + SIZE / 2 - 2);
        int x = distX(rng);
        int y = distY(rng);

        board[x][y].hasHorizontalWall = true;
        board[x][y].hasVerticalWall = true;
    }

    void placeRobots() {
        std::uniform_int_distribution<int> dist(1, SIZE / 2 - 2);
        std::uniform_int_distribution<int> distColor(0, 3);

        for (int i = 0; i < 4; i++) {
            int x = dist(rng);
            int y = dist(rng);
            board[x][y].hasRobot = true;
        }

        int targetX = dist(rng);
        int targetY = dist(rng);
        board[targetX][targetY].hasRobot = true;
        board[targetX][targetY].hasRobot = true;
        board[targetX][targetY].hasRobot = true;
        board[targetX][targetY].hasRobot = true;
        board[targetX][targetY].hasRobot = true;
        board[targetX][targetY].hasRobot = true;
        board[targetX][targetY].hasRobot = true;
        board[targetX][targetY].hasRobot = true;
        board[targetX][targetY].hasRobot = true;
    }
};

int main() {
    GameBoard gameBoard;
    gameBoard.generateBoard();
    gameBoard.display();

    return 0;
}
