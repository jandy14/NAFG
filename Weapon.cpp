#include "Weapon.h"

void Blade::SetAbility(short pMinGage)
{
	minGage = pMinGage;
}

void Ball::SetAbility(float pCastingTime, float pDurationTime)
{
	castingTime = pCastingTime;
	durationTime = pDurationTime;
}

void Missile::SetAbility(float pDurationTime, short pSpeed)
{
	durationTime = pDurationTime;
	speed = pSpeed;
}