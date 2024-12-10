#include <iostream>
#include <windows.h>  // ���ڿ��ƿ���̨��ʾ��أ��������ù��λ�õ�
#include <conio.h>    // ���ڻ�ȡ��������
#include <ctime>      // ����������������

using namespace std;

// ��Ϸ����Ŀ�Ⱥ͸߶�
const int WIDTH = 10;
const int HEIGHT = 20;

// ����ṹ�壬���ڱ�ʾÿ��С���������
struct Block {
    int x;
    int y;
};

// ������״�Ķ���˹����ģ��
// �����ö�ά��������ʾÿ����״��������겼�֣����磺
// 0 0 0 0
// 0 1 1 0
// 0 1 1 0
// 0 0 0 0 ����һ�����ַ��飬1��ʾ��������λ��
// ���涨���˼��ֳ�����״
Block shapes[7][4] = {
    { {0, 0}, {0, 1}, {1, 0}, {1, 1} },  // ���ַ���
    { {0, 0}, {0, 1}, {0, 2}, {0, 3} },  // �������飨����
    { {0, 0}, {1, 0}, {2, 0}, {3, 0} },  // �������飨�ᣩ
    { {0, 0}, {0, 1}, {0, 2}, {1, 2} },  // L�η��飨һ�֣�
    { {0, 2}, {1, 0}, {1, 1}, {1, 2} },  // L�η��飨��һ�֣�
    { {0, 0}, {1, 0}, {1, 1}, {1, 2} },  // ��Z�η���
    { {0, 1}, {1, 0}, {1, 1}, {2, 0} }   // Z�η���
};

// ��Ϸ�������ڼ�¼ÿ��λ���Ƿ��з�����ڣ�0��ʾ�գ�1��ʾ�з���
int gameBoard[HEIGHT][WIDTH] = { 0 };

// ��ǰ������������״����
Block currentBlock[4];
int currentShapeIndex;

// ��ʼ����Ϸ���������ó�ʼ�����
void initGame(){
    srand(static_cast<unsigned int>(time(nullptr)));
    currentShapeIndex = rand() % 7;
    for (int i = 0; i < 4; ++i) {
        currentBlock[i].x = WIDTH / 2 + shapes[currentShapeIndex][i].x;
        currentBlock[i].y = shapes[currentShapeIndex][i].y;
    }
}

// ����Ϸ������Ʒ��飬���ݴ���ķ�������������Ƿ���ձ�������ƻ��������
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

// ��鵱ǰ�����Ƿ�����ƶ���ָ����ƫ����λ��
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

// ��ת���飬����˳ʱ����ת��ǰ����
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

// ���������߼����÷����Զ�����һ���������������̶����鲢�����·���
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

// �����û����룬���ݰ������ƶ�����ת�����
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
// ��ʾ��Ϸ����
void displayBoard() {
    system("cls");  // ����
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