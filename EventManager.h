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
	void MakeEvent(short type, Object* owner);			// Ű������
	void MakeEvent(short type, short id_1, short id_2);	//�浹��
	void MakeNetEvent(Event* evt);
};

//���� �̺�Ʈ�� id�� �۽��������� �̹� ��ȯ�Ǿ ���� �ٲ� �ʿ����.