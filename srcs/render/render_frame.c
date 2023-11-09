#include "minirt.h"

static int	get_int_component(float x)
{
	return (clamp((int)(255.9999 * sqrt(x)), 0, 255));
}

static void	pixel_put(t_mlx *mlx, int x, int y, t_vec3 color)
{
	const int	offset = mlx->line_length * y + mlx->bytes_per_pixel * x;
	const int	r = get_int_component(color[X]);
	const int	g = get_int_component(color[Y]);
	const int	b = get_int_component(color[Z]);

	mlx->addr[offset] = r << 16 | g << 8 | b;
}

static t_vec3	raytracing(t_ray ray, t_scene *scene, int depth)
{
	static const t_interval	start_interval = (t_interval){
		SHADOW_ACNE_FIX, INFINITY};
	t_hit					hit;
	t_ray					scattered;
	t_vec3					color;

	if (depth <= 0 || !hit_objects(&hit, scene, &ray, start_interval))
		return (scene->ambient.color);
	color = get_color(scene, &hit, ray);
	if (scatter(ray, hit, &scattered))
		return (color * raytracing(scattered, scene, depth - 1));
	return (color);
}

static t_ray	get_ray(const t_camera *camera, float s, float t)
{
	const t_vec3	rd = get_random_in_unit_disk() * camera->lens_radius;
	const t_vec3	offset = camera->u * rd[X] + camera->v * rd[Y];
	const t_vec3	moved_camera = camera->origin + offset;
	const t_vec3	direction = camera->lower_left - moved_camera
		+ camera->horizontal * s + camera->vertical * t;

	return ((t_ray){moved_camera, direction, 0});
}

static void	render_pixel(t_data *data, int y, int x)
{
	const float		frame = (float)data->frame;
	const float		u = (x + get_random_float()) / WINDOW_WIDTH;
	const float		v = (WINDOW_HEIGHT - y - 1 + get_random_float())
		/ WINDOW_HEIGHT;
	const t_ray		ray = get_ray(&data->scene.camera, u, v);
	t_vec3			pixel_color;

	pixel_color = raytracing(ray, &data->scene, MAX_DEPTH);
	pixel_color = (t_vec3){
		fclampf(pixel_color[X], 0, 1),
		fclampf(pixel_color[Y], 0, 1),
		fclampf(pixel_color[Z], 0, 1)
	};
	data->pixel_colors[y][x] = (data->pixel_colors[y][x] * frame + pixel_color)
		/ (frame + 1);
	pixel_put(&data->mlx, x, y, data->pixel_colors[y][x]);
}

static void	render_thread_frame(t_thread *thread)
{
	size_t	i;

	i = 0;
	while (i < thread->pixels_count)
	{
		render_pixel(thread->data, thread->pixels_to_manage[i].y,
			thread->pixels_to_manage[i].x);
		++i;
	}
	pthread_mutex_lock(&thread->data->mutex.access_data);
	++thread->data->cpus_count;
	pthread_mutex_unlock(&thread->data->mutex.access_data);
	++thread->cur_frame;
}

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