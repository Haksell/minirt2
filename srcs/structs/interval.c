#include "minirt.h"

t_interval	interval_new(float a, float b)
{
	return ((t_interval){fminf(a, b), fmaxf(a, b)});
}

bool	in_interval(t_interval interval, float x)
{
	return (interval.min <= x && x <= interval.max);
}

t_interval	expand_interval(t_interval interval, float delta)
{
	const float	padding = delta / 2;

	return ((t_interval){interval.min - padding, interval.max + padding});
}
