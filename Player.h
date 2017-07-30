#pragma once
#include "Object.h"

enum class DIRECTION
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
	static short speed;
	static short maxGage;
	static short chargeSpeed;
	static float bladeDelay;
	short gage;
	float delay;
	float dashTime;
	bool isUp, isDown, isLeft, isRight;
public:
	Player(Vector2D pPos) { pos = pPos; }
	static void SetAbility(short speed, short maxGage, short chargeSpeed, float delay);
	void SetDir(bool isKeyDown, DIRECTION dir);
	void Dash();
	virtual void Collide();
	virtual void Update();
	virtual void Draw();
	~Player();
};