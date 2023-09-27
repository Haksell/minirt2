#include "minirt.h"

t_vec3	ray_at(t_ray ray, float t)
{
	return (ray.origin + ray.direction * t);
}
