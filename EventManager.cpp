#include "EventManager.h"

void EventManager::Initailize()
{
	gm = GameManager::GetInstance();
}
void EventManager::LocalEventHandling()
{
	for (auto it = evtList.begin(); it != evtList.end(); ++it)
	{
		(*it)->EventProcess();
	}
}
void EventManager::NetworkEventHandling()
{
	//접근하기전에 동기화를 해야한다 mutax
	for (auto it = netEvtList.begin(); it != netEvtList.end(); ++it)
	{
		(*it)->EventProcess();
	}
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
	Event* evt = new Event(pType, gm->IDGenerator(pType), (short)pOwner->pos.x, (short)pOwner->pos.y, pOwner->dir, 0);
	evtList.push_back(evt);
}
void EventManager::MakeEvent(short pType, short pID_1, short pID_2)
{
	Event* evt = new Event(pType, pID_1, 0, 0, 0, pID_2);
	evtList.push_back(evt);
}
void EventManager::MakeNetEvent(Event* pEvt)
{
	netEvtList.push_back(pEvt);
}