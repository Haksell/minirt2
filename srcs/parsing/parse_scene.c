#include "minirt.h"

static bool	get_surface_count(char *word, int *n)
{
	static char	*valid_objects[] = {"cy", "pl", "sp", NULL};	
	static int	num_surfaces[] = {SURFACES_CYLINDER, SURFACES_PLANE,
		SURFACES_SPHERE};
	int			i;

	i = 0;
	while (valid_objects[i] != NULL)
	{
		if (ft_strcmp(word, valid_objects[i]) == 0)
		{
			*n += num_surfaces[i];
			return (true);
		}
		++i;
	}
	return (false);
}

static bool	get_light_count(char *word, int *n)
{
	static char	*valid_elements[] = {"A", "C", "L", NULL};
	static int	num_lights[] = {0, 0, 1};
	int			i;

	i = 0;
	while (valid_elements[i] != NULL)
	{
		if (ft_strcmp(word, valid_elements[i]) == 0)
		{
			*n += num_lights[i];
			return (true);
		}
		++i;
	}
	return (false);
}

static bool	get_textures_count(char *word, int *n)
{
	if (ft_strcmp(word, "T") == 0)
	{
		*n += 1;
		return (true);
	}
	return (false);
}

static bool	count_objects(char ***words, int *nb_obj, int *nb_lights,
				int *nb_textures)
{
	char	*word;
	int		i;

	i = 0;
	while (words[i] != NULL)
	{
		word = words[i][0];
		if (word == NULL)
			return (complain_bool(SPACY_LINE));
		if (!get_light_count(word, nb_lights)
			&& !get_surface_count(word, nb_obj)
			&& !get_textures_count(word, nb_textures))
			return (complain_bool(INVALID_IDENTIFIER));
		++i;
	}
	return (true);
}

static bool	parse_line(t_scene *scene, void *mlx_ptr, char **line, int *current_object,
				int *current_light, int *current_texture)
{
	if (ft_strcmp(line[0], "A") == 0)
		return (parse_ambient(scene, line));
	else if (ft_strcmp(line[0], "C") == 0)
		return (parse_camera(scene, line));
	else if (ft_strcmp(line[0], "L") == 0)
		return (parse_lights(scene, line, current_light));
	else if (ft_strcmp(line[0], "T") == 0)
		return (parse_textures(scene, mlx_ptr, line, current_texture));
	else if (ft_strcmp(line[0], "sp") == 0)
		return (parse_sphere(scene, line, current_object));
	else if (ft_strcmp(line[0], "pl") == 0)
		return (parse_plane(scene, line, current_object));
	else if (ft_strcmp(line[0], "cy") == 0)
		return (parse_cylinder(scene, line, current_object));
	return (false);
}

static bool	parse_scene2(t_scene *scene, void *mlx_ptr, char ***words)
{
	int	current_object;
	int	current_light;
	int	current_texture;
	int	i;

	current_object = 0;
	current_light = 0;
	current_texture = 0;
	i = 0;
	while (words[i] != NULL)
	{
		if (!parse_line(scene, mlx_ptr, words[i], &current_object,
				&current_light, &current_texture))
		{
			ft_free_triple((void ****)&words);
			free_textures_names(scene->textures, scene->nb_textures); // TODO: add where needed
			return (false);
		}
		++i;
	}
	ft_free_triple((void ****)&words);
	if (!scene->camera.exists)
		return (complain_bool(NO_CAMERA));
	if (!scene->ambient.exists && scene->nb_lights == 0)
		return (complain_bool(NO_LIGHT));
	return (true);
}

bool	parse_scene(t_scene *scene, void* mlx_ptr, int argc, char **argv)
{
	char	***words;

	if (argc != 2 || !ft_endswith(argv[1], ".rtb"))
		return (complain_bool(USAGE_BONUS));
	words = get_words(argv[1]);
	if (words == NULL
		|| !count_objects(words, &scene->nb_obj, &scene->nb_lights,
			&scene->nb_textures))
	{
		ft_free_triple((void ****)&words);
		return (false);
	}
	printf("nb_lights: %i\n", scene->nb_lights);
	scene->world = ft_calloc(scene->nb_obj, sizeof(t_object));
	scene->lights = ft_calloc(scene->nb_lights, sizeof(t_light));
	scene->textures = ft_calloc(scene->nb_textures, sizeof(t_texture));
	if (scene->world == NULL || scene->lights == NULL
		|| scene->textures == NULL)
	{
		ft_free_triple((void ****)&words);
		free(scene->world);
		free(scene->lights);
		free(scene->textures);
		return (complain_bool(MALLOC_ERROR));
	}
	return (parse_scene2(scene, mlx_ptr, words));
}
