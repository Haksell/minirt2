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
