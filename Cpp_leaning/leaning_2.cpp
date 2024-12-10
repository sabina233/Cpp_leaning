#include <iostream>
#include <windows.h>  // 用于控制控制台显示相关，比如设置光标位置等
#include <conio.h>    // 用于获取键盘输入
#include <ctime>      // 用于生成随机数相关

using namespace std;

// 游戏区域的宽度和高度
const int WIDTH = 10;
const int HEIGHT = 20;

// 方块结构体，用于表示每个小方块的坐标
struct Block {
    int x;
    int y;
};

// 各种形状的俄罗斯方块模板
// 这里用二维数组来表示每个形状的相对坐标布局，例如：
// 0 0 0 0
// 0 1 1 0
// 0 1 1 0
// 0 0 0 0 代表一个田字方块，1表示方块所在位置
// 下面定义了几种常见形状
Block shapes[7][4] = {
    { {0, 0}, {0, 1}, {1, 0}, {1, 1} },  // 田字方块
    { {0, 0}, {0, 1}, {0, 2}, {0, 3} },  // 长条方块（竖）
    { {0, 0}, {1, 0}, {2, 0}, {3, 0} },  // 长条方块（横）
    { {0, 0}, {0, 1}, {0, 2}, {1, 2} },  // L形方块（一种）
    { {0, 2}, {1, 0}, {1, 1}, {1, 2} },  // L形方块（另一种）
    { {0, 0}, {1, 0}, {1, 1}, {1, 2} },  // 反Z形方块
    { {0, 1}, {1, 0}, {1, 1}, {2, 0} }   // Z形方块
};

// 游戏区域，用于记录每个位置是否有方块存在，0表示空，1表示有方块
int gameBoard[HEIGHT][WIDTH] = { 0 };

// 当前方块的坐标和形状索引
Block currentBlock[4];
int currentShapeIndex;

// 初始化游戏，比如设置初始方块等
void initGame(){
    srand(static_cast<unsigned int>(time(nullptr)));
    currentShapeIndex = rand() % 7;
    for (int i = 0; i < 4; ++i) {
        currentBlock[i].x = WIDTH / 2 + shapes[currentShapeIndex][i].x;
        currentBlock[i].y = shapes[currentShapeIndex][i].y;
    }
}

// 在游戏区域绘制方块，根据传入的方块坐标数组和是否清空标记来绘制或清除方块
void drawBlock(Block block[], bool clear = false) {
    for (int i = 0; i < 4; ++i) {
        int x = block[i].x;
        int y = block[i].y;
        if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            if (clear) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                gameBoard[y][x] = 0;
            }
            else {
                SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
                gameBoard[y][x] = 1;
            }
            COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
            SetConsoleCursorPosition(hConsole, coord);
            cout << (clear ? " " : "#");
        }
    }
}

// 检查当前方块是否可以移动到指定的偏移量位置
bool canMove(int offsetX, int offsetY) {
    for (int i = 0; i < 4; ++i) {
        int newX = currentBlock[i].x + offsetX;
        int newY = currentBlock[i].y + offsetY;
        if (newX < 0 || newX >= WIDTH || newY >= HEIGHT || (newY >= 0 && gameBoard[newY][newX])) {
            return false;
        }
    }
    return true;
}

// 旋转方块，尝试顺时针旋转当前方块
void rotateBlock() {
    Block rotatedBlock[4];
    int pivotX = currentBlock[1].x;
    int pivotY = currentBlock[1].y;
    for (int i = 0; i < 4; ++i) {
        int x = currentBlock[i].x - pivotX;
        int y = currentBlock[i].y - pivotY;
        rotatedBlock[i].x = pivotX - y;
        rotatedBlock[i].y = pivotY + x;
    }
    if (canMove(0, 0)) {
        drawBlock(currentBlock, true);
        for (int i = 0; i < 4; ++i) {
            currentBlock[i] = rotatedBlock[i];
        }
        drawBlock(currentBlock);
    }
}

// 方块下落逻辑，让方块自动下落一格，如果不能下落则固定方块并生成新方块
void dropBlock() {
    if (canMove(0, 1)) {
        drawBlock(currentBlock, true);
        for (int i = 0; i < 4; ++i) {
            currentBlock[i].y++;
        }
        drawBlock(currentBlock);
    }
    else {
        drawBlock(currentBlock);
        initGame();
    }
}

// 处理用户输入，根据按键来移动或旋转方块等
void handleInput() {
    if (_kbhit()) {
        char key = _getch();
        switch (key) {
        case 'a':
            if (canMove(-1, 0)) {
                drawBlock(currentBlock, true);
                for (int i = 0; i < 4; ++i) {
                    currentBlock[i].x--;
                }
                drawBlock(currentBlock);
            }
            break;
        case 'd':
            if (canMove(1, 0)) {
                drawBlock(currentBlock, true);
                for (int i = 0; i < 4; ++i) {
                    currentBlock[i].x++;
                }
                drawBlock(currentBlock);
            }
            break;
        case 's':
            if (canMove(0, 1)) {
                drawBlock(currentBlock, true);
                for (int i = 0; i < 4; ++i) {
                    currentBlock[i].y++;
                }
                drawBlock(currentBlock);
            }
            break;
        case 'w':
            rotateBlock();
            break;
        }
    }
}
//
// 显示游戏区域
void displayBoard() {
    system("cls");  // 清屏
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            cout << (gameBoard[y][x] ? "#" : " ");
        }
        cout << endl;
    }
}

int main() {
    initGame();
    drawBlock(currentBlock);
    while (true) {
        displayBoard();
        handleInput();
        dropBlock();
        Sleep(500);
    }
    return 0;
}