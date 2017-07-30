#pragma once
#include "Object.h"
class Blade : public Object
{
private:
	static short minGage;
	float elapsedTime;
public:
	static void SetAbility(short minGage);
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
	static float castingTime;
	static float durationTime;
	float elapsedTime;
public:
	static void SetAbility(float castingTime, float durationTime);
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
	static float durationTime;
	static short speed;
	float elapsedTime;
public:
	static void SetAbility(float durationTime, short speed);
	Missile(short id, Vector2D pos, short dir);
	Missile(short id, short posX, short posY, short dir);
	virtual void Collide();
	virtual void Update();
	virtual void Draw();
	~Missile();
};