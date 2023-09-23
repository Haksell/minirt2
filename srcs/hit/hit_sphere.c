#include "minirt.h"

static bool	get_root(t_ray *ray, const t_sphere *sphere, t_interval interval,
	float *root)
{
	const t_vec3	oc = ray->origin - sphere->center;
	const float		a = vec3_length_squared(ray->direction);
	const float		half_b = vec3_dot(oc, ray->direction);
	const float		c = vec3_length_squared(oc)
		- sphere->radius * sphere->radius;
	float			discriminant;

	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (false);
	discriminant = sqrt(discriminant);
	*root = (-half_b - discriminant) / a;
	if (in_interval(interval, *root))
		return (true);
	*root = (-half_b + discriminant) / a;
	return (in_interval(interval, *root));
}

bool	hit_sphere(t_hit *hit, const t_sphere *sphere, t_ray *ray,
	t_interval interval)
{
	t_vec3	outward_normal;
	float	root;

	if (!get_root(ray, sphere, interval, &root))
		return (false);
	hit->t = root;
	hit->point = ray_at(*ray, hit->t);
	hit->material = sphere->material;
	outward_normal = (hit->point - sphere->center) / sphere->radius;
	set_face_normal(hit, ray, &outward_normal);
	return (true);
}
