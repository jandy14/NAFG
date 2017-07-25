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
	WAITING,
	GAMING,
	END
};

class GameManager
{
private:
	static GameManager * instance;
	NetworkManager* netManager;
	InputManager* inputManager;
	EventManager* evtManager;
	STATE state;
	bool isHost;

	list<Object> objectList;

	GameManager();
public:
	static GameManager* GetInstance();
	void Update();
	void PhysicsUpdate();
	void Draw();
	void KeyEvent(int value);
	void CreateConnect(char* ipAdress);
	~GameManager();
};