#include <mutex>
#include "GameManager.h"
#include "InputManager.h"
#include "EventManager.h"
#include "NetworkManager.h"

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
	short value = 1;
	short objID;
	if (pType == 23 || pType == 20)
	{
		for (auto i = netObjectList.begin(); i != netObjectList.end(); ++i)
		{
			objID = (*i)->GetID();
			if (objID > pType * 100 && objID < (pType + 1) * 100)
			{
				if (objID == pType * 100 + value)
					++value;
				else
					break;
			}
		}
	}
	else
	{
		for (auto i = objectList.begin(); i != objectList.end(); ++i)
		{
			objID = (*i)->GetID();
			if (objID > pType * 100 && objID < (pType + 1) * 100)
			{
				if (objID == pType * 100 + value)
					++value;
				else
					break;
			}
		}
	}
	if (value == 100)
		return 0;	//�����÷ο�

	return value;
}
short GameManager::IDGenerator(short pType)
{
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
		opponentColor = (COLOR)((unsigned int)pXR << 16 | pGB);
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
Player* GameManager::GetPlayer()
{
	return myPlayer;
}
void GameManager::SetObjectAbility()
{
	if (isHost)
	{
		//���볻��

		//���� ������
		/*LocalToEventManager(new Event(91, xxxxxxx));
		SendEventToNetwork(new Event(91, xxxxxxx));
		LocalToEventManager(new Event(92, xxxxxxx));
		SendEventToNetwork(new Event(92, xxxxxxx));
		LocalToEventManager(new Event(93, xxxxxxx));
		SendEventToNetwork(new Event(93, xxxxxxx));
		LocalToEventManager(new Event(94, xxxxxxx));
		SendEventToNetwork(new Event(94, xxxxxxx));
		LocalToEventManager(new Event(00, xxxxxxx));
		SendEventToNetwork(new Event(00, xxxxxxx));*/
	}
}
void GameManager::GameReady()
{
	state = STATE::READY;

	//����Ʈ �ʱ�ȭ
	//�̺�Ʈ �ʱ�ȭ

	//SendEventToNetwork(new Event(01, xxxxxxx));
}
void GameManager::GameStart()
{
	state = STATE::GAMESTART;

	//�÷��̾� ����		 Local

	//LocalToEventManger(new Event(10,)) 
	//�÷��̾� �����̺�Ʈ Network

	state = STATE::GAMING;
}