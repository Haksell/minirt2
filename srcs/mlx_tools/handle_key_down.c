#include "minirt.h"

int	handle_key_down(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		close_window(data);
	return (EXIT_SUCCESS);
}
