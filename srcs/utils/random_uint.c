#include "minirt.h"

// TODO different seeds for different threads
unsigned int	get_random_uint(void)
{
	_Thread_local static unsigned int		x = UINT_SEED;

	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return (x);
}

unsigned int	get_random_uint_range(unsigned int a, unsigned int b)
{
	return (a + get_random_uint() % (b - a));
}
