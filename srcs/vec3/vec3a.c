#include "minirt.h"

float	vec3_dot(t_vec3 v1, t_vec3 v2)
{
	const t_vec3	v = v1 * v2;

	return (v[X] + v[Y] + v[Z]);
}

t_vec3	vec3_cross(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){
		v1[Y] * v2[Z] - v1[Z] * v2[Y],
		v1[Z] * v2[X] - v1[X] * v2[Z],
		v1[X] * v2[Y] - v1[Y] * v2[X],
	});
}

bool	vec3_near_zero(t_vec3 v)
{
	static float	epsilon = 1e-8;

	return (fabs(v[X]) < epsilon
		&& fabs(v[Y]) < epsilon
		&& fabs(v[Z]) < epsilon);
}
