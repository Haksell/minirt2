#include "minirt.h"
#include <stdio.h> // TODO: remove

void	print_vec3(char *name, t_vec3 v)
{
	printf("%s: (%.3f, %.3f, %.3f)\n", name, v[X], v[Y], v[Z]);
}
