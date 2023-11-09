#include "minirt.h"

bool	hit_objects(t_hit *hit, t_scene *scene, t_ray *ray,
	t_interval interval)
{
	t_object	*object;
	t_hit		temp_hit;
	bool		hit_anything;
	int			i;

	hit_anything = false;
	if (hit_bvh(hit, scene->bvh, ray, interval))
	{
		hit_anything = true;
		interval.max = hit->t;
	}
	i = 0;
	while (i < scene->nb_obj)
	{
		object = scene->objects + i;
		if (object->type == OBJECT_PLANE && hit_plane(&temp_hit, &object->u.plane, ray, interval))
		{

			hit_anything = true;
			interval.max = temp_hit.t;
			if (hit)
				*hit = temp_hit;
		}
		++i;
	}
	return (hit_anything);
}
