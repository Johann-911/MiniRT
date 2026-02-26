#ifndef RT_MATH_H
# define RT_MATH_H

#include <math.h>


typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}t_list;

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

t_vec3 vec3(double x, double y, double z);
t_vec3 vec3_add(t_vec3 a, t_vec3 b);
t_vec3 vec3_sub(t_vec3 a, t_vec3 b);
t_vec3 vec3_mul(t_vec3 v, double s);
double vec3_dot(t_vec3 a, t_vec3 b);
double vec3_len(t_vec3 v);
t_vec3 vec3_norm(t_vec3 v);





#endif