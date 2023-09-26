#include "minirt.h"

static void	set_default_material(t_material *material, t_vec3 color)
{
	material->type = MATERIAL_LAMBERTIAN;
	material->albedo = color / 255;
	material->u.lambertian.ka = 0.5;
	material->u.lambertian.kd = 0.8;
	material->u.lambertian.ks = 0.2;
	material->u.lambertian.specular_exponent = 5;
}

static t_object	add_disk(t_tube tube, bool is_top)
{
	t_vec3		axis;
	t_vec3		scaled_axis;
	t_vec3		coord;
	t_plane		plane;
	t_object	object;

	// TODO: copy material
	axis = tube.axis;
	scaled_axis = tube.axis * tube.half_height;
	if (is_top)
		axis = -axis;
	else
		scaled_axis = -scaled_axis;
	coord = tube.center - scaled_axis;
	plane = (t_plane){coord, axis, tube.color, tube.material};
	object.type = OBJECT_DISK;
	object.u.disk = (t_disk){plane, tube.radius};
	return (object);
}

bool	parse_cylinder(t_scene *scene, char **line, int *current_object)
{
	const int	length = arrlen(line);
	t_object	*object;

	object = &scene->world[*current_object];
	if (length != 8
		|| !parse_coord(line[1], &object->u.tube.center)
		|| !parse_normalized_vector(line[2], &object->u.tube.axis)
		|| !ft_atof(line[3], &object->u.tube.radius)
		|| object->u.tube.radius <= 0
		|| !ft_atof(line[4], &object->u.tube.half_height)
		|| object->u.tube.half_height <= 0
		|| !parse_color(line[5], &object->u.tube.color)
		|| !parse_material(line[6], line[7], &object->u.tube.material))
		return (complain_bool(ERROR_CYLINDER));
	object->type = OBJECT_TUBE;
	object->u.tube.half_height *= 0.5;
	object->u.tube.radius *= 0.5;
	set_default_material(&object->u.tube.material, object->u.tube.color);
	scene->world[*current_object + 1] = add_disk(object->u.tube, true);
	scene->world[*current_object + 2] = add_disk(object->u.tube, false);
	*current_object += SURFACES_CYLINDER;
	return (true);
}

bool	parse_plane(t_scene *scene, char **line, int *current_object)
{
	const int	length = arrlen(line);
	t_object	*object;

	object = &scene->world[*current_object];
	if (length != 6
		|| !parse_coord(line[1], &object->u.plane.coord)
		|| !parse_normalized_vector(line[2], &object->u.plane.vector)
		|| !parse_color(line[3], &object->u.plane.color)
		|| !parse_material(line[4], line[5], &object->u.plane.material))
		return (complain_bool(ERROR_PLANE));
	object->type = OBJECT_PLANE;
	set_default_material(&object->u.plane.material, object->u.plane.color);
	*current_object += SURFACES_PLANE;
	return (true);
}

bool	parse_sphere(t_scene *scene, char **line, int *current_object)
{
	const int	length = arrlen(line);
	t_object	*object;

	object = &scene->world[*current_object];
	if (length != 6
		|| !parse_coord(line[1], &object->u.sphere.center)
		|| !ft_atof(line[2], &object->u.sphere.radius)
		|| object->u.sphere.radius <= 0
		|| !parse_color(line[3], &object->u.sphere.color)
		|| !parse_material(line[4], line[5], &object->u.sphere.material))
		return (complain_bool(ERROR_SPHERE));
	object->type = OBJECT_SPHERE;
	object->u.sphere.radius *= 0.5;
	set_default_material(&object->u.sphere.material, object->u.sphere.color);
	*current_object += SURFACES_SPHERE;
	return (true);
}
