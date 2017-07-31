#include "Player.h"
#include "GameManager.h"

Player::Player(short pID, Vector2D pPos)
{
	id = pID;
	pos = pPos;
	delay = dashTimer = 0;
	isUp = isDown = isLeft = isRight = false;
	gage = GameManager::GetInstance()->startGauge;
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