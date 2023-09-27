#include "minirt.h"

float	get_random_float(void)
{
	return (RANDOM_FLOAT_MULTIPLICATOR * get_random_uint());
}

float	get_random_float_range(float min, float max)
{
	return (min + (max - min) * get_random_float());
}
