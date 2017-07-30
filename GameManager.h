#pragma once
#define FPS 60
#include <list>
#include "Vector2D.h"
using namespace std;

class NetworkManager;
class InputManager;
class EventManager;
class Event;
class Object;
class Player;

namespace std
{
	class mutex;
}
typedef unsigned int COLOR; //XXRRGGBB

enum class STATE
{
	INITAILIZING,
	WAITING,
	SETTING,
	READY,
	GAMESTART,
	GAMING,
	GAMEOVER,
	END
};
class GameManager
{
private:
	static GameManager * instance;
	NetworkManager* netManager;
	InputManager* inputManager;
	EventManager* evtManager;

	std::mutex* evtMutex;
	
	Player* myPlayer;
	
	list<Object*> objectList;
	list<Object*> netObjectList;
	
	COLOR playerColor;
	COLOR opponentColor;

	GameManager();
	short FindMinValue(short type); // use in IDGenerator()
public:
	STATE state = STATE::INITAILIZING;
	bool isHost;
	unsigned int win, lose;
	short bladeCost, ballCost, missileCost;
	Vector2D hostPoint, guestPoint;

	//�ʱ� ���� �� ����

	static GameManager* GetInstance();
	void Initailize();									//���� �Ŵ��� �ʱ�ȭ
	void NetInit(bool isHost, char* ipAdress = "");		//��Ʈ��ũ �Ŵ��� �ʱ�ȭ
	void Update();										//�� ������Ʈ
	void PhysicsUpdate();								//���� ������Ʈ
	void Draw();										//������Ʈ �׸���
	void KeyEvent(unsigned int value, bool isKeyDown/*����Ű�ڵ�*/);		//Ű�Է� ó��
	void EventHandling();								//�̺�Ʈ ó��
	void CollisionCheck();								//�浹 üũ�� �̺�Ʈ ����
	void LocalToEventManager(Event* evt);								//�̺�Ʈ�Ŵ������� �����̺�Ʈ �ѱ�
	void LocalToEventManager(short type, Object* owner);				//�̺�Ʈ�Ŵ������� �����̺�Ʈ �ѱ�
	void LocalToEventManager(short type, short id_1, short id_2);		//�̺�Ʈ�Ŵ������� �����̺�Ʈ �ѱ�
	void NetworkToEventManager(Event* evt);				//�̺�Ʈ�Ŵ������� ��Ʈ��ũ �̺�Ʈ �ѱ�
	short IDGenerator(short type/*�̺�ƮŸ��*/);			//������Ʈ ���̵� �ѹ� ����
	void SetColor(unsigned short xr, unsigned short gb, bool isMe);		//�÷��̾� ������
	void SetPosition(short id, short posX, short posY, short pDir = 0); //������Ʈ ��ġ ����
	void CollisionHandling(short id);					//�浹 ó��
	void InsertList(Object* obj, bool isLocal);			//������Ʈ ����Ʈ�� �߰�
	void EnterCriticalSection();		//���� ���� ���� ����
	void LeaveCriticalSection();		//���� ���� ���� ����
	void SendEventToNetwork(Event* evt);	//�̺�Ʈ ���� ����
	Player* GetPlayer();
	void SetObjectAbility();
	void GameReady();
	void GameStart();
	~GameManager();
};