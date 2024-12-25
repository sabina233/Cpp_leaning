#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 游戏区域的宽度和高度（以方块为单位）
const int WIDTH = 10;
const int HEIGHT = 20;

// 方块的大小（像素）
const int BLOCK_SIZE = 30;
	
// 定义方块结构体
struct Block {
    int x;
    int y;
    int shape[4][4];
};

// 不同形状的方块模板
Block blocks[7] = {
    {0, 0, {
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }},
    {0, 0, {
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }},
    {0, 0, {
        {1, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }},
    {0, 0, {
        {1, 1, 1, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }},
    {0, 0, {
        {1, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }},
    {0, 0, {
        {0, 0, 1, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }},
    {0, 0, {
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }}
};

// 游戏区域的二维数组，用于记录每个位置是否有方块
int gameBoard[HEIGHT][WIDTH] = { 0 };

// 窗口句柄
HWND hWnd;

// 绘制单个方块
void DrawBlock(HDC hdc, int x, int y, int color) {
    HBRUSH hBrush = CreateSolidBrush(color);
    SelectObject(hdc, hBrush);
    Rectangle(hdc, x * BLOCK_SIZE, y * BLOCK_SIZE, (x + 1) * BLOCK_SIZE, (y + 1) * BLOCK_SIZE);
    DeleteObject(hBrush);
}

// 绘制游戏区域和已落下的方块
void DrawGameBoard(HDC hdc) {
    // 绘制游戏区域边框
    HBRUSH hBorderBrush = CreateSolidBrush(RGB(100, 100, 100));
    SelectObject(hdc, hBorderBrush);
    Rectangle(hdc, 0, 0, WIDTH * BLOCK_SIZE, HEIGHT * BLOCK_SIZE);
    DeleteObject(hBorderBrush);

    // 绘制已落下的方块
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (gameBoard[y][x]) {
                DrawBlock(hdc, x, y, RGB(255, 0, 0));
            }
        }
    }
}

// 绘制当前下落的方块
void DrawCurrentBlock(HDC hdc, Block block) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (block.shape[y][x]) {
                DrawBlock(hdc, block.x + x, block.y + y, RGB(0, 255, 0));
            }
        }
    }
}

// 初始化游戏
void InitGame() {
    srand(time(NULL));
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            gameBoard[y][x] = 0;
        }
    }
}

// 检查方块是否可以移动到指定位置
bool CanMove(Block block, int newX, int newY) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (block.shape[y][x]) {
                int boardX = block.x + x + newX;
                int boardY = block.y + y + newY;
                if (boardX < 0 || boardX >= WIDTH || boardY >= HEIGHT || gameBoard[boardY][boardX]) {
                    return false;
                }
            }
        }
    }
    return true;
}

// 让方块下落一步
void MoveDown(Block& block) {
    if (CanMove(block, 0, 1)) {
        block.y++;
    }
    else {
        // 将方块固定到游戏区域
        for (int y = 0; y < 4; y++) {
            for (int x = 0; x < 4; x++) {
                if (block.shape[y][x]) {
                    gameBoard[block.y + y][block.x + x] = 1;
                }
            }
        }
    }
}

// 生成新的方块
Block NewBlock() {
    Block newBlock = blocks[rand() % 7];
    newBlock.x = WIDTH / 2 - 2;
    newBlock.y = 0;
    return newBlock;
}

// 清除已满的行
int ClearLines() {
    int linesCleared = 0;
    for (int y = HEIGHT - 1; y >= 0; y--) {
        bool lineFull = true;
        for (int x = 0; x < WIDTH; x++) {
            if (!gameBoard[y][x]) {
                lineFull = false;
                break;
            }
        }
        if (lineFull) {
            linesCleared++;
            for (int moveY = y; moveY > 0; moveY--) {
                for (int x = 0; x < WIDTH; x++) {
                    gameBoard[moveY][x] = gameBoard[moveY - 1][x];
                }
            }
            for (int x = 0; x < WIDTH; x++) {
                gameBoard[0][x] = 0;
            }
            y++;
        }
    }
    return linesCleared;
}

// 窗口过程函数，处理窗口消息
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        DrawGameBoard(hdc);
        Block currentBlock = *(Block*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
        DrawCurrentBlock(hdc, currentBlock);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_KEYDOWN:
    {
        Block currentBlock = *(Block*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
        switch (wParam) {
        case VK_LEFT:
            if (CanMove(currentBlock, -1, 0)) {
                currentBlock.x--;
            }
            break;
        case VK_RIGHT:
            if (CanMove(currentBlock, 1, 0)) {
                currentBlock.x++;
            }
            break;
        case VK_DOWN:
            MoveDown(currentBlock);
            break;
        case VK_UP:
            // 这里可以实现方块旋转逻辑（暂未完整实现旋转，仅作示意）
            break;
        }
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)&currentBlock);
        InvalidateRect(hWnd, NULL, TRUE);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR szCmdLine, int iCmdShow) {
    // 注册窗口类
    WNDCLASS wndclass;
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = sizeof(Block*);
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = TEXT("Tetris");

    if (!RegisterClass(&wndclass)) {
        MessageBox(NULL, TEXT("注册窗口类失败！"), TEXT("错误"), MB_OK | MB_ICONERROR);
        return 0;
    }

    // 创建窗口
    hWnd = CreateWindow(TEXT("Tetris"), TEXT("俄罗斯方块"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        WIDTH * BLOCK_SIZE + 16, HEIGHT * BLOCK_SIZE + 39,
        NULL, NULL, hInstance, NULL);

    if (!hWnd) {
        MessageBox(NULL, TEXT("创建窗口失败！"), TEXT("错误"), MB_OK | MB_ICONERROR);
        return 0;
    }

    ShowWindow(hWnd, iCmdShow);
    UpdateWindow(hWnd);

    // 初始化游戏
    InitGame();
    Block currentBlock = NewBlock();
    SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)&currentBlock);

    // 消息循环
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        // 让方块自动下落
        Block currentBlock = *(Block*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
        MoveDown(currentBlock);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)&currentBlock);
        InvalidateRect(hWnd, NULL, TRUE);

        // 检查是否有行已满并清除
        ClearLines();
    }

    return msg.wParam;
}