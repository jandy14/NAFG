#pragma once
#include "Object.h"
class Blade : public Object
{
private:
	static short minRequirement;
	float elapsedTimer;
public:
	static void SetAbility(short minRequirement);
	Blade(short id, Vector2D pos, short dir) : Object(id, pos, dir) { elapsedTimer = 0.0f; }
	Blade(short id, short posX, short posY, short dir) : Object(id, posX, posY, dir) { elapsedTimer = 0.0f; }
	virtual void Collide();
	virtual void Update();
	virtual void Draw(HDC hdc);
	virtual ~Blade() {}
};

class Ball : public Object
{
private:
	static float castingTime;
	static float durationTime;
	float elapsedTimer;
public:
	static void SetAbility(float castingTime, float durationTime);
	Ball(short id, Vector2D pos, short dir) : Object(id, pos, dir) { elapsedTimer = 0.0f; }
	Ball(short id, short posX, short posY, short dir) : Object(id, posX, posY, dir) { elapsedTimer = 0.0f; }
	virtual void Collide();
	virtual void Update();
	virtual void Draw(HDC hdc);
	virtual ~Ball() {}
};

class Missile : public Object
{
private:
	static float durationTime;
	static short speed;
	float elapsedTimer;
public:
	static void SetAbility(float durationTime, short speed);
	Missile(short id, Vector2D pos, short dir) : Object(id, pos, dir) { elapsedTimer = 0.0f; }
	Missile(short id, short posX, short posY, short dir) : Object(id, posX, posY, dir) { elapsedTimer = 0.0f; }
	virtual void Collide();
	virtual void Update();
	virtual void Draw(HDC hdc);
	virtual ~Missile() {}
};