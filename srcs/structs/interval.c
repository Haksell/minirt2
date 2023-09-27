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

t_aabb	new_aabb(t_vec3 a, t_vec3 b)
{
	return ((t_aabb){
		(t_interval){fminf(a[X], b[X]), fmaxf(a[X], b[X])},
		(t_interval){fminf(a[Y], b[Y]), fmaxf(a[Y], b[Y])},
		(t_interval){fminf(a[Z], b[Z]), fmaxf(a[Z], b[Z])},
	});
}
