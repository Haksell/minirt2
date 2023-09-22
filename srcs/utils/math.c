#include "minirt.h"

int	clamp(int x, int min, int max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}

bool	is_close(double x, double y)
{
	static double	epsilon = 1e-5;

	return (fabs(x - y) < epsilon);
}

bool	in_interval(t_interval interval, double x)
{
	return (interval.min <= x && x <= interval.max);
}
