#include "minirt.h"

t_bbox	bbox_infinite(void)
{
	return ((t_bbox){
		(t_interval){-INFINITY, INFINITY},
		(t_interval){-INFINITY, INFINITY},
		(t_interval){-INFINITY, INFINITY},
	});
}

t_bbox	bbox_new(t_vec3 a, t_vec3 b)
{
	return ((t_bbox){
		(t_interval){fminf(a[X], b[X]), fmaxf(a[X], b[X])},
		(t_interval){fminf(a[Y], b[Y]), fmaxf(a[Y], b[Y])},
		(t_interval){fminf(a[Z], b[Z]), fmaxf(a[Z], b[Z])},
	});
}
