#include "Object.h"

void Object::Pysics()
{

}
Object::Object(short pID, Vector2D pPos, short pDir)
{
	id = pID;
	pos = pPos;
	dir = pDir;
	isAlive = true;
}
Object::Object(short pID, short pPosX, short pPosY, short pDir)
{
	id = pID;
	pos.x = pPosX;
	pos.y = pPosY;
	dir = pDir;
	isAlive = true;
}
bool Object::IsDead()
{
	return !isAlive;
}