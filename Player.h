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
	float gaugeFraction;
	short gauge;
	float gaugeStopTimer;
	float delayTimer;
	float dashTimer;
	bool isUp, isDown, isLeft, isRight;
	Vector2D lookPoint;
public:
	Player(short id, Vector2D pos);
	static void SetAbility(short speed, short maxGauge, short chargingSpeed, float bladeDelay);
	static void SetAbility(short dashSpeed, float gaugeStopTime, float dashTime);
	void SetDir(bool isKeyDown, DIRECTION dir);
	void Dash() { dashTimer = dashTime; }
	void GaugeStop() { gaugeStopTimer = gaugeStopTime; }
	void BladeDelay() { delayTimer = bladeDelay; }
	short GetGauge() { return gauge; }
	void SetGauge(short value);
	void SetLookDir(short pDir) { dir = pDir; }
	void SetLookPoint(Vector2D point) { lookPoint = point; }

	virtual void Collide();
	virtual void Update();
	virtual void Draw(HDC hdc);
	~Player() {}
};
