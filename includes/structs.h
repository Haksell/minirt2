#ifndef STRUCTS_H
# define STRUCTS_H

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

typedef struct s_bbox {
	t_interval	x;
	t_interval	y;
	t_interval	z;
}	t_bbox;

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
	t_bbox		bbox;
}	t_sphere;

typedef struct s_plane {
	t_vec3		coord;
	t_vec3		vector;
	t_material	material;
	t_bbox		bbox;
}	t_plane;

typedef struct s_disk {
	t_plane	plane;
	float	radius;
	t_bbox	bbox;
}	t_disk;

typedef struct s_tube {
	t_vec3		center;
	t_vec3		axis;
	float		radius;
	float		half_height;
	t_material	material;
	t_bbox		bbox;
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

struct			s_thread;

typedef struct s_data {
	int					frame;
	int					cpus_count;
	bool				stop;
	t_mutex				mutex;
	t_mlx				mlx;
	t_vec3				**pixel_colors;
	t_pixel_coordinate	*pixel_coordinates;
	t_scene				scene;
	struct s_thread		*threads;
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

#endif