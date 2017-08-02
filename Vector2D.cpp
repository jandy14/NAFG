#include "Vector2D.h"
#include <math.h>

Vector2D Vector2D::Normalize()
{
	float distance = sqrt(x*x + y*y);
	if (distance == 0)
		return Vector2D(0.0f, 0.0f);
	else
		return Vector2D(x / distance, y / distance);
}
Vector2D Vector2D::operator*(short pValue)
{
	return Vector2D(x*pValue, y*pValue);
}
Vector2D Vector2D::operator*(float pValue)
{
	return Vector2D(x*pValue, y*pValue);
}