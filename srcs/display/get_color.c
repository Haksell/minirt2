#include "minirt.h"

static void	compute_light_ray(t_ray *light_ray, t_light *light, t_hit *hit)
{
	light_ray->origin = hit->point;
	light_ray->direction = light->coord - hit->point;
	light_ray->distance = vec3_length(light_ray->direction);
	light_ray->direction = vec3_unit(light_ray->direction);
}

t_vec3	get_color(t_scene *scene, t_hit *hit, t_ray ray)
{
	int		i;
	t_ray	light_ray;
	t_vec3	color;
	t_light	*light;

	if (hit->material.type == MATERIAL_METAL)
		return (hit->material.u.metal.albedo);
	if (hit->material.type == MATERIAL_DIELECTRIC)
		return (hit->material.u.dielectric.albedo);
	color = get_ambient_color(scene, hit);
	i = 0;
	while (i < scene->nb_lights)
	{
		light = &scene->lights[i];
		compute_light_ray(&light_ray, light, hit);
		if (!hit_world_light(scene, &light_ray,
				(t_interval){SHADOW_ACNE_FIX, light_ray.distance}))
			color = color
				+ get_diffuse_color(light, hit, &light_ray)
				+ get_specular_color(light, hit, &ray, &light_ray); // TODO: color += ?
		++i;
	}
	return (color);
}
