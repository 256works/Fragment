// vGFrame.cpp

#include "stdafx.h"
#include "PlatformerGameEngine.h"

#define MAX_LOADSTRING 100

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

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

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PLATFORMERGAMEENGINE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PLATFORMERGAMEENGINE));

    MSG msg;

	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)	// 종료 시 무한루프 캔슬
			{
				break;
			}

			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);	// 키보드, 마우스 등 입력 message 처리
				DispatchMessage(&msg);	// message window에 전달
			}
		}
		else
		{
			TIME->Update(GAME_FPS);
			GC->UpdateMain();
		}
	}
    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PLATFORMERGAMEENGINE));
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground  = CreateSolidBrush(RGB(0, 0, 0));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PLATFORMERGAMEENGINE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	ShowCursor(CURSOR_VISIBLE);

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;

   RECT crt;
   SetRect(&crt, 0, 0, GAME_WIDTH, GAME_HEIGHT);		// 게임 화면 사이즈 기준 RECT 설정
   AdjustWindowRect(&crt, WS_CAPTION | WS_SYSMENU, FALSE);	// 사이즈 기준으로 RETC 조정, 조정된 RECT는 윈도우 창 크기를 포함하여 아래에서 생성된 윈도우 창 위치 값(left, top, right, bottom)
														// 기준으로 새 윈도우(실제 사용할 윈도우) 생성, client rect를 확인해보면 사이즈가 일치함을 확인할 수 있음.

   // GetSystemMetrics함수를 통해 전체 화면 해상도 중심을 기준으로 창을 중앙에 위치시킬 좌표를 받아옴.
   POINT wndCenterPos = { (GetSystemMetrics(SM_CXSCREEN) / 2 - (crt.right - crt.left) / 2) , (GetSystemMetrics(SM_CYSCREEN) / 2 - (crt.bottom - crt.top) / 2) };

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_CAPTION | WS_SYSMENU,
	   wndCenterPos.x, wndCenterPos.y, crt.right - crt.left, crt.bottom - crt.top, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   //UpdateWindow(hWnd);
   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return GC->MainProc(hWnd, message, wParam, lParam);
}