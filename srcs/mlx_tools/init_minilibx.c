#include "minirt.h"

bool	init_minilibx(t_mlx *mlx, char *window_title)
{
	int	_;

	mlx->mlx = mlx_init();
	if (mlx->mlx == NULL)
		return (complain_bool(ERROR_MLX));
	mlx->win = mlx_new_window(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			window_title);
	if (mlx->win == NULL)
		return (complain_bool(ERROR_WINDOW));
	mlx->img = mlx_new_image(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (mlx->img == NULL)
		return (complain_bool(ERROR_IMAGE));
	mlx->addr = (int *)mlx_get_data_addr(mlx->img, &mlx->bytes_per_pixel,
			&mlx->line_length, &_);
	if (mlx->addr == NULL)
		return (complain_bool(ERROR_ADDR));
	mlx->bytes_per_pixel >>= 5;
	mlx->line_length >>= 2;
	return (true);
}
