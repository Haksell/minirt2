#include "minirt.h"

void	*routine(t_thread *thread)
{
	int	frame_to_compute;

	while (true)
	{
		pthread_mutex_lock(&thread->data->mutex.access_data);
		if (thread->data->frame == FRAMES || thread->data->stop)
		{
			pthread_mutex_unlock(&thread->data->mutex.access_data);
			return (NULL);
		}
		frame_to_compute = thread->data->frame;
		pthread_mutex_unlock(&thread->data->mutex.access_data);
		if (frame_to_compute == thread->cur_frame)
			render_thread_frame(thread);
		else
			usleep(100);
	}
	return (NULL);
}

int	render_frame(t_data *data)
{
	pthread_mutex_lock(&data->mutex.access_data);
	if (data->frame == FRAMES)
	{
		pthread_mutex_unlock(&data->mutex.access_data);
		usleep(CPUS * 200);
		return (EXIT_SUCCESS);
	}
	pthread_mutex_unlock(&data->mutex.access_data);
	while (true)
	{
		pthread_mutex_lock(&data->mutex.access_data);
		if (data->cpus_count == CPUS)
		{
			data->cpus_count = 0;
			break ;
		}
		pthread_mutex_unlock(&data->mutex.access_data);
		usleep(100);
	}
	++data->frame;
	ft_printf("\rFrame: %d/%d", data->frame, FRAMES);
	if (data->frame == FRAMES)
		ft_printf("\nCompleted.\n");
	pthread_mutex_unlock(&data->mutex.access_data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
	return (EXIT_SUCCESS);
}
