#include "minirt.h"

bool	parse_checkered_texture(t_scene *scene, char **line,
			int *cur_text, int len_line)
{
	if (len_line != 7)
		return (complain_bool(ERROR_TEXTURE));
	if (!parse_color(line[3], &scene->textures[*cur_text].u.checkered.color1)
		|| !parse_color(line[4], &scene->textures[*cur_text].u.checkered.color2)
		|| !ft_atof(line[5],
			&scene->textures[*cur_text].u.checkered.squares_height)
		|| !ft_atof(line[6],
			&scene->textures[*cur_text].u.checkered.squares_width))
		return (complain_bool(ERROR_TEXTURE));
	scene->textures[*cur_text].type = TEXTURE_CHECKERED;
	scene->textures[*cur_text].name = ft_strdup(line[2]);
	if (!scene->textures[*cur_text].name)
		return (complain_bool(MALLOC_ERROR));
	++(*cur_text);
	return (true);
}

bool	parse_image_texture(t_scene *scene, void* mlx_ptr, char **line,
			int *cur_text, int len_line)
{
	if (len_line != 4)
		return (complain_bool(ERROR_TEXTURE));
	scene->textures[*cur_text].u.image.img = mlx_xpm_file_to_image(
			mlx_ptr, line[3],
			&scene->textures[*cur_text].u.image.width,
			&scene->textures[*cur_text].u.image.height);
	if (!scene->textures[*cur_text].u.image.img)	
		return (complain_bool("file not found"));
	scene->textures[*cur_text].type = TEXTURE_IMAGE;
	scene->textures[*cur_text].name = ft_strdup(line[2]);
	if (!scene->textures[*cur_text].name)
		return (complain_bool(MALLOC_ERROR));
	scene->textures[*cur_text].u.image.addr = mlx_get_data_addr(
			scene->textures[*cur_text].u.image.img,
			&scene->textures[*cur_text].u.image.bpp,
			&scene->textures[*cur_text].u.image.line_length,
			&scene->textures[*cur_text].u.image.endian);
	++(*cur_text);
	return (true);
}

bool	affect_texture(t_scene *scene, char *name, t_texture *texture)
{
	int	i;

	i = 0;
	while (i < scene->nb_textures)
	{
		if (ft_strcmp(scene->textures[i].name, name) == 0)
		{
			*texture = scene->textures[i];
			return (true);
		}
		++i;
	}
	return (false);
}
