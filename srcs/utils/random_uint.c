#include "minirt.h"

unsigned int	get_random_uint(void)
{
	static unsigned int	x = UINT_SEED;

	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return (x);
}
