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
	t_hit	hit;
	t_ray	scattered;
	t_vec3	color;

	if (depth <= 0)
		return (scene->ambient.color);
	if (hit_world(&hit, scene, &ray, (t_interval){SHADOW_ACNE_FIX, INFINITY}))
	{
		color = get_color(scene, &hit, ray);
		if (scatter(ray, hit, &scattered))
			return (color * raytracing(scattered, scene, depth - 1));
		return (color);
	}
	return (scene->ambient.color);
}

static void	render_pixel(t_data *data, int y, int x)
{
	const float		frame = (float)data->frame;
	const float		u = (x + get_random_float()) / WINDOW_WIDTH;
	const float		v = (WINDOW_HEIGHT - y - 1 + get_random_float())
		/ WINDOW_HEIGHT;
	const t_ray		ray = get_ray(&data->scene.camera, u, v);
	const t_vec3	pixel_color = raytracing(ray, &data->scene, MAX_DEPTH);

	data->pixels[y][x] = (data->pixels[y][x] * frame + pixel_color)
		/ (frame + 1);
	pixel_put(&data->mlx, x, y, data->pixels[y][x]);
}

int	render_frame(t_data *data)
{
	int			y;
	int			x;

	if (data->frame == FRAMES)
		return (EXIT_SUCCESS);
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			render_pixel(data, y, x);
			++x;
		}
		++y;
	}
	++data->frame;
	ft_printf("\rFrame: %d/%d", data->frame, FRAMES);
	if (data->frame == FRAMES)
		ft_printf("\nCompleted.\n");
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
	return (EXIT_SUCCESS);
}
