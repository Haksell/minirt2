#include "minirt.h"

void	free_data(t_data *data)
{
	ft_free_double((void ***)&data->pixels);
	free(data->scene.world);
	if (data->mlx.mlx != NULL)
	{
		if (data->mlx.img != NULL)
			mlx_destroy_image(data->mlx.mlx, data->mlx.img);
		if (data->mlx.win != NULL)
			mlx_destroy_window(data->mlx.mlx, data->mlx.win);
		mlx_destroy_display(data->mlx.mlx);
		free(data->mlx.mlx);
	}
}

int	close_window(t_data *data)
{
	free_data(data);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
