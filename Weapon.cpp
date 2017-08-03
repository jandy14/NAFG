#include <Windows.h>
#include <cmath>
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
	elapsedTimer += (1.0 / FPS);

	velocity = Vector2D((float)(cos(dir * PI / 180) * 300 *(0.5 - elapsedTimer)), (float)(sin(dir * PI / 180) * -300 * (0.5 - elapsedTimer)));

	if (elapsedTimer > 0.5)
		isAlive = false;
}
void Blade::Draw(HDC pHdc)
{
	float startX = cos((dir - 60) * PI / 180) * 25;
	float startY = sin((dir - 60) * PI / -180) * 25;
	float endX = cos((dir + 60) * PI / 180) * 25;
	float endY = sin((dir + 60) * PI / -180) * 25;
	Chord(pHdc, pos.x - 20, pos.y - 20, pos.x + 20, pos.y + 20, pos.x + startX, pos.y + startY, pos.x + endX, pos.y +endY);
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
	MoveToEx(pHdc, pos.x, pos.y, NULL);
	LineTo(pHdc, pos.x + cos(dir * PI / 180) * (1000), pos.y - sin(dir * PI / 180) * (1000));
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
	POINT p[3];
	p[0].x = pos.x + cos(dir * PI / 180) * 10;
	p[0].y = pos.x - sin(dir * PI / 180) * 10;
	p[1].x = pos.x + cos((dir + 90) * PI / 180) * 10;
	p[1].y = pos.x - sin((dir + 90) * PI / 180) * 10;
	p[2].x = pos.x + cos((dir - 90) * PI / 180) * 10;
	p[2].y = pos.x - sin((dir - 90) * PI / 180) * 10;
	Polygon(pHdc, p, 3);
}

short Blade::minRequirement;

float Ball::castingTime;
float Ball::durationTime;

float Missile::durationTime;
short Missile::speed;