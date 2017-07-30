#pragma once
#include <list>
#include "GameManager.h"
#include "Event.h"
#include "Object.h"

using namespace std;

class EventManager
{
private:
	GameManager* gm;
	list<Event*> evtList;
	list<Event*> netEvtList;
	void LocalEventHandling();
	void NetworkEventHandling();
public:
	void Initailize();
	void EventHandling();
	void MakeEvent(Event* evt);
	void MakeEvent(short type, Object* owner);			// 키누름용
	void MakeEvent(short type, short id_1, short id_2);	//충돌용
	void MakeNetEvent(Event* evt);
};

//받은 이벤트의 id는 송신자측에서 이미 변환되어서 오니 바꿀 필요없다.