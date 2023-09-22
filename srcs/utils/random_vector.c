#include "minirt.h"

t_vec3	get_random_in_unit_disk(void)
{
	t_vec3	v;
	float	length;

	v[Z] = 0;
	while (true)
	{
		v[X] = get_random_float_range(-1, 1);
		v[Y] = get_random_float_range(-1, 1);
		length = vec3_length_squared(v);
		if (0 < length && length < 1)
			return (v);
	}
}

t_vec3	get_random_in_unit_sphere(void)
{
	t_vec3	v;
	float	length;

	while (true)
	{
		v[X] = get_random_float_range(-1, 1);
		v[Y] = get_random_float_range(-1, 1);
		v[Z] = get_random_float_range(-1, 1);
		length = vec3_length_squared(v);
		if (0 < length && length < 1)
			return (v);
	}
}

t_vec3	get_random_unit_vector(void)
{
	return (vec3_unit(get_random_in_unit_sphere()));
}

t_vec3	get_random_in_hemisphere(t_vec3 normal)
{
	const t_vec3	v = get_random_in_unit_sphere();

	return (v * (float)sign(vec3_dot(v, normal)));
}
