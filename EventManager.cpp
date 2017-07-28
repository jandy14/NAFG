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
	//�����ϱ����� ����ȭ�� �ؾ��Ѵ� mutax
	for (auto it = netEvtList.begin(); it != netEvtList.end(); ++it)
	{
		(*it)->EventProcess();
	}
}
void EventManager::EventHandling()
{
	//���̺�Ʈ���� �����Լ��� �߾���ߴµ� �Ǽ���.�����ϱ⿣ �� ������.
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