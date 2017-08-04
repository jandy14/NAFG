#include "Object.h"
#include "Setting.h"

void Object::SetViewSize(int pX, int pY)
{
	bottom = pY;
	right = pX;
}
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
void Object::SetDir(short pDir)
{
	dir = pDir;
	if (dir < 0)
		dir += 360;
	else if (dir > 360)
		dir -= 360;
}
bool Object::IsDead()
{
	return !isAlive;
}
void Object::Physics()
{
	pos.x += (velocity.x * (1.0f / FPS));
	pos.y += (velocity.y * (1.0f / FPS));
	if (pos.x < 0)
		pos.x = 0;
	else if (pos.x > right)
		pos.x = right;
	if (pos.y < 0)
		pos.y = 0;
	else if (pos.y > bottom)
		pos.y = bottom;
}
int Object::right;
int Object::bottom;