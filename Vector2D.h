#pragma once

class Vector2D
{
public:
	float x, y;

	Vector2D() {}
	Vector2D(float pX, float pY) :x(pX), y(pY) {}
	Vector2D(short pX, short pY) :x(pX), y(pY) {}

	Vector2D Normalize();
	short Direction(short x, short y);
	short Direction(Vector2D target);
	Vector2D operator*(short);
	Vector2D operator*(float);
};