#pragma once

class Object;

class Event
{
private:
	
	short posX, posY;
	short dir;
	short tmpVar;
public:
	short type;
	short id;

	Event() {}
	Event(short pType, short pID, short pPosX, short pPosY, short pDir, short pTmpVar)
		:type(pType), id(pID), posX(pPosX), posY(pPosY), dir(pDir), tmpVar(pTmpVar) { }
	Object* EventProcess();
	~Event() {}
};