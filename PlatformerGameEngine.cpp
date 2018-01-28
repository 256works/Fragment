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
			if (msg.message == WM_QUIT)	// ���� �� ���ѷ��� ĵ��
			{
				break;
			}

			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);	// Ű����, ���콺 �� �Է� message ó��
				DispatchMessage(&msg);	// message window�� ����
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
   SetRect(&crt, 0, 0, GAME_WIDTH, GAME_HEIGHT);		// ���� ȭ�� ������ ���� RECT ����
   AdjustWindowRect(&crt, WS_CAPTION | WS_SYSMENU, FALSE);	// ������ �������� RETC ����, ������ RECT�� ������ â ũ�⸦ �����Ͽ� �Ʒ����� ������ ������ â ��ġ ��(left, top, right, bottom)
														// �������� �� ������(���� ����� ������) ����, client rect�� Ȯ���غ��� ����� ��ġ���� Ȯ���� �� ����.

   // GetSystemMetrics�Լ��� ���� ��ü ȭ�� �ػ� �߽��� �������� â�� �߾ӿ� ��ġ��ų ��ǥ�� �޾ƿ�.
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