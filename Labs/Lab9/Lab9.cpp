// Lab9.cpp : Defines the entry point for the application.
//

#include "Lab9.h"

#define ID_BTN_ANIMATE 1
#define IDT_TIMER 2

// Global Variables:
HINSTANCE hInst;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void DeletePen(const HDC& hdc, const HPEN& hOldPen, const HPEN& hGreenPen);
void CreatePen(HPEN& hGreenPen, HPEN& hOldPen, const HDC& hdc);
void DrawBitmap(HDC hDC, int x, int y, HBITMAP hBitmap);
void Animate(HDC hdc, int x, int y, int ResourceID);

typedef enum {
    LEFT,
    RIGHT
} Direction;

typedef struct {
    int frame1;
    int frame2;
    int frame3;
} FRAMES, *PFRAMES;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.


  //  LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
  //  LoadStringW(hInstance, IDC_LAB6, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }


    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = NULL;//LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;//MAKEINTRESOURCEW(IDR_MENU1);
    wcex.lpszClassName = L"Main";//szWindowClass;
    wcex.hIconSm = NULL;//LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    HWND hWnd = CreateWindowW(L"MAIN", L"LAB6", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 1200, 1000, nullptr, nullptr, hInstance, nullptr);


    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    RECT rect;
    //2 0 2 1
 
    static FRAMES right_frames = { IDB_BITMAP1, IDB_BITMAP2, IDB_BITMAP3 };
    static FRAMES left_frames = { IDB_BITMAP4, IDB_BITMAP6, IDB_BITMAP5 };
    static PFRAMES frames;

    static int direction_left = 0, direction_frame = 0;
    static bool timerStarted = false;
    static int x = 100, y = 100;
    static Direction direction;
    
    switch (message)
    {
    case WM_CREATE:
    {

    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_RBUTTONDOWN:
        KillTimer(hWnd, IDT_TIMER);
        break;
    case WM_LBUTTONDOWN:
    {
        POINT pos;

        if (!GetCursorPos(&pos)) 
            MessageBoxW(hWnd, L"Cannot get cursor pos.", NULL, MB_OK);
        else
        {
            ScreenToClient(hWnd, &pos);
            KillTimer(hWnd, IDT_TIMER);

            Direction prev = direction;

            if (x <= pos.x)
            {           
                direction = RIGHT;
                frames = &right_frames;
            }
            else
            {
                direction = LEFT;
                frames = &left_frames;
            }

            if(direction != prev) direction_frame = 0;
            
            SetTimer(hWnd, IDT_TIMER, 600, (TIMERPROC)NULL);
            timerStarted = true;
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        if (timerStarted)
        {
            if (direction_frame == 0) Animate(hdc, x, y, frames->frame3);
            else if (direction_frame == 1) Animate(hdc, x, y, frames->frame1);
            else if (direction_frame == 2) Animate(hdc, x, y, frames->frame3);
            else Animate(hdc, x, y, frames->frame2);
            
            direction_frame++;
            if (direction_frame == 4) direction_frame = 0;
         /*   else
            {
                if (direction_left == 0) Animate(hdc, x, y, IDB_BITMAP5);
                else if (direction_left == 1) Animate(hdc, x, y, IDB_BITMAP4);
                else if (direction_left == 2) Animate(hdc, x, y, IDB_BITMAP5);
                else Animate(hdc, x, y, IDB_BITMAP6);

                direction_left++;
                if (direction_left == 4) direction_left = 0;
            }*/
        }

        //GetClientRect(hWnd, &rect);


        EndPaint(hWnd, &ps);
    }
    break;
    case WM_TIMER:
    {
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case IDT_TIMER:
            direction == RIGHT? x += 20 : x -= 20;
            InvalidateRect(hWnd, NULL, true);
            break;
        }
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


void DeletePen(const HDC& hdc, const HPEN& hOldPen, const HPEN& hGreenPen)
{
    SelectObject(hdc, hOldPen);
    DeleteObject(hGreenPen);
}

void CreatePen(HPEN& hPen, HPEN& hOldPen, const HDC& hdc)
{
    hPen = CreatePen(PS_SOLID, 10, RGB(0, 255, 0));
    hOldPen = (HPEN)SelectObject(hdc, hPen);
}

void Animate(HDC hdc, int x, int y, int ResourceID)
{
    HBITMAP hbm;
    
    hbm = LoadBitmap(hInst, MAKEINTRESOURCE(ResourceID));
    DrawBitmap(hdc, x, y, hbm);
}

void DrawBitmap(HDC hDC, int x, int y, HBITMAP hBitmap)
{
    HBITMAP hbm, hOldbm;
    HDC hMemDC;
    BITMAP bm;
    POINT  ptSize, ptOrg;

    // —оздаем контекст пам€ти, совместимый
    // с контекстом отображени€
    hMemDC = CreateCompatibleDC(hDC);

    // ¬ыбираем изображение bitmap в контекст пам€ти
    hOldbm = (HBITMAP)SelectObject(hMemDC, hBitmap);

    // ≈сли не было ошибок, продолжаем работу
    if (hOldbm)
    {
        // ƒл€ контекста пам€ти устанавливаем тот же
        // режим отображени€, что используетс€ в
        // контексте отображени€
        SetMapMode(hMemDC, GetMapMode(hDC));

        // ќпредел€ем размеры изображени€
        GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bm);

        ptSize.x = bm.bmWidth;   // ширина
        ptSize.y = bm.bmHeight;  // высота

        // ѕреобразуем координаты устройства в логические
        // дл€ устройства вывода
        DPtoLP(hDC, &ptSize, 1);

        ptOrg.x = 0;
        ptOrg.y = 0;

        // ѕреобразуем координаты устройства в логические
        // дл€ контекста пам€ти
        DPtoLP(hMemDC, &ptOrg, 1);

        // –исуем изображение bitmap
        BitBlt(hDC, x, y, ptSize.x, ptSize.y,
            hMemDC, ptOrg.x, ptOrg.y, SRCCOPY);

        // ¬осстанавливаем контекст пам€ти
        SelectObject(hMemDC, hOldbm);
    }

    // ”дал€ем контекст пам€ти
    DeleteDC(hMemDC);
}
