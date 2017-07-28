#pragma once
#include "Object.h"
class Blade : public Object
{
private:
	float elapsedTime;
public:
	Blade(Vector2D pos);
	~Blade();
};

class Ball : public Object
{
private:
	float elapsedTime;
public:
	Ball(Vector2D pos);
	~Ball();
};

class Missile : public Object
{
private:
	float elapsedTime;
public:
	Missile(Vector2D pos);
	~Missile();
};