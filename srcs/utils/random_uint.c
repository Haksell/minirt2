#include "minirt.h"

unsigned int	get_random_uint(void)
{
	static unsigned int		x = UINT_SEED;
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&mutex);
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	pthread_mutex_unlock(&mutex);
	return (x);
}

unsigned int	get_random_uint_range(unsigned int a, unsigned int b)
{
	return (a + get_random_uint() % (b - a));
}
