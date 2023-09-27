#include "minirt.h"
#include <stdio.h>

bool	hit_plane(t_hit *hit, const t_plane *plane, t_ray *ray,
	t_interval interval)
{
	const float		denom = vec3_dot(plane->vector, ray->direction);
	const t_vec3	oc = plane->coord - ray->origin;

	if (fabs(denom) < 1e-6)
		return (false);
	hit->t = vec3_dot(oc, plane->vector) / denom;
	if (!in_interval(interval, hit->t))
		return (false);
	hit->point = ray_at(*ray, hit->t);
	hit->front_face = denom < 0;
	if (hit->front_face)
		hit->normal = plane->vector;
	else
		hit->normal = -plane->vector;
	hit->material = plane->material;
	return (true);
}
