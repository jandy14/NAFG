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
	Vector2D endPoint;
public:
	static void SetAbility(float castingTime, float durationTime);
	Ball(short id, Vector2D pos, short dir);
	Ball(short id, short posX, short posY, short dir);
	Vector2D GetEndPoint() { return endPoint; }
	bool IsAct() { return elapsedTimer >= castingTime; }
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
	Object* target;
	float elapsedTimer;
public:
	static void SetAbility(float durationTime, short speed);
	Missile(short id, Vector2D pos, short dir, Object* pTarget) : Object(id, pos, dir) { elapsedTimer = 0.0f; target = pTarget; }
	Missile(short id, short posX, short posY, short dir, Object* pTarget) : Object(id, posX, posY, dir) { elapsedTimer = 0.0f; target = pTarget; }
	virtual void Collide();
	virtual void Update();
	virtual void Draw(HDC hdc);
	virtual ~Missile() {}
};