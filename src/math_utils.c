#include "cub3d.h"

float	mod(float a, float b)
{
	a -= b * fabs(a / b);
	if (a >= 0)
		return (a);
	return (a + b);
}

/*
float	fabs(float a)
{
	if (a < 0)
		return (-a);
	return (a);
}*/
