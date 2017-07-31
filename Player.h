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
	static short maxGauge;
	static short chargeSpeed;
	static float bladeDelay;
	static float gaugeStopTime;
	static float dashTime;
	short gage;
	float delay;
	float dashTimer;
	bool isUp, isDown, isLeft, isRight;
	bool isDied;
public:
	Player(Vector2D pPos) { pos = pPos; }
	static void SetAbility(short speed, short maxGauge, short chargeSpeed, float delay);
	static void SetAbility(short dashSpeed, float gaugeStopTime, float dashTime);
	void SetDir(bool isKeyDown, DIRECTION dir);
	void Dash();
	virtual void Collide();
	virtual void Update();
	virtual void Draw();
	bool IsDied() { return isDied; }
	~Player();
};
