#include "EventManager.h"

void EventManager::Initailize()
{
	gm = GameManager::GetInstance();
}
void EventManager::LocalEventHandling()
{
	Object* obj;
	Event* evt;
	for (;!evtList.empty();)
	{
		evt = evtList.front();
		obj = evt->EventProcess();
		if (obj != nullptr)
			gm->InsertList(obj, true);
		evtList.pop_front();
		delete evt;
	}
}
void EventManager::NetworkEventHandling()
{
	Object* obj;
	Event* evt;
	gm->EnterCriticalSection();
	
	for (; !netEvtList.empty();)
	{
		evt = netEvtList.front();
		obj = evt->EventProcess();
		if (obj != nullptr)
			gm->InsertList(obj, false);
		netEvtList.pop_front();
		delete evt;
	}
	
	gm->LeaveCriticalSection();
}
void EventManager::EventHandling()
{
	//각이벤트마다 가상함수로 했어야했는데 실수다.지금하기엔 좀 귀찮다.
	LocalEventHandling();
	NetworkEventHandling();
}
void EventManager::MakeEvent(Event* pEvt)
{
	evtList.push_back(pEvt);
}
void EventManager::MakeEvent(short pType, Object* pOwner)
{
	short id = gm->IDGenerator(pType);

	Event* evt = new Event(pType, id, (short)pOwner->pos.x, (short)pOwner->pos.y, pOwner->dir, 0);
	evtList.push_back(evt);

	gm->SendEventToNetwork(new Event(pType + 10, id + 1000, (short)pOwner->pos.x, (short)pOwner->pos.y, pOwner->dir, 0));

}
void EventManager::MakeEvent(short pType, short pID_1, short pID_2)
{
	Event* evt = new Event(pType, pID_1, 0, 0, 0, pID_2);
	evtList.push_back(evt);
}
void EventManager::MakeNetEvent(Event* pEvt)
{
	gm->EnterCriticalSection();

	netEvtList.push_back(pEvt);
	
	gm->LeaveCriticalSection();
}