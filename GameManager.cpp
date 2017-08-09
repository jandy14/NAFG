#include <mutex>
#include "Setting.h" 
#include "GameManager.h"
#include "InputManager.h"
#include "EventManager.h"
#include "NetworkManager.h"
#include "Player.h"
#include "Weapon.h"
#include <Windows.h>

GameManager* GameManager::GetInstance()
{
	if (!instance)
		instance = new GameManager();

	return instance;
}
GameManager::GameManager() { }

void GameManager::Initailize(HWND pHWnd)
{
	RECT crt;
	HDC hdc;

	hWnd = pHWnd;

	GetClientRect(hWnd, &crt);
	hdc = GetDC(hWnd);
	if (hBit == NULL)
	{
		hBit = CreateCompatibleBitmap(hdc, crt.right, crt.bottom);
	}
	Object::SetViewSize(crt.right, crt.bottom);

	state = STATE::INITAILIZING;
	win = lose = 0;
	playerColor = 0;
	opponentColor = 0;

	isNeedReady = false;

	bladeIDNum = 1;
	ballIDNum = 1;
	missileIDNum = 1;

	evtMutex = new std::mutex();
	//list class doesn't need new();

	netManager = new NetworkManager();
	inputManager = new InputManager();
	evtManager = new EventManager();

	inputManager->Initailize();
	evtManager->Initailize();
	//netManager init is in diolog

}
void GameManager::NetInit(bool pIsHost, char* pIPAdress)
{
	isHost = pIsHost;
	netManager->Initailize(isHost, pIPAdress);

	state = STATE::WAITING;
}
void GameManager::Update()
{
	//all object's Update()
	for (Object* o : objectList)
		o->Update();
	for (Object* o : netObjectList)
		o->Update();
	//for (auto it = objectList.begin(); it != objectList.end(); ++it)
	//	(*it)->Update();
	//for (auto it = netObjectList.begin(); it != netObjectList.end(); ++it)
	//	(*it)->Update();
}
void GameManager::PhysicsUpdate()
{
	//only objectList's Physics() detail : myPlayer blade ball missile opponentBlade
	for (Object* o : objectList)
	{

		if (o->GetID() > 2200)
			break;

		o->Physics();

		if (o->GetID() / 100 == 10)
			SendEventToNetwork(new Event(31, o->GetID() + 1000, o->pos.x, o->pos.y, o->dir, ((Player*)o)->GetGauge()));
		if (o->GetID() / 100 == 13)
			SendEventToNetwork(new Event(31, o->GetID() + 1000, o->pos.x, o->pos.y, o->dir, 0));
	}
}
void GameManager::Draw()
{
	//all object's Draw()

	RECT crt;
	HDC hdc, hMemDC;
	HBITMAP oldBit;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	bool isEnemy = false;

	GetClientRect(hWnd, &crt);
	hdc = GetDC(hWnd);

	hMemDC = CreateCompatibleDC(hdc);
	oldBit = (HBITMAP)SelectObject(hMemDC, hBit);

	/* Start Draw */
	FillRect(hMemDC, &crt, GetSysColorBrush(COLOR_WINDOW));

	switch (state)
	{
	case STATE::INITAILIZING:
		SetTextAlign(hMemDC, TA_CENTER);
		TextOut(hMemDC, (crt.right / 2), (crt.bottom / 2), "INITAILIZING", 12);
		break;
	case STATE::WAITING:
		SetTextAlign(hMemDC, TA_CENTER);
		TextOut(hMemDC, (crt.right / 2), (crt.bottom / 2), "WAITING", 7);
		break;
	case STATE::SETTING:
		SetTextAlign(hMemDC, TA_CENTER);
		TextOut(hMemDC, (crt.right / 2), (crt.bottom / 2), "SETTING", 7);
		break;
	case STATE::READY:
		SetTextAlign(hMemDC, TA_CENTER);
		TextOut(hMemDC, (crt.right / 2), (crt.bottom / 2), "READY", 5);
		break;
	case STATE::GAMESTART:
		SetTextAlign(hMemDC, TA_CENTER);
		TextOut(hMemDC, (crt.right / 2), (crt.bottom / 2), "GAMESTART", 9);
		break;
	case STATE::GAMING:

		hPen = CreatePen(PS_INSIDEFRAME, 2, RGB(0,0,0));
		hBrush = CreateSolidBrush(RGB(playerColor >> 16 & 0xff, playerColor >> 8 & 0xff, playerColor & 0xff));
		oldPen = (HPEN)SelectObject(hMemDC, hPen);
		oldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);
		for (Object* o : objectList)
		{
			if (!isEnemy)
			{
				if (o->GetID() > 2000)
				{
					DeleteObject(SelectObject(hMemDC, oldBrush));
					hBrush = CreateSolidBrush(RGB(opponentColor >> 16 & 0xff, opponentColor >> 8 & 0xff, opponentColor & 0xff));
					oldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);
					isEnemy = true;
				}
			}
			o->Draw(hMemDC);
		}
		if (!isEnemy)
		{
			DeleteObject(SelectObject(hMemDC, oldBrush));
			hBrush = CreateSolidBrush(RGB(opponentColor >> 16 & 0xff, opponentColor >> 8 & 0xff, opponentColor & 0xff));
			oldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);
			isEnemy = true;
		}
		for (Object* o : netObjectList)
			o->Draw(hMemDC);

		DeleteObject(SelectObject(hMemDC, oldBrush));
		DeleteObject(SelectObject(hMemDC, oldPen));

		/*hud*/
		char score[19];
		sprintf_s(score, "win : %02d lose : %02d", win, lose);
		SetTextAlign(hMemDC, TA_CENTER);
		TextOut(hMemDC, (crt.right / 2), 20, score, 18);

		if (myPlayer != nullptr)
		{
			short max = myPlayer->GetMaxGauge();

			hBrush = CreateSolidBrush(RGB(255, 255, 255));
			oldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);
			Rectangle(hMemDC, crt.right - 110, 10, crt.right - 10, 40);
			DeleteObject(SelectObject(hMemDC, oldBrush));
			int gauge = myPlayer->GetGauge();
			if (gauge <= max/3)
			{
				hBrush = CreateSolidBrush(RGB(255, 127, 0));
				oldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);
				Rectangle(hMemDC, crt.right - 110, 10, crt.right - 110 + ((float)gauge/max)*300, 40);
				DeleteObject(SelectObject(hMemDC, oldBrush));
			}
			else if (gauge <= max*2/3)
			{
				hBrush = CreateSolidBrush(RGB(255, 127, 0));
				oldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);
				Rectangle(hMemDC, crt.right - 110, 10, crt.right - 10, 40);
				DeleteObject(SelectObject(hMemDC, oldBrush));

				hBrush = CreateSolidBrush(RGB(255, 0, 0));
				oldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);
				Rectangle(hMemDC, crt.right - 110, 10, crt.right - 110 + ((float)gauge/max)*300 - 100, 40);
				DeleteObject(SelectObject(hMemDC, oldBrush));
			}
			else
			{
				hBrush = CreateSolidBrush(RGB(255, 0, 0));
				oldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);
				Rectangle(hMemDC, crt.right - 110, 10, crt.right - 10, 40);
				DeleteObject(SelectObject(hMemDC, oldBrush));

				hBrush = CreateSolidBrush(RGB(255, 0, 180));
				oldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);
				Rectangle(hMemDC, crt.right - 110, 10, crt.right - 110 + ((float)gauge/max)*300 - 200, 40);
				DeleteObject(SelectObject(hMemDC, oldBrush));
			}
		}
		break;
	case STATE::GAMEOVER:
		SetTextAlign(hMemDC, TA_CENTER);
		TextOut(hMemDC, (crt.right / 2), (crt.bottom / 2), "GAMEOVER", 8);
		break;
	}

	/* End Draw */

	SelectObject(hMemDC, oldBit);
	DeleteDC(hMemDC);
	ReleaseDC(hWnd, hdc);

	InvalidateRect(hWnd, NULL, FALSE);
}
void GameManager::KeyEvent(unsigned int pValue, bool pIsKeyDown)
{
	if(myPlayer != nullptr)
		inputManager->KeyEvent(pValue, pIsKeyDown);
}
void GameManager::EventHandling()
{
	evtManager->EventHandling();
}
void GameManager::CollisionCheck()
{
	// player 20 ball line blade half20 missile 10
	for (Object* o : objectList)
	{
		if (o->GetID() / 100 == 10 || o->GetID() / 100 == 13)
		{
			short _oID = o->GetID();
			for (Object* t : objectList)
			{
				short _tID = t->GetID();
				if (_tID == _oID)
					continue;
				if (_oID / 100 == 10 && _tID / 100 == 21)
				{
					if (IsCrash(o->pos, 20, t->pos, 20, t->dir))
					{
						//충돌
						LocalToEventManager(new Event(41, _oID, 0, 0, 0, _tID));
						SendEventToNetwork(new Event(41, _oID + 1000, 0, 0, 0, _tID - 1000));
					}
				}
				else if (_tID / 100 == 22)
				{
					if (!((Ball*)t)->IsAct())
						continue;
					if (IsCrash(o->pos, _oID == 1001? 20:10, t->pos, ((Ball*)t)->GetEndPoint()))
					{
						//충돌
						LocalToEventManager(new Event(41, _oID, 0, 0, 0, _tID));
						SendEventToNetwork(new Event(41, _oID + 1000, 0, 0, 0, _tID - 1000));
					}
				}
			}
			for (Object* t : netObjectList)
			{
				short _tID = t->GetID();
				if (_tID / 100 == 23)
				{
					if (IsCrash(o->pos, _oID == 1001 ? 20 : 10, t->pos, 10))
					{
						//충돌
						LocalToEventManager(new Event(41, _oID, 0, 0, 0, _tID));
						SendEventToNetwork(new Event(41, _oID + 1000, 0, 0, 0, _tID - 1000));
					}
				}
			}
		}
	}
	for (Object* o : netObjectList)
	{
		if (o->GetID() / 100 == 20 || o->GetID() / 100 == 23)
		{
			short _oID = o->GetID();
			for (Object* t : objectList)
			{
				short _tID = t->GetID();
				if (_tID == _oID)
					continue;
				if (_oID / 100 == 20 && _tID / 100 == 11)
				{
					if (IsCrash(o->pos, 20, t->pos, 20, t->dir))
					{
						//충돌
						LocalToEventManager(new Event(41, _oID, 0, 0, 0, _tID));
						SendEventToNetwork(new Event(41, _oID - 1000, 0, 0, 0, _tID + 1000));
					}
				}
				else if (_tID / 100 == 12)
				{
					if (!((Ball*)t)->IsAct())
						continue;
					if (IsCrash(o->pos, _oID == 2001 ? 20 : 10, t->pos, ((Ball*)t)->GetEndPoint()))
					{
						//충돌
						LocalToEventManager(new Event(41, _oID, 0, 0, 0, _tID));
						SendEventToNetwork(new Event(41, _oID - 1000, 0, 0, 0, _tID + 1000));
					}
				}
				else if (_tID / 100 == 13)
				{
					if (IsCrash(o->pos, _oID == 2001 ? 20 : 10, t->pos, 10))
					{
						//충돌
						LocalToEventManager(new Event(41, _oID, 0, 0, 0, _tID));
						SendEventToNetwork(new Event(41, _oID - 1000, 0, 0, 0, _tID + 1000));
					}
				}
			}
		}
	}
}
void GameManager::LocalToEventManager(Event* pEvt)
{
	evtManager->MakeEvent(pEvt);
}
void GameManager::LocalToEventManager(short pType, Object* pOwner)
{
	evtManager->MakeEvent(pType, pOwner);

}
void GameManager::LocalToEventManager(short pType, short pID_1, short pID_2)
{
	evtManager->MakeEvent(pType, pID_1, pID_2);
}
void GameManager::NetworkToEventManager(Event* pEvt)
{
	evtManager->MakeNetEvent(pEvt);
}
GameManager::~GameManager()
{
	delete netManager;
	delete inputManager;
	delete evtManager;

	ResetObjectList();

	delete evtMutex;
}
short GameManager::FindMinValue(short pType)
{
	// short value = 1;
	// short objID;
	// if (pType == 23 || pType == 20)
	// {
	// 	for (auto i = netObjectList.begin(); i != netObjectList.end(); ++i)
	// 	{
	// 		objID = (*i)->GetID();
	// 		if (objID > pType * 100 && objID < (pType + 1) * 100)
	// 		{
	// 			if (objID == pType * 100 + value)
	// 				++value;
	// 			else
	// 				break;
	// 		}
	// 	}
	// }
	// else
	// {
	// 	for (auto i = objectList.begin(); i != objectList.end(); ++i)
	// 	{
	// 		objID = (*i)->GetID();
	// 		if (objID > pType * 100 && objID < (pType + 1) * 100)
	// 		{
	// 			if (objID == pType * 100 + value)
	// 				++value;
	// 			else
	// 				break;
	// 		}
	// 	}
	// }
	short value;
	if(pType == 10)
		return 1;
	else if(pType == 11)
	{
		value = bladeIDNum;
		++bladeIDNum;
		if(bladeIDNum == 100)
			bladeIDNum = 1;
	}
	else if(pType == 12)
	{
		value = ballIDNum;
		++ballIDNum;
		if(ballIDNum == 100)
			ballIDNum = 1;
	}
	else if(pType == 13)
	{
		value = missileIDNum;
		++missileIDNum;
		if(missileIDNum == 100)
			missileIDNum = 1;
	}

	if (value == 100)
		return 0;	//오버플로우

	return value;
}
short GameManager::IDGenerator(short pType)
{
	//변경 요망 현재 이벤트에 있는 값은 고려되지 않았다(조금 이상하게 해결)
	short value = FindMinValue(pType);
	if (value == 0)
		return 0; // 오버플로우
	return pType * 100 + value;
}
void GameManager::SetColor(unsigned short pXR, unsigned short pGB, bool pIsMe)
{
	if (pIsMe)
		playerColor = (COLOR)((unsigned int)pXR << 16 | pGB);
	else
	{
		if(opponentColor == 0)
			opponentColor = (COLOR)((unsigned int)pXR << 16 | pGB);
	}
}
void GameManager::SetPosition(short pID, short pPosX, short pPosY, short pDir)
{
	for (auto it = netObjectList.begin(); it != netObjectList.end(); ++it)
	{
		if ((*it)->GetID() == pID)
		{
			(*it)->SetPosition(pPosX, pPosY);
			(*it)->SetDir(pDir);
			break;
		}
	}
}
void GameManager::CollisionHandling(short pID)
{
	if ((pID / 100) == 20 || (pID / 100) == 23)
	{
		for (auto it = netObjectList.begin(); it != netObjectList.end(); ++it)
		{
			if ((*it)->GetID() == pID)
			{
				(*it)->Collide();
				break;
			}
		}
	}
	else
	{
		for (auto it = objectList.begin(); it != objectList.end(); ++it)
		{
			if ((*it)->GetID() == pID)
			{
				(*it)->Collide();
				break;
			}
		}
	}
}
void GameManager::InsertList(Object* pObj, bool pIsLocal)
{
	//순서에 맞게 저장
	//파라미터가 좀 쓸모가 없게 됐다.
	if (pObj->GetID() / 100 == 20 || pObj->GetID() / 100 == 23)
	{
		if (netObjectList.begin() == netObjectList.end())
		{
			netObjectList.push_back(pObj);
			return;
		}
		for (auto it = netObjectList.begin(); it != netObjectList.end(); ++it)
		{
			if (pObj->GetID() < (*it)->GetID())
			{
				netObjectList.insert(it, pObj);
				return;
			}
		}
		netObjectList.push_back(pObj);
		return;
	}
	else
	{
		if (objectList.begin() == objectList.end())
		{
			objectList.push_back(pObj);
			return;
		}
		for (auto it = objectList.begin(); it != objectList.end(); ++it)
		{
			if (pObj->GetID() < (*it)->GetID())
			{
				objectList.insert(it, pObj);
				return;
			}
		}
		objectList.push_back(pObj);
		return;
	}
}
void GameManager::EnterCriticalSection()
{
	evtMutex->lock();
}
void GameManager::LeaveCriticalSection()
{
	evtMutex->unlock();
}
void GameManager::SendEventToNetwork(Event* evt)
{
	netManager->SendEvent(evt);
}
void GameManager::SetPlayer(Player* pPlayer)
{
	myPlayer = pPlayer;
}
Player* GameManager::GetPlayer()
{
	return myPlayer;
}
Object* GameManager::GetOpponent()
{
	Object* op = netObjectList.front();
	if(op->GetID() == 2001)
		return netObjectList.front();
	return nullptr;
}
void GameManager::SetGame()
{
	if (!isAlreadySet)
	{

		short var_1, var_2, var_3, var_4, var_5;
		int v[5];
		float tmp_1, tmp_2;
		FILE* f;
		fopen_s(&f, "GameSetting.txt", "rt");

		COLOR _myColor,_opponentColor;
		//내용 읽고 저장하기
		fscanf_s(f, "%*s : %x\n%*s : %x\n", &_myColor, &_opponentColor);
		if (_opponentColor >= 0x1000000)
			opponentColor = 0;
		else
			opponentColor = _opponentColor;
		playerColor = _myColor;

		if (!isHost)
		{
			fclose(f);
			isAlreadySet = true;
			return;
		}
		//내용 읽고 보내기
		//Event 91 (Player) speed, maxgauge, charging speed, (f)blade delay
		fscanf_s(f, "%*s : %d\n%*s : %d\n%*s : %d\n%*s : %f\n", &v[0], &v[1], &v[2], &tmp_1);
		var_1 = (short)v[0];
		var_2 = (short)v[1];
		var_3 = (short)v[2];
		var_4 = (short)((*((unsigned int*)&tmp_1) >> 16) & 0xffff);
		var_5 = (short)(*((unsigned int*)&tmp_1) & 0xffff);
		LocalToEventManager(new Event(91, var_1, var_2, var_3, var_4, var_5));
		SendEventToNetwork(new Event(91, var_1, var_2, var_3, var_4, var_5));

		//Event 92 (player) dashSpeed, (f)gaugeStopTime, (f)dashTime
		fscanf_s(f, "%*s : %d\n%*s : %f\n%*s : %f\n", &v[0], &tmp_1, &tmp_2);
		var_1 = (short)v[0];
		var_2 = (short)((*((unsigned int*)&tmp_1) >> 16) & 0xffff);
		var_3 = (short)(*((unsigned int*)&tmp_1) & 0xffff);
		var_4 = (short)((*((unsigned int*)&tmp_2) >> 16) & 0xffff);
		var_5 = (short)(*((unsigned int*)&tmp_2) & 0xffff);
		LocalToEventManager(new Event(92, var_1, var_2, var_3, var_4, var_5));
		SendEventToNetwork(new Event(92, var_1, var_2, var_3, var_4, var_5));

		//Event 93 (Blade) min requirement, cost		&& DashCost
		fscanf_s(f, "%*s : %d\n%*s : %d\n%*s : %d\n", &v[0], &v[1], &v[2]);
		var_1 = (short)v[0];
		var_2 = (short)v[1];
		var_3 = (short)v[2];
		LocalToEventManager(new Event(93, var_1, var_2, var_3, 0, 0));
		SendEventToNetwork(new Event(93, var_1, var_2, var_3, 0, 0));

		//Event 94 (Ball) (f)castingTime, (f)durationTime, cost
		fscanf_s(f, "%*s : %f\n%*s : %f\n%*s : %d\n", &tmp_1, &tmp_2, &v[4]);
		var_1 = (short)((*((unsigned int*)&tmp_1) >> 16) & 0xffff);
		var_2 = (short)(*((unsigned int*)&tmp_1) & 0xffff);
		var_3 = (short)((*((unsigned int*)&tmp_2) >> 16) & 0xffff);
		var_4 = (short)(*((unsigned int*)&tmp_2) & 0xffff);
		var_5 = (short)v[4];
		LocalToEventManager(new Event(94, var_1, var_2, var_3, var_4, var_5));
		SendEventToNetwork(new Event(94, var_1, var_2, var_3, var_4, var_5));

		//Event 95 (Missile) (f)durationTime, speed, cost
		fscanf_s(f, "%*s : %f\n%*s : %d\n%*s : %d\n", &tmp_1, &v[2], &v[3]);
		var_1 = (short)((*((unsigned int*)&tmp_1) >> 16) & 0xffff);
		var_2 = (short)(*((unsigned int*)&tmp_1) & 0xffff);
		var_3 = (short)v[2];
		var_4 = (short)v[3];
		LocalToEventManager(new Event(95, var_1, var_2, var_3, var_4, 0));
		SendEventToNetwork(new Event(95, var_1, var_2, var_3, var_4, 0));

		//Event 96 (Start Setting) host X, host Y, Guest X, Guest Y, StartGauge
		fscanf_s(f, "%*s : %d\n%*s : %d\n%*s : %d\n%*s : %d\n%*s : %d", &v[0], &v[1], &v[2], &v[3], &v[4]);
		var_1 = (short)v[0];
		var_2 = (short)v[1];
		var_3 = (short)v[2];
		var_4 = (short)v[3];
		var_5 = (short)v[4];
		LocalToEventManager(new Event(96, var_1, var_2, var_3, var_4, var_5));
		SendEventToNetwork(new Event(96, var_1, var_2, var_3, var_4, var_5));

		fclose(f);

		//Event 00 (GameReady)
		LocalToEventManager(new Event(00, 0, 0, 0, 0, 0));
		SendEventToNetwork(new Event(00, 0, 0, 0, 0, 0));

		isAlreadySet = true;
	}
}
void GameManager::GameReady()
{

	//리스트 초기화
	ResetObjectList();
	//이벤트 초기화
	ResetEventList();
}
void GameManager::ResetObjectList()
{
	Object* obj;
	for(;!objectList.empty();)
	{
		obj = objectList.front();
		objectList.pop_front();
		delete obj;
	}
	for(;!netObjectList.empty();)
	{
		obj = netObjectList.front();
		netObjectList.pop_front();
		delete obj;
	}
}
void GameManager::ResetEventList()
{
	evtManager->ResetEventList();
}
void GameManager::GameStart()
{
	state = STATE::GAMESTART;

	myPlayer = nullptr;
	Vector2D myPoint;
	short id;
	if(isHost)
		myPoint = hostPoint;
	else
		myPoint = guestPoint;

	id = IDGenerator(10);
	//플레이어 생성
	LocalToEventManager(new Event(10, id, (short)myPoint.x, (short)myPoint.y, 0, 0));
	//플레이어 생성이벤트 Network
	SendEventToNetwork(new Event(20, id + 1000, (short)myPoint.x, (short)myPoint.y, (short)(playerColor>>16), (short)(playerColor)));

	SendEventToNetwork(new Event(01, 0, 0, 0, 0, 0));

	state = STATE::GAMING;
}
void GameManager::GameOver(bool pIsWin)
{
	if(pIsWin)
		++win;
	else
		++lose;
	if(state != STATE::GAMEOVER)
	{
		state = STATE::GAMEOVER;
		SendEventToNetwork(new Event(00, 0, 0, 0, 0, 0));
	}
}
bool GameManager::PlayerIsDied()
{
	if (myPlayer == nullptr)
		return false;
	return myPlayer->IsDead();
}
void GameManager::DeleteDeadObject()
{
	auto it = objectList.begin();
	for (; it != objectList.end(); ++it)
	{
		if ((*it)->GetID() == 1001)
			continue;
		if ((*it)->IsDead())
		{
			//될거같은데 혹시 몰라서
			//Debug모드는 포인터값을 알아서 바꿔버리는 경우가 있다.(객체 사라질때)
			//delete *it;
			//objectList.remove(*it);	//안된다
			Object* obj = *it;
			auto iter = it;
			--it;
			objectList.remove(*iter);
			delete obj;
		}
	}
	it = netObjectList.begin();
	for (; it != netObjectList.end(); ++it)
	{
		if ((*it)->GetID() == 2001)
			continue;
		if ((*it)->IsDead())
		{
			Object* obj = *it;
			auto iter = it;
			--it;
			netObjectList.remove(*iter);
			delete obj;
		}
	}
}
bool GameManager::SpendGauge(short pType)
{
	short _cost;
	short _gauge;
	switch (pType)
	{
	case 11:
		_cost = bladeCost;
		break;
	case 12:
		_cost = ballCost;
		break;
	case 13:
		_cost = missileCost;
		break;
	case 14:
		_cost = dashCost;
	}
	
	_gauge = myPlayer->GetGauge();
	
	if (pType == 11)
	{
		if (_gauge < bladeMinRequirement)
			return false;
	}

	if (_gauge > _cost)
	{
		myPlayer->SetGauge(_gauge - _cost);
		return true;
	}
	else
		return false;
}
HBITMAP GameManager::GetBitMap()
{
	return hBit;
}
void GameManager::SetDir(short pX, short pY)
{
	if (myPlayer == nullptr)
		return;
	myPlayer->SetLookPoint(Vector2D(pX, pY));
}
bool GameManager::IsCrash(Vector2D myPos, short mySize, Vector2D targetPos, short targetSize)
{
	return myPos.Distance(targetPos) < mySize + targetSize;
}
bool GameManager::IsCrash(Vector2D myPos, short mySize, Vector2D startPoint, Vector2D endPoint)
{
	if (IsCrash(myPos, mySize, startPoint, 0))
		return true;
	if (IsCrash(myPos, mySize, endPoint, 0))
		return true;

	double x;
	double y;

	if (endPoint.x == startPoint.x)
	{
		x = startPoint.x;
		y = myPos.y;

		double smallY = startPoint.y < endPoint.y ? startPoint.y : endPoint.y;
		double bigY = startPoint.y >= endPoint.y ? startPoint.y : endPoint.y;
		if (!(y > smallY && y < bigY))
			return false;
	}
	else if (endPoint.y == startPoint.y)
	{
		x = myPos.x;
		y = startPoint.y;

		double smallX = startPoint.x < endPoint.x ? startPoint.x : endPoint.y;
		double bigX = startPoint.x >= endPoint.x ? startPoint.x : endPoint.y;
		if (!(x > smallX && x < bigX))
			return false;
	}
	else
	{
		double lean = (endPoint.y - startPoint.y) / (endPoint.x - startPoint.x);
		double b = (-lean * startPoint.x) + startPoint.y;
		double c = (myPos.x * 1 / lean) + myPos.y;

		x = b - c;
		y = (b / -lean) + (-lean * c);
		x *= (-lean / (lean * lean + 1));
		y *= (-lean / (lean * lean + 1));

		double smallX = startPoint.x < endPoint.x ? startPoint.x : endPoint.x;
		double bigX = startPoint.x >= endPoint.x ? startPoint.x : endPoint.x;
		if (!(x > smallX && x < bigX))
			return false;
	}
	return IsCrash(myPos, mySize, Vector2D((float)x, (float)y), 0);
}
bool GameManager::IsCrash(Vector2D myPos, short mySize, Vector2D targetPos, short targetSize, short targetDir)
{
	if (IsCrash(myPos, mySize, targetPos, targetSize))
	{
		short dir = targetPos.Direction(myPos);
		dir = dir < 0 ? dir + 360 : dir;
		targetDir = targetDir < 0 ? targetDir + 360 : targetDir;
		short diff = dir - targetDir;

		for (; diff > 180; diff -= 360);
		for (; diff < -180; diff += 360);
		
		if (diff <= 90)
			return true;
		else
			return IsCrash(myPos, mySize, targetPos, targetSize - targetSize*((diff - 90) / 90));
	}
	else
		return false;
}
GameManager* GameManager::instance;