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
}

void Player::SetAbility(short pSpeed, short pMaxGauge, short pChargingSpeed, float pBladeDelay)
{
	speed = pSpeed;
	maxGauge = pMaxGauge;
	chargingSpeed = pChargingSpeed;
	bladeDelay = pBladeDelay;
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
void Player::Dash()
{
	dashTimer = dashTime;
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

	velocity = _vel.Normalize() * speed;

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