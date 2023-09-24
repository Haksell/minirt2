#include "minirt.h"

static bool	touches_tube(t_hit *hit, const t_tube *tube, t_interval interval)
{
	const float	max_dist_squared = tube->half_height * tube->half_height
		+ tube->radius * tube->radius;

	return (in_interval(interval, hit->t)
		&& vec3_dist_squared(hit->point, tube->center) < max_dist_squared);
}

static bool	get_root(t_hit *hit, const t_tube *tube, t_ray *ray,
	t_interval interval)
{
	const t_vec3	new_dir = vec3_cross(ray->direction, tube->axis);
	const t_vec3	oc = ray->origin - tube->center;
	const float		a = vec3_length_squared(new_dir);
	const float		half_b = vec3_dot(new_dir, vec3_cross(oc, tube->axis));
	float			discriminant;

	discriminant = half_b * half_b - a
		* (vec3_length_squared(vec3_cross(oc, tube->axis))
			- tube->radius * tube->radius);
	if (discriminant < 0)
		return (false);
	discriminant = sqrt(discriminant);
	hit->t = (-half_b - discriminant) / a;
	hit->point = ray_at(*ray, hit->t);
	if (touches_tube(hit, tube, interval))
		return (true);
	hit->t = (-half_b + discriminant) / a;
	hit->point = ray_at(*ray, hit->t);
	return (touches_tube(hit, tube, interval));
}

bool	hit_tube(t_hit *hit, const t_tube *tube, t_ray *ray,
	t_interval interval)
{
	t_vec3	outward_normal;
	t_vec3	center_to_hit;

	if (!get_root(hit, tube, ray, interval))
		return (false);
	hit->material = tube->material;
	center_to_hit = hit->point - tube->center;
	// TODO: fix the normal when the ray hits the top or bottom of the tube (the normal should be the axis of the tube) (the normal should be the axis of the tube) 
	// outward_normal = vec3_unit(tube->center
	// 		+ tube->axis * vec3_dot(tube->axis, center_to_hit));
	
	outward_normal = vec3_unit(hit->point
			- tube->center
			-tube->axis * vec3_dot(tube->axis, hit->point - tube->center));
	set_face_normal(hit, ray, &outward_normal);
	return (true);
}
