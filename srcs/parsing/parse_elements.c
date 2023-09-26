#include "minirt.h"

bool	parse_ambient(t_scene *scene, char **line)
{
	const int	length = arrlen(line);
	float		ratio;

	if (scene->ambient.exists)
		return (complain_bool(DOUBLE_AMBIENT));
	if (length != 3
		|| !ft_atof_range(line[1], &ratio, 0, 1)
		|| !parse_color(line[2], &scene->ambient.color))
		return (complain_bool(ERROR_AMBIENT));
	scene->ambient.exists = true;
	return (true);
}

static void	define_camera(t_camera *camera, float fov)
{
	camera->exists = true;
	camera->lens_radius = 0; // TODO add to parsing
	camera->focus_dist = 1; // TODO add to parsing
	camera->aspect_ratio = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;
	camera->viewport_width = 2 * tan(fov * M_PI / 360);
	camera->viewport_height = camera->viewport_width / camera->aspect_ratio;
	camera->u = vec3_unit(vec3_cross(camera->orientation, (t_vec3){0, 1, 0}));
	camera->v = vec3_cross(camera->u, camera->orientation);
	camera->horizontal = camera->focus_dist * camera->viewport_width
		* camera->u;
	camera->vertical = camera->focus_dist * camera->viewport_height * camera->v;
	camera->lower_left = camera->origin
		- (camera->horizontal + camera->vertical) * 0.5
		+ camera->orientation * camera->focus_dist;
}

bool	parse_camera(t_scene *scene, char **line)
{
	const int	length = arrlen(line);
	float		fov;

	if (scene->camera.exists)
		return (complain_bool(DOUBLE_CAMERA));
	if (length != 4
		|| !parse_coord(line[1], &scene->camera.origin)
		|| !parse_normalized_vector(line[2], &scene->camera.orientation)
		|| !ft_atof_range(line[3], &fov, 0, 180))
		return (complain_bool(ERROR_CAMERA));
	if (fov == 0 || fov == 180)
		return (complain_bool(FOV_ERROR));
	define_camera(&scene->camera, fov);
	return (true);
}

bool	parse_lights(t_scene *scene, char **line)
{
	const int	length = arrlen(line);
	float		brightness;

	// TODO several lights
	if (length != 4
		|| !parse_coord(line[1], &scene->lights[0].coord)
		|| !ft_atof_range(line[2], &brightness, 0, 1)
		|| !parse_color(line[3], &scene->lights[0].color))
		return (complain_bool(ERROR_LIGHT));
	scene->lights[0].color = brightness * scene->lights[0].color;
	return (true);
}
