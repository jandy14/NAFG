#pragma once
#define FPS 60
#include <list>
using namespace std;

class NetworkManager;
class InputManager;
class EventManager;
class Event;
class Object;
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
	

	static GameManager* GetInstance();
	void Initailize();									//게임 매니저 초기화
	void NetInit(bool isHost, char* ipAdress = "");		//네트워크 매니저 초기화
	void Update();										//논리 업데이트
	void PhysicsUpdate();								//물리 업데이트
	void Draw();										//오브젝트 그리기
	void KeyEvent(unsigned int value/*가상키코드*/);		//키입력 처리
	void EventHandling();								//이벤트 처리
	void CollisionCheck();								//충돌 체크후 이벤트 생성
	void LocalToEventManager(Event* evt);								//이벤트매니저에게 로컬이벤트 넘김
	void LocalToEventManager(short type, Object* owner);				//이벤트매니저에게 로컬이벤트 넘김
	void LocalToEventManager(short type, short id_1, short id_2);		//이벤트매니저에게 로컬이벤트 넘김
	void NetworkToEventManager(Event* evt);				//이벤트매니저에게 네트워크 이벤트 넘김
	short IDGenerator(short type/*이벤트타입*/);			//오브젝트 아이디 넘버 생성
	void SetColor(unsigned short xr, unsigned short gb, bool isMe);		//플레이어 색지정
	void SetPosition(short id, short posX, short posY, short pDir = 0); //오브젝트 위치 조정
	void CollisionHandling(short id);					//충돌 처리
	void InsertList(Object* obj, bool isLocal);			//오브젝트 리스트에 추가
	void EnterCriticalSection();		//동시 접근 제한 설정
	void LeaveCriticalSection();		//동시 접근 제한 해제
	~GameManager();
};