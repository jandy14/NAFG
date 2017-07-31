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
	static short dashSpeed;
	static short maxGauge;
	static short chargingSpeed;
	static float bladeDelay;
	static float gaugeStopTime;
	static float dashTime;
	short gage;
	float delay;
	float dashTimer;
	bool isUp, isDown, isLeft, isRight;
public:
	Player(short id, Vector2D pos);
	static void SetAbility(short speed, short maxGauge, short chargingSpeed, float bladeDelay);
	static void SetAbility(short dashSpeed, float gaugeStopTime, float dashTime);
	void SetDir(bool isKeyDown, DIRECTION dir);
	void Dash();
	virtual void Collide();
	virtual void Update();
	virtual void Draw();
	~Player();
};
