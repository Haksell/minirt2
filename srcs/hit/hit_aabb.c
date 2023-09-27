#include "minirt.h"

// static t_interval   get_axis(t_aabb *aabb, size_t i)
// {
//     if (n == 1) return (aabb->y);
//     if (n == 2) return (aabb->z);
//     return (aabb->x);
// }

bool	hit_aabb(t_hit *hit, t_aabb *aabb, t_ray *ray, t_interval interval)
{
	(void)hit;
	(void)aabb;
	(void)ray;
	(void)interval;
	return (false);
	// for (int i = 0; i < 3; i++) {
	//     t_interval axis = get_axis(aabb, i);
	//     auto t0 = fmin((axis.min - ray->origin[i]) / ray->direction[i],
	//                     (axis.max - ray->origin[i]) / ray->direction[i]);
	//     auto t1 = fmax((axis.min - ray->origin[i]) / ray->direction[i],
	//                     (axis.max - ray->origin[i]) / ray->direction[i]);
	//     ray_t.min = fmax(t0, ray_t.min);
	//     ray_t.max = fmin(t1, ray_t.max);
	//     if (ray_t.max <= ray_t.min)
	//         return false;
	// }
	// return true;
}
