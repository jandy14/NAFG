#pragma once
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

struct HBITMAP__;
struct HWND__;

typedef HBITMAP__* HBITMAP;
typedef HWND__* HWND;
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
	FINISH,
	END
};
class GameManager
{
private:
	static GameManager * instance;
	NetworkManager* netManager;
	InputManager* inputManager;
	EventManager* evtManager;

	std::mutex* evtMutex;	//critical section control

	HWND hWnd;				//draw window handle
	HBITMAP hBit;			//bitmap handle

	Player* myPlayer;

	list<Object*> objectList;
	list<Object*> netObjectList;
	
	COLOR playerColor;
	COLOR opponentColor;

	bool isAlreadySet;
	bool isNeedReady;

	short bladeIDNum;
	short ballIDNum;
	short missileIDNum;

	GameManager();
	short FindMinValue(short type); // use in IDGenerator()
	void ResetObjectList(); //use in GameReady()
	void ResetEventList();	//use in GameReady()
public:
	STATE state = STATE::INITAILIZING;
	bool isHost;
	unsigned int win, lose;
	short bladeCost, ballCost, missileCost, dashCost;
	short bladeMinRequirement;
	short startGauge;
	Vector2D hostPoint, guestPoint;

	//초기 설정 값 변수

	static GameManager* GetInstance();
	void Initailize(HWND hWnd);									//게임 매니저 초기화
	void NetInit(bool isHost, char* ipAdress = "");		//네트워크 매니저 초기화
	void Update();										//논리 업데이트
	void PhysicsUpdate();								//물리 업데이트
	void Draw();										//오브젝트 그리기
	void KeyEvent(unsigned int value, bool isKeyDown/*가상키코드*/);		//키입력 처리
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
	void SendEventToNetwork(Event* evt);	//이벤트 소켓 전송
	void SetPlayer(Player* player);
	Player* GetPlayer();
	Object* GetOpponent();
	void SetGame();
	void GameReady();
	void GameStart();
	void GameOver(bool isWin);
	bool PlayerIsDied();
	void DeleteDeadObject();
	bool SpendGauge(short type);
	HBITMAP GetBitMap();
	~GameManager();
	bool IsNeedReady() { return isNeedReady; }
	void SetIsNeedReady(bool pIsNeedReady) { isNeedReady = pIsNeedReady; }
	void SetDir(short x, short y);
	bool IsCrash(Vector2D myPos, short mySize, Vector2D targetPos, short targetSize);
	bool IsCrash(Vector2D myPos, short mySize, Vector2D startPoint, Vector2D endPoint);
	bool IsCrash(Vector2D myPos, short mySize, Vector2D targetPos, short targetSize, short targetDir);
};
