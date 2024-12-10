// ¶íÂÞË¹·½¿é
#include <iostream>
#include <vector>
#include <cstdlib>
#include <conio.h> // for _kbhit() and _getch()

const int WIDTH = 10;
const int HEIGHT = 20;
std::vector<std::vector<int>> board(HEIGHT, std::vector<int>(WIDTH, 0));

void drawBoard() {
    system("cls");
    for (const auto& row : board) {
        for (int cell : row) {
            std::cout << (cell ? "#" : ".") << " ";
        }
        std::cout << "\n";
    }
}

bool isValidMove(int shape, int rotation, int posX, int posY) {
    // Simplified collision detection (assumes 1 shape for example)
    return posX >= 0 && posX < WIDTH && posY < HEIGHT;
}

void placeShape(int shape, int rotation, int posX, int posY) {
    board[posY][posX] = 1; // Simplified for placing one block
}

int main() {
    int shape = 0, rotation = 0, posX = WIDTH / 2, posY = 0;

    while (true) {
        drawBoard();
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 'a') posX--; // Move left
            else if (ch == 'd') posX++; // Move right
            else if (ch == 's') posY++; // Move down
            else if (ch == 'q') break; // Quit
        }

        if (isValidMove(shape, rotation, posX, posY)) {
            placeShape(shape, rotation, posX, posY);
            posY++;
        }

        if (posY >= HEIGHT) {
            // Reset position for next shape
            posX = WIDTH / 2;
            posY = 0;
        }
    }
    return 0;
}
