#include "minirt.h"

static unsigned int	get_random_uint(void)
{
	static unsigned int	x = 3941839098;

	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return (x);
}

float	get_random_float(void)
{
	return (RANDOM_FLOAT_MULTIPLICATOR * get_random_uint());
}

float	get_random_float_range(float min, float max)
{
	return (min + (max - min) * get_random_float());
}
