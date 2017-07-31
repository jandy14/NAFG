#include "Weapon.h"

void Blade::SetAbility(short pMinRequirement)
{
	minRequirement = pMinRequirement;
}
void Blade::Collide()
{

}
void Blade::Update()
{

}
void Blade::Draw()
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

}
void Ball::Draw()
{

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

}
void Missile::Draw()
{

}

short Blade::minRequirement;

float Ball::castingTime;
float Ball::durationTime;

float Missile::durationTime;
short Missile::speed;