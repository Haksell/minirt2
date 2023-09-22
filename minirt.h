#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "mlx.h"

# define X 0
# define Y 1
# define Z 2

typedef float	t_v3f __attribute__((vector_size(16)));

bool	complain_bool(char *error_message);
int		complain_int(char *error_message);
void	*complain_ptr(char *error_message);

#endif
