#include "cub3d.h"

float	mod(float a, float b)
{
	a -= b * fabs((float)((int)(a / b)));
	if (a >= 0)
		return (a);
	return (a + b);
}

float	deg_to_rad(float a)
{
	return (a / 360 * (2 * M_PI));
}

float	dist(float a, float b, float x, float y)
{
	return sqrt(pow(a - x, 2) + pow(b - y, 2));
}

int		rgb(int r, int g, int b)
{
	int c = r;
	c = (c << 8) | g;
	c = (c << 8) | b;
	return c;
}
