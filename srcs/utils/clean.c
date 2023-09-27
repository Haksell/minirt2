#include "minirt.h"

static void	destroy_mutexes(t_data *data)
{
	pthread_mutex_destroy(&data->mutex.access_data);
	pthread_mutex_destroy(&data->mutex.access_image);
}

static void	wait_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < CPUS)
	{
		pthread_join(data->threads[i].pthread_id, NULL);
		i++;
	}
}

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
	pthread_mutex_lock(&data->mutex.access_data);
	data->stop = true;
	pthread_mutex_unlock(&data->mutex.access_data);
	wait_threads(data);
	destroy_mutexes(data);
	free_data(data);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

int	handle_key_down(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		close_window(data);
	return (EXIT_SUCCESS);
}
