#pragma once
#define FPS 60
#include <list>

using namespace std;

class NetworkManager;
class InputManager;
class EventManager;
class Event;
class Object;

typedef unsigned int COLOR; //XXRRGGBB

enum STATE
{
	INITAILIZING,
	WAITING,
	SETTING,
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

	list<Object*> objectList;
	list<Object*> netObjectList;
	
	COLOR playerColor;
	COLOR opponentColor;

	GameManager();
	short FindMinValue(short type); // use in IDGenerator()
public:
	STATE state = INITAILIZING;
	bool isHost;
	unsigned int win, lose;
	

	static GameManager* GetInstance();
	void Initailize();
	void NetInit(bool isHost, char* ipAdress = "");
	void Update();
	void PhysicsUpdate();
	void Draw();
	void KeyEvent(unsigned int value/*가상키코드*/);
	void EventHandling();
	void CollisionCheck();
	void LocalToEventManaget(Event* evt);
	void LocalToEventManaget(short type, Object* owner);
	void LocalToEventManaget(short type, short id_1, short id_2);
	void NetworkToEventManager(Event* evt);
	short IDGenerator(short type/*이벤트타입*/);
	void SetColor(unsigned short xr, unsigned short gb, bool isMe);
	void SetPosition(short id, short posX, short posY, short pDir = 0);
	void CollisionHandling(short id);
	void InsertList(Object* obj, bool isLocal);
	~GameManager();
};