#pragma once

class Vector2D
{
public:
	float x, y;

	Vector2D(float pX, float pY) :x((short)pX), y((short)pY) {}
	Vector2D(short pX, short pY) :x(pX), y(pY) {}

};