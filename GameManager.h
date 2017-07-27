#pragma once
#define FPS 60
#include <list>

using namespace std;

class NetworkManager;
class InputManager;
class EventManager;
class Object;

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

	list<Object> objectList;

	GameManager();
public:
	STATE state;
	bool isHost;
	int win, lose;

	static GameManager* GetInstance();
	void Initailize();
	void NetInit(bool isHost, char* ipAdress = "");
	void Update();
	void PhysicsUpdate();
	void Draw();
	void KeyEvent(unsigned int value/*����Ű�ڵ�*/);
	void InputEventHandling();
	void CollisionCheck();
	void CollisionEventHandling();
	void ToEventManager(Event* evt);

	~GameManager();
};