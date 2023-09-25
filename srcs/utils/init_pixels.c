#include "minirt.h"

bool	init_pixels(t_data *data)
{
	int	i;

	data->pixels = ft_calloc(WINDOW_HEIGHT + 1, sizeof(t_vec3 *));
	if (data->pixels == NULL)
		return (complain_bool(MALLOC_ERROR));
	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		data->pixels[i] = ft_calloc(WINDOW_WIDTH, sizeof(t_vec3));
		if (data->pixels[i] == NULL)
		{
			ft_free_double((void ***)&data->pixels);
			return (complain_bool(MALLOC_ERROR));
		}
		++i;
	}
	return (true);
}

static void	shuffle_coordinates(t_pixel *pixel_coordinates)
{
	const unsigned int	arr_size = WINDOW_HEIGHT * WINDOW_WIDTH;
	t_pixel				tmp;
	int					i;
	int					j;

	i = 0;
	while (i < WINDOW_HEIGHT * WINDOW_WIDTH)
	{
		j = get_random_uint_range(i, arr_size);
		tmp = pixel_coordinates[i];
		pixel_coordinates[i] = pixel_coordinates[j];
		pixel_coordinates[j] = tmp;
		++i;
	}
}

bool	init_pixel_coordinates(t_data *data)
{
	int	i;
	int	y;
	int	x;

	data->pixel_coordinates = ft_calloc(WINDOW_HEIGHT * WINDOW_WIDTH,
			sizeof(t_pixel *));
	if (data->pixel_coordinates == NULL)
		return (complain_bool(MALLOC_ERROR));
	i = 0;
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			data->pixel_coordinates[i] = (t_pixel){x, y};
			++x;
			++i;
		}
		++y;
	}
	shuffle_coordinates(data->pixel_coordinates);
	return (true);
}
