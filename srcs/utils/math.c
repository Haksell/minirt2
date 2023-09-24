#include "minirt.h"

int	clamp(int x, int min, int max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}

float	fffclampfff(float x, float min, float max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}

bool	is_close(float x, float y)
{
	static float	epsilon = 1e-5;

	return (fabs(x - y) < epsilon);
}

bool	in_interval(t_interval interval, float x)
{
	return (interval.min <= x && x <= interval.max);
}

int	sign(float x)
{
	return ((x > 0) - (x < 0));
}
