//#include "framework.h"
#include "Lab7.h"

//#define MAX_LOADSTRING 100
#define ID_BTN_ADD      1
#define ID_BTN_CLEAR    2
#define ID_BTN_RIGHT    3
#define ID_BTN_DELETE   4
#define ID_LIST1        5
#define ID_LIST2        6
#define ID_EDIT         7

// Global Variables:
HINSTANCE hInst;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


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
    wcex.hCursor = LoadCursor(nullptr, IDC_CROSS);
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
    static HWND 
        hEdit1, 
        hListBox1,
        hListBox2,
        hButtonAdd, 
        hButtonClear,
        hButtonRight;

    switch (message)
    {
    case WM_CREATE:
    {
        int x = 100;
        hListBox1 = CreateWindow(
            L"listbox", 
            NULL,
            WS_CHILD | WS_VISIBLE | LBS_STANDARD |
            LBS_WANTKEYBOARDINPUT,
            x, 300, 200, 100,
            hWnd, (HMENU)ID_LIST1, hInst, nullptr);

        hListBox2 = CreateWindow(
            L"listbox",
            NULL,
            WS_CHILD | WS_VISIBLE | LBS_STANDARD |
            LBS_WANTKEYBOARDINPUT,
            x + 250, 300, 200, 100,
            hWnd, (HMENU)ID_LIST2, hInst, nullptr);

        hEdit1 = CreateWindow(L"edit", L"Some text...",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, x, 500, 120, 20,
            hWnd, (HMENU)ID_EDIT, hInst, NULL);

        hButtonAdd = CreateWindow(
            L"BUTTON",
            L"Add",
            WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
            x, 600, 70, 50,
            hWnd, (HMENU)ID_BTN_ADD, hInst, nullptr
        );

        hButtonClear = CreateWindow(
            L"BUTTON",
            L"Clear",
            WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
            x + 100, 600, 70, 50,
            hWnd, (HMENU)ID_BTN_CLEAR, hInst, nullptr
        );

        hButtonRight = CreateWindow(
            L"BUTTON",
            L"ToRight",
            WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
            x + 200, 600, 70, 50,
            hWnd, (HMENU)ID_BTN_RIGHT, hInst, nullptr
        );

        hButtonRight = CreateWindow(
            L"BUTTON",
            L"Delete",
            WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
            x + 300, 600, 70, 50,
            hWnd, (HMENU)ID_BTN_DELETE, hInst, nullptr
        );
    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
            //case IDM_EXIT:
            //    DestroyWindow(hWnd);
            //    break;
        case ID_BTN_ADD:
        {  
            TCHAR text[100];
            int strExists;
            GetWindowText(hEdit1, text, 100);

            strExists = (int)SendMessage(hListBox1, LB_FINDSTRINGEXACT, 0, (LPARAM)text);
            if (strExists == LB_ERR)
            {
                SendMessage(hListBox1, LB_ADDSTRING, 0,
                    (LPARAM)text);
            }
        }
            break;
        case ID_BTN_CLEAR:
            SendMessage(hListBox1, LB_RESETCONTENT, 0, 0L);
            SendMessage(hListBox2, LB_RESETCONTENT, 0, 0L);
            break;
        case ID_BTN_RIGHT:
        {  
            int selectedItem;
            TCHAR buffer[100];

            // Determining index of selected string
            selectedItem = (int)SendMessage(hListBox1,
                LB_GETCURSEL, 0, 0L);

            if (selectedItem != LB_ERR)
            {
                // Получаем выделенную строку
                SendMessage(hListBox1, LB_GETTEXT,
                    selectedItem, (LPARAM)buffer);

            }
            else break;

            int strExists = (int)SendMessage(hListBox2, LB_FINDSTRINGEXACT, 0, (LPARAM)buffer);
            if (strExists == LB_ERR)
            {
                SendMessage(hListBox2, LB_ADDSTRING, 0,
                    (LPARAM)buffer);
            }
        }
        break;
        case ID_BTN_DELETE:
        {
            int selectedItem1, selectedItem2;

            // Determining index of selected string
            selectedItem1 = (int)SendMessage(hListBox1,
                LB_GETCURSEL, 0, 0L);
            selectedItem2 = (int)SendMessage(hListBox2,
                LB_GETCURSEL, 0, 0L);

            if (selectedItem1 != LB_ERR)
            {
                // Получаем выделенную строку
                SendMessage(hListBox1, LB_DELETESTRING,
                    selectedItem1, 0L);

            }

            if (selectedItem2 != LB_ERR)
            {
                // Получаем выделенную строку
                SendMessage(hListBox2, LB_DELETESTRING,
                    selectedItem2, 0L);

            }
            
        }
        break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        GetClientRect(hWnd, &rect);


        EndPaint(hWnd, &ps);
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

