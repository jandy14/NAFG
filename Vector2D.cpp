#include "Vector2D.h"
#include <cmath>

#define PI (3.141592)
Vector2D Vector2D::Normalize()
{
	float distance = sqrt(x*x + y*y);
	if (distance == 0)
		return Vector2D(0.0f, 0.0f);
	else
		return Vector2D(x / distance, y / distance);
}
short Vector2D::Direction(short pX, short pY)
{
	if ((pX - x) == 0)
	{
		if ((pY - y) < 0)
			return 90;
		else
			return 270;
	}
	else
	{
		if ((pX - x) > 0)
			return atan(-(pY - y) / (pX - x)) * 180 / PI;
		else
			return (atan(-(pY - y) / (pX - x)) * 180 / PI) + 180;
	}
	return 0;
}
short Vector2D::Direction(Vector2D pTarget)
{
	return Direction(pTarget.x, pTarget.y);
}
Vector2D Vector2D::operator*(short pValue)
{
	return Vector2D(x*pValue, y*pValue);
}
Vector2D Vector2D::operator*(float pValue)
{
	return Vector2D(x*pValue, y*pValue);
}