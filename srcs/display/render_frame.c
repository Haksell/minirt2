#include "minirt.h"

static int	get_int_component(float x)
{
	return (clamp((int)(255.9999 * x), 0, 255));
}

static void	pixel_put(t_mlx *mlx, int x, int y, t_vec3 color)
{
	const int	offset = mlx->line_length * y + mlx->bytes_per_pixel * x;
	const int	r = get_int_component(color[X]);
	const int	g = get_int_component(color[Y]);
	const int	b = get_int_component(color[Z]);

	mlx->addr[offset] = r << 16 | g << 8 | b;
}

static void	render_pixel(t_data *data, int y, int x)
{
	const t_vec3	color = (t_vec3){
		x * 1.0 / (WINDOW_WIDTH - 1),
		y * 1.0 / (WINDOW_HEIGHT - 1),
		1};

	pixel_put(&data->mlx, x, y, color);
}

int	render_frame(t_data *data)
{
	// const float	aspect_ratio = (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT;
	// const float viewport_height = 2.0;
	// const float viewport_width = aspect_ratio * viewport_height;
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
