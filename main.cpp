#include <Windows.h>
#include "Setting.h"
#include "resource.h"
#include "GameManager.h"
#include "Event.h"
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("NAFG");

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
	GameManager * gm = GameManager::GetInstance();
	while (1)
	{
		startTime = timeGetTime();

		/*  메세지 처리  */
		while (PeekMessage(&Message, NULL, 0, 0, PM_NOREMOVE))
		{
			GetMessage(&Message, NULL, 0, 0);
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		if (gm->state == STATE::INITAILIZING)
		{
			gm->Draw();
		}
		else if (gm->state == STATE::WAITING)
		{
			gm->Draw();
		}
		else if (gm->state == STATE::SETTING)
		{
			gm->SetGame();

			gm->EventHandling();
			gm->Draw();
		}
		else if (gm->state == STATE::READY)
		{
			//GAMESTART이벤트 받으려면 해야한다
			if (gm->IsNeedReady())
			{
				gm->GameReady();
				gm->SetIsNeedReady(false);
			}
			if (!gm->IsNeedReady())
			{
				gm->SendEventToNetwork(new Event(01, 0, 0, 0, 0, 0));
				gm->EventHandling();
			}
		}
		else if (gm->state == STATE::GAMESTART)
		{
			gm->Draw();
		}
		else if (gm->state == STATE::GAMING)
		{
			/*  게임 루프  */
			gm->EventHandling();//중요해서 두번 넣음
			gm->PhysicsUpdate();
			if (gm->isHost)
				gm->CollisionCheck();
			gm->EventHandling();//중요해서 두번 넣음
			gm->DeleteDeadObject();
			gm->Update();
			gm->Draw();

			if(gm->PlayerIsDied())
			{
				//죽었으면 게임 오버 보냄
				//Event 02 승리는 1 패배는 0
				gm->LocalToEventManager(new Event(02,0,0,0,0,0));
				gm->SendEventToNetwork(new Event(02,1,0,0,0,0));
			}
		}
		else if (gm->state == STATE::GAMEOVER)
		{
			//READY이벤트 받으려면 해야한다
			gm->EventHandling();
			gm->Draw();
		}
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
			GameManager::GetInstance()->NetInit(true);
			EndDialog(hDlg, 0);
			return TRUE;
		case IDGUEST:
			char ipAdress[16];
			GetDlgItemText(hDlg, IDC_IPADRESS, ipAdress, 16);
			GameManager::GetInstance()->NetInit(false, ipAdress);
			EndDialog(hDlg, 0);
			return TRUE;
		}
		break;
	}
	return FALSE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc, hMemDC;
	PAINTSTRUCT ps;
	HBITMAP oldBit;
	RECT crt;

	GameManager* gm = GameManager::GetInstance();

	switch (iMessage)
	{
	case WM_CREATE:
		//GameManager Init
		gm->Initailize(hWnd);//게임매니저 생성및 초기화
							 //인풋값 설정, 이벤트 리스트 초기화
		return 0;
	case WM_KEYDOWN:

		if (gm->state == STATE::GAMING)
			gm->KeyEvent(wParam, true);
		return 0;

	case WM_KEYUP:

		if (gm->state == STATE::GAMING)
			gm->KeyEvent(wParam, false);
		return 0;

	case WM_LBUTTONDOWN:

		if (gm->state == STATE::GAMING)
			gm->KeyEvent(01, true);
		return 0;

	case WM_RBUTTONDOWN:

		if (gm->state == STATE::GAMING)
			gm->KeyEvent(02, true);
		return 0;
	case WM_MOUSEMOVE:
		if (gm->state == STATE::GAMING)
			gm->SetDir(LOWORD(lParam), HIWORD(lParam));
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &crt);
		hMemDC = CreateCompatibleDC(hdc);
		oldBit = (HBITMAP)SelectObject(hMemDC, gm->GetBitMap());
		BitBlt(hdc, 0, 0, crt.right, crt.bottom, hMemDC, 0, 0, SRCCOPY);
		SelectObject(hMemDC, oldBit);
		DeleteDC(hMemDC);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
