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

bool	parse_lights(t_scene *scene, char **line, int *current_light)
{
	const int	length = arrlen(line);
	float		brightness;

	printf("parse_lights, current light nb: %i\n", *current_light);
	if (length != 4
		|| !parse_coord(line[1], &scene->lights[*current_light].coord)
		|| !ft_atof_range(line[2], &brightness, 0, 1)
		|| !parse_color(line[3], &scene->lights[*current_light].color))
		return (complain_bool(ERROR_LIGHT));
	scene->lights[*current_light].color = brightness
		* scene->lights[*current_light].color;
	++(*current_light);
	return (true);
}

bool	parse_textures(t_scene *scene, void *mlx_ptr, char **line, int *current_texture)
{
	const int	length = arrlen(line);

	if (length < 4)
		return (complain_bool(ERROR_TEXTURE));
	if (ft_strcmp(line[1], "checkered") == 0)
		return (parse_checkered_texture(scene, line, current_texture, length));
	else if (ft_strcmp(line[1], "image") == 0)
		return (parse_image_texture(scene, mlx_ptr, line, current_texture, length));
	return (complain_bool(ERROR_TEXTURE));
}