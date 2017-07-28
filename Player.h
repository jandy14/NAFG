#pragma once
#include "Object.h"

enum DIRECTION
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	END
};

class Player : public Object
{
private:
	short gage;
	unsigned int color;
	float delay;
	
	bool isUp, isDown, isLeft, isRight;
public:
	Player(Vector2D pos, int color);
	void SetDir(bool isKeyDown, DIRECTION dir);
	virtual void Collide();
	virtual void Update();
	virtual void Draw();
	~Player();
};