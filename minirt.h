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
/*                                   ERRORS                                   */
/*                                                                            */
/******************************************************************************/

# define USAGE_MANDATORY "Usage: ./miniRT *.rt"
# define USAGE_BONUS "Usage: ./miniRTbonus *.rtb?"

# define SPACY_LINE "Line contains only spaces and tabulations"
# define OPEN_ERROR "File cannot be opened"
# define MALLOC_ERROR "Impossible to allocate heap memory"
# define READ_ERROR "Error while reading the file"
# define INVALID_IDENTIFIER "Invalid identifier"

# define float_AMBIENT "Too many ambient lights"
# define float_CAMERA "Too many cameras"
# define float_LIGHT "Too many lights"
# define ERROR_AMBIENT "Error parsing ambient light"
# define ERROR_CAMERA "Error parsing camera"
# define ERROR_LIGHT "Error parsing light"
# define NO_CAMERA "There is no camera"
# define NO_LIGHT "There is no light"
# define FOV_ERROR "Field of view is invalid"

# define ERROR_CYLINDER "Error parsing cylinder"
# define ERROR_PLANE "Error parsing plane"
# define ERROR_SPHERE "Error parsing sphere"

# define ERROR_MLX "Failed to initialize mlx"
# define ERROR_WINDOW "Failed to initialize window"
# define ERROR_IMAGE "Failed to initialize image"
# define ERROR_ADDR "Failed to initialize addr"

/******************************************************************************/
/*                                                                            */
/*                                  DEFINES                                   */
/*                                                                            */
/******************************************************************************/

# define X 0
# define Y 1
# define Z 2

# ifndef M_PI
#  define M_PI 3.141592653589793
# endif

# define WINDOW_WIDTH 640
# define WINDOW_HEIGHT 360
# define FRAMES 100
# define MAX_DEPTH 25
# define LIGHT_INTENSITY 100.0
# define BUFFER_SIZE_RT 16384
# define SHADOW_ACNE_FIX 1e-3
# define SPACES " \f\n\r\t\v"

# define SURFACES_CYLINDER 3
# define SURFACES_PLANE 1
# define SURFACES_SPHERE 1

/******************************************************************************/
/*                                                                            */
/*                                  TYPEDEFS                                  */
/*                                                                            */
/******************************************************************************/

// TODO: try vec3 of doubles
typedef float	t_vec3 __attribute__((vector_size(16)));

typedef struct s_interval {
	float	min;
	float	max;
}	t_interval;

typedef struct s_mlx {
	int		bytes_per_pixel;
	int		line_length;
	int		*addr;
	void	*win;
	void	*img;
	void	*mlx;
}	t_mlx;

typedef struct s_data {
	int		frame;
	t_mlx	mlx;
}	t_data;

/******************************************************************************/
/*                                                                            */
/*                                 PROTOTYPES                                 */
/*                                                                            */
/******************************************************************************/

// display
int		render_frame(t_data *data);

// mlx_tools
int		handle_key_down(int keycode, t_data *data);
bool	init_minilibx(t_mlx *mlx, char *window_title);

// utils
int		clamp(int x, int min, int max);
int		close_window(t_data *data);
bool	complain_bool(char *error_message);
int		complain_int(char *error_message);
void	*complain_ptr(char *error_message);
void	free_data(t_data *data);
bool	in_interval(t_interval interval, float x);
bool	is_close(float x, float y);
void	print_vec3(char *name, t_vec3 v); // TODO remove

// vec3
float	vec3_dot(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_cross(t_vec3 v1, t_vec3 v2);
bool	vec3_near_zero(t_vec3 v);
float	vec3_length_squared(t_vec3 v);
float	vec3_length(t_vec3 v);
t_vec3	vec3_unit(t_vec3 v);
float	vec3_dist_squared(t_vec3 v1, t_vec3 v2);

#endif
