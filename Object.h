#pragma once
#include "Vector2D.h"
class Object
{
private:
	short id;
	Vector2D pos;
	Vector2D dir;
	Vector2D velocity;
	//충돌 정보
public:
	Object();
	virtual void Pysics();
	virtual void Update() = 0;
	virtual void Draw() = 0;
	~Object();
};