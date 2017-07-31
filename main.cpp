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

		/*  �޼��� ó��  */
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
			if (gm->isHost)
				gm->SetGame();

			gm->EventHandling();
			gm->Draw();
		}
		else if (gm->state == STATE::READY)
		{
			//GAMESTART�̺�Ʈ �������� �ؾ��Ѵ�
			gm->EventHandling();
		}
		else if (gm->state == STATE::GAMESTART)
		{

		}
		else if (gm->state == STATE::GAMING)
		{
			/*  ���� ����  */
			gm->EventHandling();//�߿��ؼ� �ι� ����
			gm->PhysicsUpdate();
			if (gm->isHost)
				gm->CollisionCheck();
			gm->EventHandling();//�߿��ؼ� �ι� ����
			gm->DeleteDeadObject();
			gm->Update();
			gm->Draw();

			if(gm->PlayerIsDied())
			{
				//�׾����� ���� ���� ����
				//Event 02 �¸��� 1 �й�� 0
				gm->LocalToEventManager(new Event(02,0,0,0,0,0));
				gm->SendEventToNetwork(new Event(02,1,0,0,0,0));
			}
		}
		else if (gm->state == STATE::GAMEOVER)
		{
			//READY�̺�Ʈ �������� �ؾ��Ѵ�
			gm->EventHandling();
		}
		/*  ������ ����  */
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
	switch (iMessage)
	{
	case WM_CREATE:
		//GameManager Init
		GameManager::GetInstance()->Initailize();//���ӸŴ��� ������ �ʱ�ȭ
												 //��ǲ�� ����, �̺�Ʈ ����Ʈ �ʱ�ȭ
		return 0;
	case WM_KEYDOWN:
		{
			GameManager* gm = GameManager::GetInstance();
			if (gm->state == STATE::GAMING)
				gm->KeyEvent(wParam, true);
			return 0;
		}
	case WM_KEYUP:
		{
			GameManager* gm = GameManager::GetInstance();
			if (gm->state == STATE::GAMING)
				gm->KeyEvent(wParam, false);
			return 0;
		}
	case WM_LBUTTONDOWN:
		{
			GameManager* gm = GameManager::GetInstance();
			if (gm->state == STATE::GAMING)
				gm->KeyEvent(01, false);
			return 0;
		}
	case WM_RBUTTONDOWN:
		{
			GameManager* gm = GameManager::GetInstance();
			if (gm->state == STATE::GAMING)
				gm->KeyEvent(02, false);
			return 0;
		}
	/*case WM_PAINT:
		return 0;*/
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
