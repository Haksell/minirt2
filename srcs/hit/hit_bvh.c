#include "minirt.h"

// static void	swap_floats(float *a, float *b)
// {
// 	float	tmp;

// 	tmp = *a;
// 	*a = *b;
// 	*b = tmp;
// }

bool	hit_bvh(t_hit *hit, t_bvh *bvh, t_ray *ray, t_interval interval)
{
	(void)hit;
	(void)bvh;
	(void)ray;
	(void)interval;
	return (false);
	// t_interval	axis;
	// size_t		i;
	// float		inv_d;
	// float		t0;
	// float		t1;

	// (void)hit; // TODO
	// i = 0;
	// while (i < 3)
	// {
	// 	axis = ((t_interval *)bbox)[i];
	// 	inv_d = 1.0 / ray->direction[i];
	// 	t0 = (axis.min - ray->origin[i]) * inv_d;
	// 	t1 = (axis.max - ray->origin[i]) * inv_d;
	// 	if (inv_d < 0)
	// 		swap_floats(&t0, &t1);
	// 	interval.min = fmaxf(t0, interval.min);
	// 	interval.max = fminf(t1, interval.max);
	// 	if (interval.max <= interval.min)
	// 		return (false);
	// 	++i;
	// }
	// return (true);
}
