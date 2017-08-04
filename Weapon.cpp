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

	velocity = Vector2D((float)(cos(dir * PI / 180) * 500 *(0.5 - elapsedTimer)), (float)(sin(dir * PI / 180) * -500 * (0.5 - elapsedTimer)));

	if (elapsedTimer > 0.5)
		isAlive = false;
}
void Blade::Draw(HDC pHdc)
{
	float startX = cos((dir - 90) * PI / 180) * 25;
	float startY = sin((dir - 90) * PI / -180) * 25;
	float endX = cos((dir + 90) * PI / 180) * 25;
	float endY = sin((dir + 90) * PI / -180) * 25;
	Chord(pHdc, pos.x - 20, pos.y - 20, pos.x + 20, pos.y + 20, pos.x + startX, pos.y + startY, pos.x + endX, pos.y +endY);
}
void Ball::SetAbility(float pCastingTime, float pDurationTime)
{
	castingTime = pCastingTime;
	durationTime = pDurationTime;
}
Ball::Ball(short id, Vector2D pos, short dir) : Object(id, pos, dir)
{
	elapsedTimer = 0.0f;
	endPoint.x = pos.x + cos(dir * PI / 180) * (1000);
	endPoint.y = pos.y - sin(dir * PI / 180) * (1000);
}
Ball::Ball(short id, short posX, short posY, short dir) : Object(id, posX, posY, dir)
{
	elapsedTimer = 0.0f;
	endPoint.x = pos.x + cos(dir * PI / 180) * (1000);
	endPoint.y = pos.y - sin(dir * PI / 180) * (1000);
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
	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;

	if (elapsedTimer < castingTime)
	{
		hPen = hPen = CreatePen(PS_INSIDEFRAME, 1, RGB(0, 0, 0));
		oldPen = (HPEN)SelectObject(pHdc, hPen);
		MoveToEx(pHdc, pos.x, pos.y, NULL);
		LineTo(pHdc, endPoint.x, endPoint.y);
		DeleteObject(SelectObject(pHdc, oldPen));
	}
	else
	{
		MoveToEx(pHdc, pos.x, pos.y, NULL);
		LineTo(pHdc, endPoint.x, endPoint.y);
	}
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

	if (target == nullptr)
		return;

	if (elapsedTimer < 0.5)
	{
		velocity = Vector2D((float)((cos(dir * PI / 180)) * 2 * speed), (float)((sin(dir * PI / 180)) * 2 * -speed));
		return;
	}
	short targetDir = pos.Direction(target->pos);

	targetDir = targetDir < 0 ? targetDir + 360 : targetDir;

	SetDir(dir);
	if (targetDir - dir > 180 || (targetDir - dir < 0 && targetDir - dir > -180))
		dir -= 2;
	else
		dir += 2;
	

	velocity = Vector2D((float)((cos(dir * PI / 180)) * speed), (float)((sin(dir * PI / 180)) * -speed));
}
void Missile::Draw(HDC pHdc)
{
	POINT p[5];
	p[0].x = pos.x + cos(dir * PI / 180) * 10;
	p[0].y = pos.y - sin(dir * PI / 180) * 10;
	p[1].x = pos.x + cos((dir + 90) * PI / 180) * 10;
	p[1].y = pos.y - sin((dir + 90) * PI / 180) * 10;
	p[2].x = pos.x + cos((dir + 135) * PI / 180) * 10;
	p[2].y = pos.y - sin((dir + 135) * PI / 180) * 10;
	p[3].x = pos.x + cos((dir - 135) * PI / 180) * 10;
	p[3].y = pos.y - sin((dir - 135) * PI / 180) * 10;
	p[4].x = pos.x + cos((dir - 90) * PI / 180) * 10;
	p[4].y = pos.y - sin((dir - 90) * PI / 180) * 10;

	Polygon(pHdc, p, 5);
}

short Blade::minRequirement;

float Ball::castingTime;
float Ball::durationTime;

float Missile::durationTime;
short Missile::speed;