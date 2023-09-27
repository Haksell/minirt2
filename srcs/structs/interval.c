#include "minirt.h"

bool	in_interval(t_interval interval, float x)
{
	return (interval.min <= x && x <= interval.max);
}

t_interval	expand_interval(t_interval interval, float delta)
{
	const float	padding = delta / 2;

	return ((t_interval){interval.min - padding, interval.max + padding});
}
