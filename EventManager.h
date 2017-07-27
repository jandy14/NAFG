#pragma once
#include <list>
#include "Event.h"
#include "Object.h"

using namespace std;

class EventManager
{
private:
	list<Event> evtList;
	list<Event> netEntList;
public:
	void EventHandling();
	void MakeEvent(Event evt);
	void MakeEvent(short type, Object* owner);
	void MakeEvent(short type, short id_1, short id_2);
};