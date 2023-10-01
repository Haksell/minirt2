#include "minirt.h"

static t_vec3	get_ambient_color(t_scene *scene, t_hit *hit)
{
	return (hit->hit_color
		* scene->ambient.color
		* hit->material.u.lambertian.ka);
}

static t_vec3	get_diffuse_color(t_light *light, t_hit *hit, t_ray *light_ray)
{
	return (light->color
		* LIGHT_INTENSITY
		* fmaxf(vec3_dot(light_ray->direction, hit->normal), 0)
		/ (light_ray->distance * light_ray->distance)
		* hit->hit_color
		* hit->material.u.lambertian.kd);
}

static t_vec3	get_specular_color(t_light *light, t_hit *hit, t_ray *ray,
	t_ray *light_ray)
{
	const t_vec3	reflection_direction = reflect(
			-light_ray->direction, hit->normal);

	return (light->color
		* LIGHT_INTENSITY
		* hit->material.u.lambertian.ks
		/ (light_ray->distance * light_ray->distance) * powf(fmaxf(0,
				-vec3_dot(reflection_direction, vec3_unit(ray->direction))),
			hit->material.u.lambertian.specular_exponent));
}


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

	if (hit->material.type != MATERIAL_LAMBERTIAN)
		return (hit->hit_color);
	color = get_ambient_color(scene, hit);
	i = 0;
	while (i < scene->nb_lights)
	{
		light = &scene->lights[i];
		compute_light_ray(&light_ray, light, hit);
		if (!hit_world(NULL, scene, &light_ray,
				(t_interval){SHADOW_ACNE_FIX, light_ray.distance}))
			color += get_diffuse_color(light, hit, &light_ray)
				+ get_specular_color(light, hit, &ray, &light_ray);
		++i;
	}
	return (color);
}
