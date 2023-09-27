#ifndef PROTOTYPES_H
# define PROTOTYPES_H

typedef bool	(*t_scatter_func)(t_ray, t_hit, t_ray *);

/******************************************************************************/
/*                                                                            */
/*                                    HIT                                     */
/*                                                                            */
/******************************************************************************/

bool			hit_aabb(t_hit *hit, t_aabb *aabb, t_ray *ray,
					t_interval interval);
bool			hit_disk(t_hit *hit, const t_disk *disk, t_ray *ray,
					t_interval interval);
bool			hit_plane(t_hit *hit, const t_plane *plane, t_ray *ray,
					t_interval interval);
bool			hit_sphere(t_hit *hit, const t_sphere *sphere, t_ray *ray,
					t_interval interval);
bool			hit_tube(t_hit *hit, const t_tube *tube, t_ray *ray,
					t_interval interval);
bool			hit_world(t_hit *hit, t_scene *scene, t_ray *ray,
					t_interval interval);
void			set_face_normal(t_hit *hit, t_ray *ray, t_vec3 *outward_normal);

/******************************************************************************/
/*                                                                            */
/*                                    INIT                                    */
/*                                                                            */
/******************************************************************************/

bool			init_minilibx(t_mlx *mlx, char *window_title);
bool			init_mutexes(t_data *data);
bool			init_pixel_colors(t_data *data);
bool			init_pixel_coordinates(t_data *data);
bool			init_thread(t_data *data);

/******************************************************************************/
/*                                                                            */
/*                                  PARSING                                   */
/*                                                                            */
/******************************************************************************/

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

/******************************************************************************/
/*                                                                            */
/*                                   RANDOM                                   */
/*                                                                            */
/******************************************************************************/

float			get_random_float(void);
float			get_random_float_range(float min, float max);
t_vec3			get_random_in_unit_disk(void);
t_vec3			get_random_in_unit_sphere(void);
unsigned int	get_random_uint(void);
unsigned int	get_random_uint_range(unsigned int a, unsigned int b);
t_vec3			get_random_unit_vector(void);

/******************************************************************************/
/*                                                                            */
/*                                   RENDER                                   */
/*                                                                            */
/******************************************************************************/

t_vec3			get_color(t_scene *scene, t_hit *hit, t_ray ray);
t_vec3			reflect(t_vec3 v, t_vec3 n);
float			reflectance(float cosine, float ref_idx);
t_vec3			refract(t_vec3 v, t_vec3 n, float ir);
int				render_frame(t_data *data);
void			*routine(t_thread *thread);
bool			scatter(t_ray ray, t_hit hit, t_ray *scattered);

/******************************************************************************/
/*                                                                            */
/*                                  STRUCTS                                   */
/*                                                                            */
/******************************************************************************/

t_interval		expand_interval(t_interval interval, float delta);
bool			in_interval(t_interval interval, float x);
t_aabb			new_aabb(t_vec3 a, t_vec3 b);
t_vec3			ray_at(t_ray ray, float t);
t_vec3			vec3_cross(t_vec3 v1, t_vec3 v2);
float			vec3_dist_squared(t_vec3 v1, t_vec3 v2);
float			vec3_dot(t_vec3 v1, t_vec3 v2);
float			vec3_length(t_vec3 v);
float			vec3_length_squared(t_vec3 v);
bool			vec3_near_zero(t_vec3 v);
t_vec3			vec3_unit(t_vec3 v);

/******************************************************************************/
/*                                                                            */
/*                                   UTILS                                    */
/*                                                                            */
/******************************************************************************/

int				arrlen(char **lines);
int				clamp(int x, int min, int max);
int				close_window(t_data *data);
bool			complain_bool(char *error_message);
int				complain_int(char *error_message);
void			*complain_ptr(char *error_message);
float			fclampf(float x, float min, float max);
void			free_data(t_data *data);
int				handle_key_down(int keycode, t_data *data);
bool			is_close(float x, float y);
void			print_vec3(char *name, t_vec3 v); // TODO: remove
int				sign(float x);

#endif
