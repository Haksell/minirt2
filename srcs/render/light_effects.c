#include "minirt.h"

float	reflectance(float cosine, float ref_idx)
{
	float	r0;

	r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 *= r0;
	return (r0 + (1 - r0) * pow(1 - cosine, 5));
}

t_vec3	reflect(t_vec3 v, t_vec3 n)
{
	return (v - 2 * vec3_dot(v, n) * n);
}

t_vec3	refract(t_vec3 v, t_vec3 n, float ir)
{
	const float		cos_theta = fmin(-vec3_dot(v, n), 1);
	const t_vec3	perpendicular = ir * (v + n * cos_theta);
	const t_vec3	parallel = n
		* -sqrtf(fabs(1 - vec3_length_squared(perpendicular)));

	return (perpendicular + parallel);
}
