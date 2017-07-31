#include "Weapon.h"

void Blade::SetAbility(short pMinGage)
{
	minGage = pMinGage;
}
void Blade::Collide()
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
void Missile::SetAbility(float pDurationTime, short pSpeed)
{
	durationTime = pDurationTime;
	speed = pSpeed;
}
void Missile::Collide()
{
	isAlive = false;
}