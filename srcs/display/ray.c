#include "minirt.h"

t_ray	get_ray(const t_camera *camera, float s, float t)
{
	const t_vec3	rd = get_random_in_unit_disk() * camera->lens_radius;
	const t_vec3	offset = camera->u * rd[X] + camera->v * rd[Y];
	const t_vec3	moved_camera = camera->origin + offset;
	const t_vec3	direction = camera->lower_left
		+ camera->horizontal * s + camera->vertical * t - moved_camera;

	return ((t_ray){moved_camera, direction, 0});
}

t_vec3	ray_at(t_ray ray, float t)
{
	return (ray.origin + ray.direction * t);
}

void	set_face_normal(t_hit *hit, t_ray *ray, t_vec3 *outward_normal)
{
	hit->front_face = vec3_dot(ray->direction, *outward_normal) < 0;
	if (hit->front_face)
		hit->normal = *outward_normal;
	else
		hit->normal = -(*outward_normal);
}
