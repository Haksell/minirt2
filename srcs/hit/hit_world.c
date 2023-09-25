#include "minirt.h"

static bool	hit_object(t_hit *hit, t_object *object, t_ray *ray,
	t_interval interval)
{
	if (object->type == OBJECT_DISK)
		return (hit_disk(hit, &object->u.disk, ray, interval));
	else if (object->type == OBJECT_SPHERE)
		return (hit_sphere(hit, &object->u.sphere, ray, interval));
	else if (object->type == OBJECT_PLANE)
		return (hit_plane(hit, &object->u.plane, ray, interval));
	else if (object->type == OBJECT_TUBE)
		return (hit_tube(hit, &object->u.tube, ray, interval));
	return (false);
}

bool	hit_world(t_hit *hit, t_scene *scene, t_ray *ray,
	t_interval interval)
{
	t_hit	temp_hit;
	bool	hit_anything;
	int		i;

	hit_anything = false;
	i = 0;
	while (i < scene->nb_obj)
	{
		if (hit_object(&temp_hit, scene->world + i, ray, interval))
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
