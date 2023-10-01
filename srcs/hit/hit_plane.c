#include "minirt.h"
#include <stdio.h>

static	t_vec3	get_hit_color_plane(const t_hit *hit, const t_plane *plane)
{
	float	u;
	float	v;
	t_vec3	vector_to_hit;
	t_vec3	vec_u;
	t_vec3	vec_v;

	if (plane->texture.type == TEXTURE_NONE)
		return (plane->material.albedo);
	else if (plane->texture.type == TEXTURE_CHECKERED)
	{
		vector_to_hit = hit->point - plane->coord;
		if ((plane->vector[X] == 0 && fabs(plane->vector[Y]) == 1
				&& plane->vector[Z] == 0)
			|| (fabs(plane->vector[X]) == 1 && plane->vector[Y] == 0
				&& plane->vector[Z] == 0))
			vec_u = vec3_unit(vec3_cross(plane->vector, (t_vec3){0.8, 0.6, 0}));
		else
			vec_u = vec3_unit(vec3_cross(plane->vector, (t_vec3){1, 0, 0}));
		vec_v = vec3_unit(vec3_cross(plane->vector, vec_u));
		u = vec3_dot(vector_to_hit, vec_u);
		v = vec3_dot(vector_to_hit, vec_v);
		if (((int)floor(u * plane->texture.u.checkered.squares_width)
				+ (int)floor(v * plane->texture.u.checkered.squares_height))
			% 2 == 0)
			return (plane->texture.u.checkered.color1);
		else
			return (plane->texture.u.checkered.color2);
	}
	return (plane->material.albedo);
}

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
	hit->hit_color = get_hit_color_plane(hit, plane);
	return (true);
}
