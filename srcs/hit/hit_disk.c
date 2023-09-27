#include "minirt.h"

bool	hit_disk(t_hit *hit, const t_disk *disk, t_ray *ray,
	t_interval interval)
{
	return (hit_plane(hit, (t_plane *)disk, ray, interval)
		&& vec3_dist_squared(disk->coord, hit->point)
		<= disk->radius * disk->radius);
}
