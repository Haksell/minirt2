#include "minirt.h"

void	set_face_normal(t_hit *hit, t_ray *ray, t_vec3 *outward_normal)
{
	hit->front_face = vec3_dot(ray->direction, *outward_normal) < 0;
	if (hit->front_face)
		hit->normal = *outward_normal;
	else
		hit->normal = -(*outward_normal);
}
