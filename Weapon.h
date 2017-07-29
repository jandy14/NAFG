#pragma once
#include "Object.h"
class Blade : public Object
{
private:
	float elapsedTime;
public:
	Blade(short id, Vector2D pos, short dir);
	Blade(short id, short posX, short posY, short dir);
	virtual void Collide();
	virtual void Update();
	virtual void Draw();
	~Blade();
};

class Ball : public Object
{
private:
	float elapsedTime;
public:
	Ball(short id, Vector2D pos, short dir);
	Ball(short id, short posX, short posY, short dir);
	virtual void Collide();
	virtual void Update();
	virtual void Draw();
	~Ball();
};

class Missile : public Object
{
private:
	float elapsedTime;
public:
	Missile(short id, Vector2D pos, short dir);
	Missile(short id, short posX, short posY, short dir);
	virtual void Collide();
	virtual void Update();
	virtual void Draw();
	~Missile();
};