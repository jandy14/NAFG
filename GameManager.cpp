#include <mutex>
#include "GameManager.h"
#include "InputManager.h"
#include "EventManager.h"
#include "NetworkManager.h"
#include "Player.h"

GameManager* GameManager::GetInstance()
{
	if (!instance)
		instance = new GameManager();

	return instance;
}
GameManager::GameManager() { }

void GameManager::Initailize()
{
	state = STATE::INITAILIZING;
	win = lose = 0;
	playerColor = 0;
	opponentColor = 0;

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
}
void GameManager::PhysicsUpdate()
{
	//only objectList's Pysics()
}
void GameManager::Draw()
{
	//all object's Draw()
}
void GameManager::KeyEvent(unsigned int pValue, bool pIsKeyDown)
{
	inputManager->KeyEvent(pValue, pIsKeyDown);
}
void GameManager::EventHandling()
{
	evtManager->EventHandling();
}
void GameManager::CollisionCheck()
{
	/* need solution */
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
	/* �ۼ� �ʿ� */
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
		return 0;	//�����÷ο�

	return value;
}
short GameManager::IDGenerator(short pType)
{
	//���� ��� ���� �̺�Ʈ�� �ִ� ���� ������� �ʾҴ�(���� �̻��ϰ� �ذ�)
	short value = FindMinValue(pType);
	if (value == 0)
		return 0; // �����÷ο�
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
	//������ �°� ����
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
void GameManager::SetGame()
{
	if (!isAlreadySet)
	{

		COLOR _myColor,_opponentColor;
		//���� �а� �����ϱ�

		short var_1, var_2, var_3, var_4, var_5;
		float tmp;

		//���� �а� ������
		//Event 91 (Player) speed, maxgauge, charging speed, (f)blade delay

		LocalToEventManager(new Event(91, var_1, var_2, var_3, var_4, var_5));
		SendEventToNetwork(new Event(91, var_1, var_2, var_3, var_4, var_5));

		//Event 92 (player) dashSpeed, (f)gaugeStopTime, (f)dashTime

		LocalToEventManager(new Event(92, var_1, var_2, var_3, var_4, var_5));
		SendEventToNetwork(new Event(92, var_1, var_2, var_3, var_4, var_5));

		//Event 93 (Blade) min requirement, cost

		LocalToEventManager(new Event(93, var_1, var_2, 0, 0, 0));
		SendEventToNetwork(new Event(93, var_1, var_2, 0, 0, 0));

		//Event 94 (Ball) (f)castingTime, (f)durationTime, cost

		LocalToEventManager(new Event(94, var_1, var_2, var_3, var_4, var_5));
		SendEventToNetwork(new Event(94, var_1, var_2, var_3, var_4, var_5));

		//Event 95 (Missile) (f)durationTime, cost

		LocalToEventManager(new Event(95, var_1, var_2, var_3, 0, 0));
		SendEventToNetwork(new Event(95, var_1, var_2, var_3, 0, 0));

		//Event 96 (Start Setting) host X, host Y, Guest X, Guest Y, StartGauge

		LocalToEventManager(new Event(96, var_1, var_2, var_3, var_4, var_5));
		SendEventToNetwork(new Event(96, var_1, var_2, var_3, var_4, var_5));

		//Event 00 (GameReady)
		LocalToEventManager(new Event(00, 0, 0, 0, 0, 0));
		SendEventToNetwork(new Event(00, 0, 0, 0, 0, 0));

		isAlreadySet = true;
	}
}
void GameManager::GameReady()
{
	state = STATE::READY;

	//����Ʈ �ʱ�ȭ
	ResetObjectList();
	//�̺�Ʈ �ʱ�ȭ
	ResetEventList();

	//��뿡�� �غ�Ϸ���¸� ����
	SendEventToNetwork(new Event(01, 0, 0, 0, 0, 0));
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
	for(;!netObjectList.empty;)
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

	//�÷��̾� ����
	Vector2D myPoint;
	short id;
	if(isHost)
		myPoint = hostPoint;
	else
		myPoint = guestPoint;
	id = IDGenerator(10);
	LocalToEventManager(new Event(10, id, (short)myPoint.x, (short)myPoint.y, 0, 0));
	//�÷��̾� �����̺�Ʈ Network
	SendEventToNetwork(new Event(20, id + 1000, (short)myPoint.x, (short)myPoint.y, (short)(playerColor>>16), (short)(playerColor)));

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
	return myPlayer->IsDead();
}
void GameManager::DeleteDeadObject()
{
	auto it = objectList.begin();
	for (; it != objectList.end(); ++it)
	{
		if ((*it)->GetID() == 1001)
			continue;
		if ((*it)->IsDead)
		{
			//�ɰŰ����� Ȥ�� ����
			//Debug���� �����Ͱ��� �˾Ƽ� �ٲ������ ��찡 �ִ�.(��ü �������)
			//delete *it;
			//objectList.remove(*it);
			Object* obj = *it;
			objectList.remove(*it);
			delete obj;
		}
	}
	it = netObjectList.begin();
	for (; it != netObjectList.end(); ++it)
	{
		if ((*it)->GetID() == 2001)
			continue;
		if ((*it)->IsDead)
		{
			Object* obj = *it;
			netObjectList.remove(*it);
			delete obj;
		}
	}
}
