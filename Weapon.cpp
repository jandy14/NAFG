#include <Windows.h>
#include "Setting.h"
#include "Weapon.h"

void Blade::SetAbility(short pMinRequirement)
{
	minRequirement = pMinRequirement;
}
void Blade::Collide()
{
	elapsedTimer += (1.0 / FPS);

	if (elapsedTimer > 0.1f)
		isAlive = false;
}
void Blade::Update()
{

}
void Blade::Draw(HDC pHdc)
{

}
void Ball::SetAbility(float pCastingTime, float pDurationTime)
{
	castingTime = pCastingTime;
	durationTime = pDurationTime;
}
void Ball::Collide()
{

}
void Ball::Update()
{
	elapsedTimer += (1.0/FPS);

	if (elapsedTimer > castingTime + durationTime)
		isAlive = false;
}
void Ball::Draw(HDC pHdc)
{
	Ellipse(pHdc, pos.x - 10, pos.y - 10, pos.x + 10, pos.y + 10);
}
void Missile::SetAbility(float pDurationTime, short pSpeed)
{
	durationTime = pDurationTime;
	speed = pSpeed;
}
void Missile::Collide()
{
	isAlive = false;
}
void Missile::Update()
{
	elapsedTimer += (1.0 / FPS);

	if (elapsedTimer > durationTime)
		isAlive = false;
}
void Missile::Draw(HDC pHdc)
{

}

short Blade::minRequirement;

float Ball::castingTime;
float Ball::durationTime;

float Missile::durationTime;
short Missile::speed;