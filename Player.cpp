#include <Windows.h>
#include "Setting.h"
#include "Player.h"
#include "GameManager.h"

Player::Player(short pID, Vector2D pPos)
{
	id = pID;
	pos = pPos;
	gaugeStopTimer = delayTimer = dashTimer = 0;
	isUp = isDown = isLeft = isRight = false;
	gauge = GameManager::GetInstance()->startGauge;
	gaugeFraction = 0.0f;
}

void Player::SetAbility(short pSpeed, short pMaxGauge, short pChargingSpeed, float pBladeDelay)
{
	speed = pSpeed;
	maxGauge = pMaxGauge;
	chargingSpeed = pChargingSpeed;
	Player::bladeDelay = pBladeDelay;
}
void Player::SetAbility(short pDashSpeed, float pGaugeStopTime, float pDashTime)
{
	dashSpeed = pDashSpeed;
	gaugeStopTime = pGaugeStopTime;
	dashTime = pDashTime;
}
void Player::SetDir(bool pIsKeyDown, DIRECTION pDir)
{
	switch (pDir)
	{
	case DIRECTION::UP:
		isUp = pIsKeyDown;
		break;
	case DIRECTION::DOWN:
		isDown = pIsKeyDown;
		break;
	case DIRECTION::LEFT:
		isLeft = pIsKeyDown;
		break;
	case DIRECTION::RIGHT:
		isRight = pIsKeyDown;
		break;
	}
}
void Player::SetGauge(short pValue)
{
	if (pValue > maxGauge)
		gauge = maxGauge;
	else if (pValue < 0)
		gauge = 0;
	else
		gauge = pValue;
}
void Player::Collide()
{
	isAlive = false;
}
void Player::Update()
{
	Vector2D _vel(0.0f,0.0f);
	
	if (isUp)
		_vel.y -= 1;
	if (isDown)
		_vel.y += 1;
	if (isLeft)
		_vel.x -= 1;
	if (isRight)
		_vel.x += 1;

	if(dashTimer == 0)
		velocity = _vel.Normalize() * speed;
	else
		velocity = _vel.Normalize() * dashSpeed;

	if (gauge < maxGauge)
	{
		gaugeFraction += (chargingSpeed * (1.0 / FPS));
		if (gaugeFraction > 1)
		{
			gauge += ((int)gaugeFraction);
			gaugeFraction -= ((int)gaugeFraction);
		}
		if (gauge >= maxGauge)
		{
			gauge = maxGauge;
			gaugeFraction = 0.0f;
		}
	}

	if (gaugeStopTimer > 0)
	{
		gaugeStopTimer -= (1.0f / FPS);
		if (gaugeStopTimer < 0)
			gaugeStopTimer = 0;
	}
	if (delayTimer > 0)
	{
		delayTimer -= (1.0f / FPS);
		if (delayTimer < 0)
			delayTimer = 0;
	}
	if (dashTimer > 0)
	{
		dashTimer -= (1.0f / FPS);
		if (dashTimer < 0)
			dashTimer = 0;
	}
}
void Player::Draw(HDC pHdc)
{
	Ellipse(pHdc, pos.x - 20, pos.y - 20, pos.x + 20, pos.y + 20);
}
short Player::speed;
short Player::dashSpeed;
short Player::maxGauge;
short Player::chargingSpeed;
float Player::bladeDelay;
float Player::gaugeStopTime;
float Player::dashTime;