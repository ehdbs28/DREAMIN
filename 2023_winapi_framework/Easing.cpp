#include "pch.h"
#include "Easing.h"

float EaseOutCubic(float _x)
{
	return 1 - powf(1 - _x, 3);
}

float EaseInOutCubic(float _x)
{
	return (_x < 0.5 ? 4 * _x * _x * _x : 1 - powf(-2 * _x + 2, 3) / 2);
}

float EaseInBack(float _x) {
	const float c1 = 1.70158;
	const float c3 = c1 + 1;

	return c3 * _x * _x * _x - c1 * _x * _x;
}