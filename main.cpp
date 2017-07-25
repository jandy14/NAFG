#include <Windows.h>
#include "resource.h"
#include "GameManager.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("NAFG");

BOOL isHost = TRUE;
char ip[16];

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;
	
	//Create Window
	{
		WndClass.cbClsExtra = 0;
		WndClass.cbWndExtra = 0;
		WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		WndClass.hInstance = hInstance;
		WndClass.lpfnWndProc = WndProc;
		WndClass.lpszClassName = lpszClass;
		WndClass.lpszMenuName = NULL;
		WndClass.style = CS_HREDRAW | CS_VREDRAW;
		RegisterClass(&WndClass);

		hWnd = CreateWindow(lpszClass, lpszClass, WS_MINIMIZEBOX | WS_CAPTION | WS_SYSMENU
			, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL
			, (HMENU)NULL, hInstance, NULL);
		ShowWindow(hWnd, nCmdShow);
	}

	DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgProc);

	int startTime = 0;
	int elapsedTime = 0;
	while (1)
	{
		startTime = timeGetTime();
		
		/*  메세지 처리  */
		while (PeekMessage(&Message,NULL,0,0,PM_NOREMOVE))
		{
			GetMessage(&Message, NULL, 0, 0);
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		/*  게임 루프  */
		//================================//
		//           Game Loop            //
		//================================//

		/*  프레임 유지  */
		elapsedTime += timeGetTime() - startTime;
		if ((1000 / FPS) > elapsedTime)
		{
			Sleep((1000 / FPS) - elapsedTime);
			elapsedTime = 0;
		}
		else //Frame Skipping
			elapsedTime -= (1000 / FPS);
	}

	return (int)Message.wParam;
}


BOOL CALLBACK DlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch (wParam)
		{
		case IDHOST:
			isHost = TRUE;
			EndDialog(hDlg, 0);
			return TRUE;
		case IDGUEST:
			isHost = FALSE;
			GetDlgItemText(hDlg, IDC_IPADRESS, ip, 16);
			EndDialog(hDlg, 0);
			return TRUE;
		}
		break;
	}
	return FALSE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		//GameManager Init
		return 0;
	case WM_KEYDOWN:
		//gameManager의 keyEvent()
		return 0;
	case WM_PAINT:
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}