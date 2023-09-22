#include "minirt.h"

float	vec3_length_squared(t_vec3 v)
{
	return (vec3_dot(v, v));
}

float	vec3_length(t_vec3 v)
{
	return (sqrt(vec3_length_squared(v)));
}

t_vec3	vec3_unit(t_vec3 v)
{
	return (v / vec3_length(v));
}

float	vec3_dist_squared(t_vec3 v1, t_vec3 v2)
{
	return (vec3_length_squared(v1 - v2));
}

float	vec3_dist(t_vec3 v1, t_vec3 v2)
{
	return (vec3_length(v1 - v2));
}
