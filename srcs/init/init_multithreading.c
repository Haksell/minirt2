#include "minirt.h"

bool	init_mutexes(t_data *data)
{
	return (pthread_mutex_init(&data->mutex.access_data, NULL) == 0);
}

static size_t	cut_pixels(int i)
{
	return (WINDOW_WIDTH * WINDOW_HEIGHT * i / CPUS);
}

// TODO: protect mallocs
bool	init_thread(t_data *data)
{
	size_t	i;
	size_t	j;
	size_t	start;
	size_t	end;

	i = 0;
	data->threads = malloc(CPUS * sizeof(t_thread));
	while (i < CPUS)
	{
		data->threads[i].idx = i;
		data->threads[i].data = data;
		data->threads[i].cur_frame = 0;
		start = cut_pixels(i);
		end = cut_pixels(i + 1);
		data->threads[i].pixels_count = end - start;
		data->threads[i].pixels_to_manage = malloc(sizeof(t_pixel) * (end - start));
		j = 0;
		while (j < data->threads[i].pixels_count)
		{
			data->threads[i].pixels_to_manage[j] = data->pixel_coordinates[start + j];
			j++;
		}
		if (pthread_create(&data->threads[i].pthread_id, NULL,
				(void *(*)(void *))routine, &data->threads[i]) != 0)
		{
			j = 0;
			while (j < i)
			{
				pthread_join(data->threads[j].pthread_id, NULL);
				j++;
			}
			return (false);
		}
		++i;
	}
	return (true);
}
