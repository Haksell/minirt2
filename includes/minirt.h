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

# include "defines.h"
# include "errors.h"

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

typedef struct s_aabb {
	t_interval	x;
	t_interval	y;
	t_interval	z;
}	t_aabb;

typedef struct s_pixel_coordinate {
	int	x;
	int	y;
}	t_pixel_coordinate;

/******************************************************************************/
/*                                                                            */
/*                                 MATERIALS                                  */
/*                                                                            */
/******************************************************************************/

typedef struct t_dielectric {
	float	ir;
}	t_dielectric;

typedef struct t_lambertian {
	float	ka;
	float	kd;
	float	ks;
	float	specular_exponent;
}	t_lambertian;

typedef struct t_metal {
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
	t_vec3				albedo;
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
	t_material	material;
}	t_sphere;

typedef struct s_plane {
	t_vec3		coord;
	t_vec3		vector;
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
	int					frame;
	int					cpus_count;
	bool				stop;
	t_mutex				mutex;
	t_mlx				mlx;
	t_vec3				**pixel_colors;
	t_pixel_coordinate	*pixel_coordinates;
	t_scene				scene;
	struct s_thread	*threads;
}	t_data;

typedef struct s_thread
{
	int					idx;
	int					cur_frame;
	pthread_t			pthread_id;
	t_pixel_coordinate	*pixels_to_manage;
	size_t				pixels_count;
	t_data				*data;
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
t_vec3			ray_at(t_ray ray, float t);
t_vec3			reflect(t_vec3 v, t_vec3 n);
float			reflectance(float cosine, float ref_idx);
t_vec3			refract(t_vec3 v, t_vec3 n, float ir);
int				render_frame(t_data *data);
void			*routine(t_thread *thread);
bool			scatter(t_ray ray, t_hit hit, t_ray *scattered);

// hit
bool			hit_aabb(t_hit *hit, t_aabb *aabb, t_ray *ray,
					t_interval interval);
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
void			set_face_normal(t_hit *hit, t_ray *ray, t_vec3 *outward_normal);

// init
bool			init_mutexes(t_data *data);
bool			init_thread(t_data *data);
bool			init_minilibx(t_mlx *mlx, char *window_title);

// parsing
bool			ft_atof(char *s, float *ans);
bool			ft_atof_range(char *s, float *ans, float min, float max);
bool			get_commas3(char *s, char **s2, char **s3);
bool			get_commas4(char *s, char **s2, char **s3, char **s4);
char			***get_words(char *filename);
bool			parse_ambient(t_scene *scene, char **line);
bool			parse_camera(t_scene *scene, char **line);
bool			parse_color(char *s, t_vec3 *color);
bool			parse_coord(char *s, t_vec3 *coord);
bool			parse_cylinder(t_scene *scene, char **line,
					int *current_object);
bool			parse_lights(t_scene *scene, char **line, int *current_light);
bool			parse_material(char *material_name, char *attributes,
					t_material *material);
bool			parse_normalized_vector(char *s, t_vec3 *vector);
bool			parse_plane(t_scene *scene, char **line, int *current_object);
bool			parse_scene(t_scene *scene, int argc, char **argv);
bool			parse_sphere(t_scene *scene, char **line, int *current_object);

// random
unsigned int	get_random_uint(void);
unsigned int	get_random_uint_range(unsigned int a, unsigned int b);
float			get_random_float(void);
float			get_random_float_range(float min, float max);
t_vec3			get_random_in_unit_disk(void);
t_vec3			get_random_in_unit_sphere(void);
t_vec3			get_random_unit_vector(void);

// structs
t_interval		expand_interval(t_interval interval, float delta);
bool			in_interval(t_interval interval, float x);
t_aabb			new_aabb(t_vec3 a, t_vec3 b);
float			vec3_dot(t_vec3 v1, t_vec3 v2);
t_vec3			vec3_cross(t_vec3 v1, t_vec3 v2);
bool			vec3_near_zero(t_vec3 v);
float			vec3_length_squared(t_vec3 v);
float			vec3_length(t_vec3 v);
t_vec3			vec3_unit(t_vec3 v);
float			vec3_dist_squared(t_vec3 v1, t_vec3 v2);

// utils
int				arrlen(char **lines);
int				clamp(int x, int min, int max);
int				close_window(t_data *data);
bool			complain_bool(char *error_message);
int				complain_int(char *error_message);
void			*complain_ptr(char *error_message);
float			fclampf(float x, float min, float max);
void			free_data(t_data *data);
int				handle_key_down(int keycode, t_data *data);
bool			init_pixel_colors(t_data *data);
bool			init_pixel_coordinates(t_data *data);
bool			is_close(float x, float y);
void			print_vec3(char *name, t_vec3 v); // TODO remove
int				sign(float x);

#endif
