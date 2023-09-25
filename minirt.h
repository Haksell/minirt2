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
# include <stddef.h>
# include <stdio.h> // TODO: remove
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <X11/keysym.h>
# include <X11/Xlib.h>
# include <pthread.h>

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

# define DOUBLE_AMBIENT "Too many ambient lights"
# define DOUBLE_CAMERA "Too many cameras"
# define DOUBLE_LIGHT "Too many lights"
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

# ifndef CPUS
#  define CPUS 20
# endif

# define RANDOM_FLOAT_MULTIPLICATOR 0.00000000023283064365386962890625

# define WINDOW_WIDTH 640
# define WINDOW_HEIGHT 360
# define FRAMES 100
# define MAX_DEPTH 20
# define LIGHT_INTENSITY 100.0
# define BUFFER_SIZE_RT 16384
# define SHADOW_ACNE_FIX 1e-3
# define SPACES " \f\n\r\t\v"
# define UINT_SEED 3941839098

# define SURFACES_CYLINDER 3
# define SURFACES_PLANE 1
# define SURFACES_SPHERE 1

// TODO: try vec3 of doubles
typedef float	t_vec3 __attribute__((vector_size(16)));

/******************************************************************************/
/*                                                                            */
/*                                   BASIC                                    */
/*                                                                            */
/******************************************************************************/

typedef struct s_ray {
	t_vec3	origin;
	t_vec3	direction;
	float	distance;
}	t_ray;

typedef struct s_interval {
	float	min;
	float	max;
}	t_interval;

/******************************************************************************/
/*                                                                            */
/*                                 MATERIALS                                  */
/*                                                                            */
/******************************************************************************/

typedef struct t_dielectric {
	t_vec3	albedo;
	float	ir;
}	t_dielectric;

typedef struct t_lambertian {
	t_vec3	albedo;
	float	ka;
	float	kd;
	float	ks;
	float	specular_exponent;
}	t_lambertian;

typedef struct t_metal {
	t_vec3	albedo;
	float	fuzz;
}	t_metal;

typedef enum e_material_type {
	MATERIAL_DIELECTRIC = 0,
	MATERIAL_LAMBERTIAN,
	MATERIAL_METAL,
}	t_material_type;

typedef union u_material_union {
	t_dielectric	dielectric;
	t_lambertian	lambertian;
	t_metal			metal;
}	t_material_union;

typedef struct t_material {
	t_material_type		type;
	t_material_union	u;
}	t_material;

/******************************************************************************/
/*                                                                            */
/*                                  OBJECTS                                   */
/*                                                                            */
/******************************************************************************/

typedef struct s_sphere {
	t_vec3		center;
	float		radius;
	t_vec3		color;
	t_material	material;
}	t_sphere;

typedef struct s_plane {
	t_vec3		coord;
	t_vec3		vector;
	t_vec3		color;
	t_material	material;
}	t_plane;

typedef struct s_disk {
	t_plane	plane;
	float	radius;
}	t_disk;

typedef struct s_tube {
	t_vec3		center;
	t_vec3		axis;
	float		radius;
	float		half_height;
	t_vec3		color;
	t_material	material;
}	t_tube;

typedef enum e_object_type {
	OBJECT_DISK = 0,
	OBJECT_PLANE,
	OBJECT_SPHERE,
	OBJECT_TUBE
}	t_object_type;

typedef union u_object_union {
	t_disk		disk;
	t_plane		plane;
	t_sphere	sphere;	
	t_tube		tube;
}	t_object_union;

typedef struct s_object {
	t_object_type	type;
	t_object_union	u;
}	t_object;

/******************************************************************************/
/*                                                                            */
/*                                  ELEMENTS                                  */
/*                                                                            */
/******************************************************************************/

typedef struct s_ambient {
	bool	exists;
	t_vec3	color;
}	t_ambient;

typedef struct s_camera {
	bool	exists;
	float	aspect_ratio;
	float	viewport_width;
	float	viewport_height;
	float	lens_radius;
	float	focus_dist;
	t_vec3	origin;
	t_vec3	orientation;
	t_vec3	lower_left;
	t_vec3	horizontal;
	t_vec3	vertical;
	t_vec3	u;
	t_vec3	v;
}	t_camera;

typedef struct s_light {
	t_vec3	coord;
	t_vec3	color;
}	t_light;

/******************************************************************************/
/*                                                                            */
/*                                  GENERAL                                   */
/*                                                                            */
/******************************************************************************/

typedef struct s_hit {
	bool		front_face;
	float		t;
	t_vec3		point;
	t_vec3		normal;
	t_material	material;
}	t_hit;

typedef struct s_scene {
	t_ambient	ambient;
	t_camera	camera;
	t_light		*lights;
	t_object	*world;
	int			nb_obj;
	int			nb_lights;
}	t_scene;

typedef struct s_mlx {
	int		bytes_per_pixel;
	int		line_length;
	int		*addr;
	void	*win;
	void	*img;
	void	*mlx;
}	t_mlx;

typedef struct s_mutex
{
	pthread_mutex_t	access_data;
	pthread_mutex_t	access_image;
}	t_mutex;

struct	s_thread;

typedef struct s_data {
	int				frame;
	int				cpus_count;
	bool			stop;
	t_mutex			mutex;
	t_mlx			mlx;
	t_vec3			**pixels;
	t_scene			scene;
	struct s_thread	*threads;
}	t_data;

typedef struct s_thread
{
	int			idx;
	int			cur_frame;
	pthread_t	pthread_id;
	t_data		*data;
}	t_thread;

/******************************************************************************/
/*                                                                            */
/*                                 PROTOTYPES                                 */
/*                                                                            */
/******************************************************************************/

typedef bool	(*t_scatter_func)(t_ray, t_hit, t_ray *);

// display
t_vec3			get_color(t_scene *scene, t_hit *hit, t_ray ray);
t_vec3			get_ambient_color(t_scene *scene, t_hit *hit);
t_vec3			get_diffuse_color(t_light *light, t_hit *hit, t_ray *light_ray);
t_vec3			get_specular_color(t_light *light, t_hit *hit, t_ray *ray,
					t_ray *light_ray);
t_ray			get_ray(const t_camera *camera, float s, float t);
t_vec3			ray_at(t_ray ray, float t);
t_vec3			reflect(t_vec3 v, t_vec3 n);
float			reflectance(float cosine, float ref_idx);
t_vec3			refract(t_vec3 v, t_vec3 n, float ir);
int				render_frame(t_data *data);
bool			scatter(t_ray ray, t_hit hit, t_ray *scattered);
void			set_face_normal(t_hit *hit, t_ray *ray, t_vec3 *outward_normal);

// hit
bool			hit_disk(t_hit *hit, const t_disk *disk, t_ray *ray,
					t_interval interval);
bool			hit_sphere(t_hit *hit, const t_sphere *sphere, t_ray *ray,
					t_interval interval);
bool			hit_plane(t_hit *hit, const t_plane *plane, t_ray *ray,
					t_interval interval);
bool			hit_tube(t_hit *hit, const t_tube *tube, t_ray *ray,
					t_interval interval);
bool			hit_world(t_hit *hit, t_scene *scene, t_ray *ray,
					t_interval interval);

// mlx_tools
int				handle_key_down(int keycode, t_data *data);
bool			init_minilibx(t_mlx *mlx, char *window_title);

// parsing
bool			ft_atof(char *s, float *ans);
bool			ft_atof_range(char *s, float *ans, float min, float max);
bool			get_commas2(char *s, char **s2);
bool			get_commas3(char *s, char **s2, char **s3);
bool			get_commas4(char *s, char **s2, char **s3, char **s4);
char			***get_words(char *filename);
bool			parse_ambient(t_scene *scene, char **line);
bool			parse_camera(t_scene *scene, char **line);
bool			parse_color(char *s, t_vec3 *color);
bool			parse_coord(char *s, t_vec3 *coord);
bool			parse_cylinder(t_scene *scene, char **line,
					int *current_object);
bool			parse_lights(t_scene *scene, char **line);
bool			parse_normalized_vector(char *s, t_vec3 *vector);
bool			parse_plane(t_scene *scene, char **line, int *current_object);
bool			parse_scene(t_scene *scene, int argc, char **argv);
bool			parse_sphere(t_scene *scene, char **line, int *current_object);

// utils
int				arrlen(char **lines);
int				clamp(int x, int min, int max);
int				close_window(t_data *data);
bool			complain_bool(char *error_message);
int				complain_int(char *error_message);
void			*complain_ptr(char *error_message);
float			fclampf(float x, float min, float max);
void			free_data(t_data *data);
unsigned int	get_random_uint(void);
float			get_random_float(void);
float			get_random_float_range(float min, float max);
t_vec3			get_random_in_unit_disk(void);
t_vec3			get_random_in_unit_sphere(void);
t_vec3			get_random_unit_vector(void);
bool			includes(char **arr, char *s);
bool			in_interval(t_interval interval, float x);
bool			init_pixels(t_data *data);
bool			is_close(float x, float y);
void			print_vec3(char *name, t_vec3 v); // TODO remove
int				sign(float x);

// vec3
float			vec3_dot(t_vec3 v1, t_vec3 v2);
t_vec3			vec3_cross(t_vec3 v1, t_vec3 v2);
bool			vec3_near_zero(t_vec3 v);
float			vec3_length_squared(t_vec3 v);
float			vec3_length(t_vec3 v);
t_vec3			vec3_unit(t_vec3 v);
float			vec3_dist_squared(t_vec3 v1, t_vec3 v2);

// multi-threading
void			render_thread_frame(t_thread *thread);
void			*routine(t_thread *thread);

#endif
