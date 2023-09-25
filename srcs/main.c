#include "minirt.h"

static bool	init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->mutex.access_data, NULL) != 0)
		return (false);
	return (true);
}

static size_t	cut_pixels(int i)
{
	return (WINDOW_WIDTH * WINDOW_HEIGHT * i / CPUS);
}

static bool	init_thread(t_data *data)
{
	size_t		i;
	size_t		j;
	t_thread	tab_thread[CPUS]; // TODO: malloc?
	size_t 		start;
	size_t 		end;

	i = 0;
	while (i < CPUS)
	{
		tab_thread[i].idx = i;
		tab_thread[i].data = data;
		tab_thread[i].cur_frame = 0;
		start = cut_pixels(i);
		end = cut_pixels(i + 1);
		tab_thread[i].pixels_count = end - start;
		tab_thread[i].pixels_to_manage = malloc(sizeof(t_pixel) * (end - start)); //TO DO : protect malloc
		j = 0;
		while (j < tab_thread[i].pixels_count)
		{
			tab_thread[i].pixels_to_manage[j] = data->pixel_coordinates[start + j];
			j++;
		}
		if (pthread_create(&tab_thread[i].pthread_id, NULL,
				(void *(*)(void *))routine, &tab_thread[i]) != 0)
		{
			j = 0;
			while (j < i)
			{
				pthread_join(tab_thread[j].pthread_id, NULL);
				j++;
			}
			return (false);
		}
		++i;
	}
	data->threads = tab_thread; // TODO: check
	return (true);
}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(data));
	if (!parse_scene(&data.scene, argc, argv)
		|| !init_pixels(&data)
		|| !init_pixel_coordinates(&data)
		|| !init_minilibx(&data.mlx, argv[1])
		|| !init_mutexes(&data)
		|| !init_thread(&data))
	{
		free_data(&data);
		return (EXIT_FAILURE);
	}
	mlx_hook(data.mlx.win, DestroyNotify, NoEventMask, close_window, &data);
	mlx_hook(data.mlx.win, KeyPress, KeyPressMask, handle_key_down, &data);
	mlx_loop_hook(data.mlx.mlx, &render_frame, &data);
	mlx_loop(data.mlx.mlx);
	return (EXIT_SUCCESS);
}
