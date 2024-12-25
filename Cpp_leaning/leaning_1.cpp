#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ��Ϸ����Ŀ�Ⱥ͸߶ȣ��Է���Ϊ��λ��
const int WIDTH = 10;
const int HEIGHT = 20;

// ����Ĵ�С�����أ�
const int BLOCK_SIZE = 30;
	
// ���巽��ṹ��
struct Block {
    int x;
    int y;
    int shape[4][4];
};

// ��ͬ��״�ķ���ģ��
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

// ��Ϸ����Ķ�ά���飬���ڼ�¼ÿ��λ���Ƿ��з���
int gameBoard[HEIGHT][WIDTH] = { 0 };

// ���ھ��
HWND hWnd;

// ���Ƶ�������
void DrawBlock(HDC hdc, int x, int y, int color) {
    HBRUSH hBrush = CreateSolidBrush(color);
    SelectObject(hdc, hBrush);
    Rectangle(hdc, x * BLOCK_SIZE, y * BLOCK_SIZE, (x + 1) * BLOCK_SIZE, (y + 1) * BLOCK_SIZE);
    DeleteObject(hBrush);
}

// ������Ϸ����������µķ���
void DrawGameBoard(HDC hdc) {
    // ������Ϸ����߿�
    HBRUSH hBorderBrush = CreateSolidBrush(RGB(100, 100, 100));
    SelectObject(hdc, hBorderBrush);
    Rectangle(hdc, 0, 0, WIDTH * BLOCK_SIZE, HEIGHT * BLOCK_SIZE);
    DeleteObject(hBorderBrush);

    // ���������µķ���
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (gameBoard[y][x]) {
                DrawBlock(hdc, x, y, RGB(255, 0, 0));
            }
        }
    }
}

// ���Ƶ�ǰ����ķ���
void DrawCurrentBlock(HDC hdc, Block block) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (block.shape[y][x]) {
                DrawBlock(hdc, block.x + x, block.y + y, RGB(0, 255, 0));
            }
        }
    }
}

// ��ʼ����Ϸ
void InitGame() {
    srand(time(NULL));
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            gameBoard[y][x] = 0;
        }
    }
}

// ��鷽���Ƿ�����ƶ���ָ��λ��
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

// �÷�������һ��
void MoveDown(Block& block) {
    if (CanMove(block, 0, 1)) {
        block.y++;
    }
    else {
        // ������̶�����Ϸ����
        for (int y = 0; y < 4; y++) {
            for (int x = 0; x < 4; x++) {
                if (block.shape[y][x]) {
                    gameBoard[block.y + y][block.x + x] = 1;
                }
            }
        }
    }
}

// �����µķ���
Block NewBlock() {
    Block newBlock = blocks[rand() % 7];
    newBlock.x = WIDTH / 2 - 2;
    newBlock.y = 0;
    return newBlock;
}

// �����������
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

// ���ڹ��̺�������������Ϣ
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
            // �������ʵ�ַ�����ת�߼�����δ����ʵ����ת������ʾ�⣩
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
    // ע�ᴰ����
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
        MessageBox(NULL, TEXT("ע�ᴰ����ʧ�ܣ�"), TEXT("����"), MB_OK | MB_ICONERROR);
        return 0;
    }

    // ��������
    hWnd = CreateWindow(TEXT("Tetris"), TEXT("����˹����"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        WIDTH * BLOCK_SIZE + 16, HEIGHT * BLOCK_SIZE + 39,
        NULL, NULL, hInstance, NULL);

    if (!hWnd) {
        MessageBox(NULL, TEXT("��������ʧ�ܣ�"), TEXT("����"), MB_OK | MB_ICONERROR);
        return 0;
    }

    ShowWindow(hWnd, iCmdShow);
    UpdateWindow(hWnd);

    // ��ʼ����Ϸ
    InitGame();
    Block currentBlock = NewBlock();
    SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)&currentBlock);

    // ��Ϣѭ��
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        // �÷����Զ�����
        Block currentBlock = *(Block*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
        MoveDown(currentBlock);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)&currentBlock);
        InvalidateRect(hWnd, NULL, TRUE);

        // ����Ƿ��������������
        ClearLines();
    }

    return msg.wParam;
}