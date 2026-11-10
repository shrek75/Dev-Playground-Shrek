// 034_PathFinding_WinApp.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "034_PathFinding_WinApp.h"
#include <windowsx.h>
#include "PathFinding.h"

#define MAX_LOADSTRING 100

#define PROFILER
#include "C:/Users/user/Desktop/MyDLL/Profiler/profiler.h"
#pragma comment(lib,"C:/Users/user/Desktop/MyDLL/Profiler/Profiler.lib")


// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

int g_x;   //현재 마우스의 x좌표
int g_y;   //현재 마우스의 y좌표
int g_col; //몇번째 열의 cell인지
int g_row; //몇번째 행의 cell인지



// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
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

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY034PATHFINDINGWINAPP, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY034PATHFINDINGWINAPP));

    MSG msg;


    PathFinding::Init();

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    PathFinding::DeInit();


    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY034PATHFINDINGWINAPP));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY034PATHFINDINGWINAPP);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_MOUSEMOVE:
    {
        PROFILE(L"WM_MOUSEMOVE");
        g_x = GET_X_LPARAM(lParam);
        g_y = GET_Y_LPARAM(lParam);

        //픽셀 좌표 > 격자 칸 번호로 변환
        g_col = g_x / CELL_SIZE;
        g_row = g_y / CELL_SIZE;

       // InvalidateRect(hWnd, nullptr, TRUE);
    }
    break;
    case WM_LBUTTONDOWN:
    {
        PathFinding::SetObstacleNode(g_row, g_col, TRUE);

        InvalidateRect(hWnd, nullptr, TRUE); //WM_PAINT 요청이래.
    }
    break;

    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case L'1':
            PathFinding::SetStartNode(g_row, g_col);
            break;
        case L'2':
            PathFinding::SetEndNode(g_row, g_col);
            break;
        case L'S':
            PathFinding::FindPath();
            break;
        case L'P':
        {
            Profiler::ProfileDataOutText(L"PathFindingWinAppProfileTest.txt");
        }
        break;
            
        }

        //다시 그리기 요청
        InvalidateRect(hWnd, nullptr, TRUE);
    }
    break;

    case WM_PAINT:
        {
            PROFILE(L"WM_PAINT");
            PAINTSTRUCT ps;
            HDC hdc =BeginPaint(hWnd, &ps);
            // TODO: 여기에 그리기 코드를 추가합니다...

            //Node 색칠해주기.

            for (DWORD y = 0; y < PathFinding::GetScreenHeight(); y++)
            {
                for (DWORD x = 0; x < PathFinding::GetScreenWidth(); x++)
                {
                    const Node* node;
                    if (!PathFinding::GetNode(y, x, &node)) continue;
 
                    HBRUSH myBrush;
                    if (node->_isObstacle)
                        myBrush = CreateSolidBrush(RGB(50, 50, 50));
                    else if (node->_isTraveled)
                        myBrush = CreateSolidBrush(RGB(255, 0, 100));
                    else if (node->_isReserved)
                        myBrush = CreateSolidBrush(RGB(255, 100, 0));
                    else continue;
                    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

                    Rectangle(hdc,
                        CELL_SIZE * x,
                        CELL_SIZE * y,
                        CELL_SIZE * (x + 1),
                        CELL_SIZE * (y + 1)
                    );

                    SelectObject(hdc, oldBrush);
                    DeleteObject(myBrush);

                }
            }



            DWORD startNodeCol;
            DWORD startNodeRow;
            DWORD endNodeCol;
            DWORD endNodeRow;

            //시작 Node 그리기
			if (PathFinding::GetStartNode(&startNodeRow, &startNodeCol))
			{
				HBRUSH myBrush = CreateSolidBrush(RGB(255, 0, 0));
				HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

                Rectangle(hdc,
                    CELL_SIZE * startNodeCol,
                    CELL_SIZE * startNodeRow,
                    CELL_SIZE * (startNodeCol + 1),
                    CELL_SIZE * (startNodeRow + 1)
                );

				SelectObject(hdc, oldBrush);
				DeleteObject(myBrush);

			}

            //도착 Node 그리기
            if (PathFinding::GetEndNode(&endNodeRow, &endNodeCol))
            {
                HBRUSH myBrush = CreateSolidBrush(RGB(255, 0, 255));
                HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

                Rectangle(hdc,
                    CELL_SIZE * endNodeCol,
                    CELL_SIZE * endNodeRow,
                    CELL_SIZE * (endNodeCol + 1),
                    CELL_SIZE * (endNodeRow + 1)
                );

                SelectObject(hdc, oldBrush);
                DeleteObject(myBrush);
            }


            // 격자 그리기
            DWORD maxH = PathFinding::GetScreenHeight();
            DWORD maxW = PathFinding::GetScreenWidth();

            for (DWORD i = 0; i <= maxH; i++)
            {
                MoveToEx(hdc, 0, i * CELL_SIZE, nullptr);
                LineTo(hdc, maxW * CELL_SIZE, i * CELL_SIZE);
            }

            for (DWORD j = 0; j <= maxW; j++)
            {
                MoveToEx(hdc, j * CELL_SIZE, 0, nullptr);
                LineTo(hdc, j * CELL_SIZE, maxH * CELL_SIZE);
            }


            // 단축키 출력 해주기
            TextOut(hdc, 
                (maxW + 1) * CELL_SIZE,
                0,
                L"안녕하세용ㅋ", 6);

            TextOut(hdc,
                (maxW + 1) * CELL_SIZE,
                1 * CELL_SIZE,
                L"왼클릭 : 장애물 그리기", 13);

            TextOut(hdc,
                (maxW + 1) * CELL_SIZE,
                2 * CELL_SIZE,
                L"우클릭 : 장애물 지우기", 13);

            TextOut(hdc,
                (maxW + 1) * CELL_SIZE,
                3 * CELL_SIZE,
                L"1 : 시작지점 설정", 11);

            TextOut(hdc,
                (maxW + 1) * CELL_SIZE,
                4 * CELL_SIZE,
                L"2 : 도착지점 설정", 11);

            TextOut(hdc,
                (maxW + 1) * CELL_SIZE,
                5 * CELL_SIZE,
                L"S : 시작 / 일시정지", 13);

            TextOut(hdc,
                (maxW + 1) * CELL_SIZE,
                6 * CELL_SIZE,
                L"R : 재시작", 7);

            TextOut(hdc,
                (maxW + 1) * CELL_SIZE,
                7 * CELL_SIZE,
                L"L : 맵 불러오기", 10);

            WCHAR str1[32];
            swprintf_s(str1, L"x : %d y : %d", g_x, g_y);
            TextOut(hdc,
                (maxW + 1) * CELL_SIZE,
                8 * CELL_SIZE,
                str1, (int)wcslen(str1));

            WCHAR str2[32];
            swprintf_s(str2, L"행 : %d 열 : %d", g_row, g_col);
            TextOut(hdc,
                (maxW + 1) * CELL_SIZE,
                9 * CELL_SIZE,
                str2, (int)wcslen(str2));

            // pen, brush사용법
            //HBRUSH myBrush = CreateSolidBrush(RGB(255, 0, 0));
            //HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
            //
            //Rectangle(hdc, 10, 10, 100, 100);
            //
            //SelectObject(hdc, oldBrush);
            //DeleteObject(myBrush);

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

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
