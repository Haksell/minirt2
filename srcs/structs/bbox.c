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
		interval_new(a[X], b[X]),
		interval_new(a[Y], b[Y]),
		interval_new(a[Z], b[Z]),
	});
}
