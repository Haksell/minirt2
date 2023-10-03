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

static t_vec3	translate_tube_point(const t_vec3 point, const t_tube *tube)
{
	const float	dx = tube->axis[X];
	const float	dy = tube->axis[Y];
	const float	dz = tube->axis[Z];
	const float	d = sqrt(dx * dx + dy * dy + dz * dz);
	t_vec3		translated_point;

	if (dy != 1 && dy != -1)
	{
		translated_point[X] = (((dx * dx * dy / d) + dz * dz)
				/ (dx * dx + dz * dz)) * point[X]
			- (dx / d) * point[Y]
			+ ((dx * dz * (dy / d - 1)) / (dx * dx + dz * dz))
			* point[Z];
		translated_point[Y] = (dx / d) * point[X]
			+ (dy / d) * point[Y]
			+ (dz / d) * point[Z];
		translated_point[Z] = (((dx * dz * (dy / d - 1))
					/ (dx * dx + dz * dz))) * point[X]
			- (dz / d) * point[Y]
			+ (((dz * dz * dy / d) + dx * dx) / (dx * dx + dz * dz))
			* point[Z];
		return (translated_point);
	}
	else
		return (point);
}

static	t_vec3	get_hit_color_tube(const t_hit *hit, const t_tube *tube)
{
	float		u;
	float		v;
	t_vec3		corrected_hit_point;

	if (tube->texture.type == TEXTURE_NONE)
		return (tube->material.albedo);
	else if (tube->texture.type == TEXTURE_CHECKERED)
	{
		corrected_hit_point = translate_tube_point(hit->point, tube)
			- translate_tube_point(tube->center, tube);
		u = atan2(corrected_hit_point[Z], corrected_hit_point[X])
			/ (2 * M_PI) + 0.5;
		v = corrected_hit_point[Y] / (2 * tube->half_height);
		if (((int)floor(u * tube->texture.u.checkered.squares_width)
				+ (int)floor(v * tube->texture.u.checkered.squares_height))
			% 2 == 0)
			return (tube->texture.u.checkered.color1);
		else
			return (tube->texture.u.checkered.color2);
	}
	return (tube->material.albedo);
}

bool	hit_tube(t_hit *hit, const t_tube *tube, t_ray *ray,
	t_interval interval)
{
	t_vec3	outward_normal;
	t_vec3	center_to_hit;

	if (!get_root(hit, tube, ray, interval))
		return (false);
	hit->material = tube->material;
	hit->hit_color = get_hit_color_tube(hit, tube);
	center_to_hit = hit->point - tube->center;
	outward_normal = vec3_unit(center_to_hit
			- tube->axis * vec3_dot(tube->axis, center_to_hit));
	set_face_normal(hit, ray, &outward_normal);
	return (true);
}
