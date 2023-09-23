#include "minirt.h"

bool	hit_disk(t_hit *hit, const t_disk *disk, t_ray *ray,
	t_interval interval)
{
	float	dist_squared;

	if (!hit_plane(hit, &disk->plane, ray, interval))
		return (false);
	dist_squared = vec3_dist_squared(disk->plane.coord, hit->point);
	return (dist_squared <= disk->radius * disk->radius);
}
