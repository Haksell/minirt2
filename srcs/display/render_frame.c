#include "minirt.h"

static void	pixel_put(t_mlx *mlx, int x, int y)
{
	const int	offset = mlx->line_length * y + mlx->bytes_per_pixel * x;

	mlx->addr[offset] = x + y;
}

static void	render_pixel(t_data *data, int y, int x)
{
	pixel_put(&data->mlx, x, y);
}

int	render_frame(t_data *data)
{
	int	y;
	int	x;

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
