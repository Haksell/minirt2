#ifndef MINIRT_H
# define MINIRT_H

/******************************************************************************/
/*                                                                            */
/*                                  INCLUDES                                  */
/*                                                                            */
/******************************************************************************/

# include "libft.h"
# include "mlx.h"

# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <X11/keysym.h>
# include <X11/Xlib.h>

/******************************************************************************/
/*                                                                            */
/*                                  DEFINES                                   */
/*                                                                            */
/******************************************************************************/

# define X 0
# define Y 1
# define Z 2

/******************************************************************************/
/*                                                                            */
/*                                  TYPEDEFS                                  */
/*                                                                            */
/******************************************************************************/

typedef float	t_v3f __attribute__((vector_size(16)));

typedef struct s_mlx {
	int		bytes_per_pixel;
	int		line_length;
	int		*addr;
	void	*win;
	void	*img;
	void	*mlx;
}	t_mlx;

/******************************************************************************/
/*                                                                            */
/*                                 PROTOTYPES                                 */
/*                                                                            */
/******************************************************************************/

bool	complain_bool(char *error_message);
int		complain_int(char *error_message);
void	*complain_ptr(char *error_message);

#endif
