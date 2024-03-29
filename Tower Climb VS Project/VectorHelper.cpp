#include "VectorHelper.h"
#include <math.h>

float VectorHelper::SquareMagnitude(sf::Vector2f vec)
{
	return vec.x * vec.x + vec.y * vec.y;
}

float VectorHelper::Magnitude(sf::Vector2f vec)
{
	return sqrtf(SquareMagnitude(vec));
}
