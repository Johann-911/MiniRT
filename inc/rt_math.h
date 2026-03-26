#ifndef RT_MATH_H
# define RT_MATH_H

#include <math.h>
#include <stdbool.h>

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

typedef struct s_vec3
{
	double x;
	double y;
	double z;
}	t_vec3;

typedef struct s_rgb
{
	int r;
	int g;
	int b;
}t_rgb;

typedef struct s_sphere
{
	t_vec3	center;
	double 	r;
	t_rgb 	color;
}t_sphere;

typedef struct s_plane
{
	t_vec3	point;
	t_vec3 	normal;
	t_rgb 	color;

}t_plane;

typedef struct s_cylinder
{
	t_vec3 center;
	t_vec3 vector;
	double radius;
	double height;
	t_rgb color;
	t_vec3 axis;
	t_vec3 oc;
	t_vec3 proj_dir;
	t_vec3 proj_oc;
	double a;
	double b;
	double c;
	double disc;
	double h_check;
}t_cylinder;

typedef struct s_triangle
{
	t_vec3	x;
	t_vec3	y;
	t_vec3	z;
	t_rgb	color;
}t_triangle;

typedef struct s_cone
{
	t_vec3	tip;
	t_vec3	axis;
	double	radius;
	double	height;
	t_rgb	color;
	t_vec3	oc;
	double	k;
	double	dv;
	double	ov;
	double	dd;
	double	od;
	double	oo;
	double	a;
	double	b;
	double	c;
	double	disc;
	double	h;
}t_cone;

typedef struct s_light
{
	t_vec3 pos;
	double 	b;
	t_rgb color;
	struct s_light *next;
}t_light;


typedef union u_objects
{
	t_plane		plane;
	t_sphere	sphere;
	t_cylinder	cylinder;
	t_cone		cone;
	t_triangle	triangle;
}t_objects;

typedef enum e_obj_type
{
	OBJ_PLANE,
	OBJ_SPHERE,
	OBJ_CYLINDER,
	OBJ_CONE,
	OBJ_TRIANGLE
}t_obj_type;

typedef struct s_object
{
	t_obj_type	type;
	t_objects	data;
	struct s_object *next;
	int checker;
	int bump;
}	t_object;


typedef struct s_ambient
{
	double ratio;
	t_rgb color;
}t_ambient;


typedef struct s_camera
{
	t_vec3 origin;
	t_vec3 vector;
	double fov;
}t_camera;

typedef struct s_ray
{
	t_vec3 origin;
	t_vec3 direction;
} t_ray;

typedef struct s_scene
{
	t_ambient ambient;
	t_camera  camera;
	t_light		*light;
	t_object	*objects;
	int			nb_lights;
    int			nb_objects;
    int			has_ambient;
    int			has_camera;
}t_scene;

typedef struct s_hit
{
    double	t;
    t_vec3	point;
    t_vec3	normal;
    t_rgb	color;
    int		hit;
}t_hit;

t_vec3 vec3(double x, double y, double z);
t_vec3 vec3_add(t_vec3 a, t_vec3 b);
t_vec3 vec3_sub(t_vec3 a, t_vec3 b);
t_vec3 vec3_scale(t_vec3 v, double s);
double vec3_dot(t_vec3 a, t_vec3 b);
double vec3_len(t_vec3 v);
t_vec3 vec3_norm(t_vec3 v);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);
double	ft_atod(const char *str);
t_hit   closest_hit(t_ray ray, t_scene *scene);
int		any_hit_before(t_ray ray, t_scene *scene, double max_t);

//intersection functions
double	inter_sphere(t_ray ray, t_sphere sphere);
double	inter_plane(t_ray ray, t_plane plane);
double	inter_cylinder(t_ray ray, t_cylinder cylinder);
double	inter_cone(t_ray ray, t_cone cone);


// normal functions
t_vec3	norm_sphere(t_vec3 point, t_sphere *sphere);
t_vec3	norm_plane(t_plane *plane);
t_vec3	normal_cylinder(t_vec3 point, t_cylinder *cylinder);
t_vec3  normal_cone(t_vec3 point, t_cone *cone);
void	set_normal(t_hit *result, t_object *obj, t_vec3 hit_point);

// cone
void	setup_cone(t_ray ray, t_cone *co);
double	disc_cone(t_cone *co);
double	test_cone_side(t_cone *co);
double	inter_cone(t_ray ray, t_cone co);

// cylinder
void	setup_cyl(t_ray ray, t_cylinder *cy);
double	disc_cyl(t_cylinder *cy);
double	test_side(t_ray ray, t_cylinder *cy);


double	inter_cap(t_ray ray, t_vec3 cap_center, t_vec3 cap_norm, double radius);
double	min_pos(double t1, double t2);
t_vec3	perturb_normal(t_vec3 base_n, t_vec3 p_local, double stren, double freq);



#endif