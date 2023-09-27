#include "minirt.h"

static bool	scatter_dielectric(t_ray ray, t_hit hit, t_ray *scattered)
{
	float	ir;
	float	cos_theta;
	float	sin_theta;
	t_vec3	unit_direction;
	t_vec3	direction;

	if (hit.front_face)
		ir = 1.0 / hit.material.u.dielectric.ir;
	else
		ir = hit.material.u.dielectric.ir;
	unit_direction = vec3_unit(ray.direction);
	cos_theta = fmin(-vec3_dot(unit_direction, hit.normal), 1);
	sin_theta = sqrt(1 - cos_theta * cos_theta);
	if (ir * sin_theta > 1 || reflectance(cos_theta, ir) > get_random_float())
		direction = reflect(unit_direction, hit.normal);
	else
		direction = refract(unit_direction, hit.normal, ir);
	*scattered = (t_ray){hit.point, direction, 0};
	return (true);
}

static bool	scatter_lambertian(t_ray ray, t_hit hit, t_ray *scattered)
{
	t_vec3	scatter_direction;

	(void)ray;
	scatter_direction = hit.normal + get_random_unit_vector();
	if (vec3_near_zero(scatter_direction))
		scatter_direction = hit.normal;
	*scattered = (t_ray){hit.point, scatter_direction, 0};
	return (true);
}

static bool	scatter_metal(t_ray ray, t_hit hit, t_ray *scattered)
{
	t_vec3	reflected;
	t_vec3	fuzzed;

	reflected = reflect(vec3_unit(ray.direction), hit.normal);
	fuzzed = reflected
		+ get_random_in_unit_sphere() * hit.material.u.metal.fuzz;
	*scattered = (t_ray){hit.point, fuzzed, 0};
	return (vec3_dot(reflected, hit.normal) > 0);
}

bool	scatter(t_ray ray, t_hit hit, t_ray *scattered)
{
	static t_scatter_func	funcs[] = {
	[MATERIAL_DIELECTRIC] = scatter_dielectric,
	[MATERIAL_LAMBERTIAN] = scatter_lambertian,
	[MATERIAL_METAL] = scatter_metal};

	return (funcs[hit.material.type](ray, hit, scattered));
}
