#include "Object.h"
#include "Setting.h"
Object::Object()
{
	isAlive = true;
	velocity.x = 0;
	velocity.y = 0;
}
Object::Object(short pID, Vector2D pPos, short pDir)
{
	id = pID;
	pos = pPos;
	dir = pDir;
	isAlive = true;
	velocity.x = 0;
	velocity.y = 0;
}
Object::Object(short pID, short pPosX, short pPosY, short pDir)
{
	id = pID;
	pos.x = pPosX;
	pos.y = pPosY;
	dir = pDir;
	isAlive = true;
	velocity.x = 0;
	velocity.y = 0;
}
bool Object::IsDead()
{
	return !isAlive;
}
void Object::Physics()
{
	pos.x += (velocity.x * (1.0f / FPS));
	pos.y += (velocity.y * (1.0f / FPS));
}
