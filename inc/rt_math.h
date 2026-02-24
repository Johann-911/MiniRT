#ifndef RT_MATH_H
# define RT_MATH_H

#include <math.h>

typedef struct s_vec3
{
	double x;
	double y;
	double z;
}	t_vec3;

typedef struct s_rgb
{
	double r;
	double g;
	double b;
}t_rgb;

typedef struct s_sphere
{
	double x;
	double y;
	double z;
	double r;
	t_rgb color;
}t_sphere;

typedef struct s_plane
{
	double x;
	double y;
	double z;
	t_vec3 vector;
	t_rgb color;
}t_plane;

typedef struct s_cylinder
{
	double x;
	double y;
	double z;
	t_vec3 vector;
	double dia;
	double height;
	t_rgb color;
}t_cylinder;

typedef struct s_light
{
	double x;
	double y;
	double z;
	float 	b;
	t_rgb color;
}t_light;


typedef union u_objects
{
	t_plane		plane;
	t_sphere	sphere;
	t_cylinder	cylinder;
}t_objects;

typedef struct s_ambient
{
	double ratio;
	t_rgb color;
}t_ambient;

typedef struct s_camera
{
	double x;
	double y;
	double z;
	t_vec3 vector;
	float fov;
}t_camera;

typedef struct s_scene
{
	t_ambient ambient;
	t_camera  camera;
	t_light		light;
	t_objects	objects;
}t_scene;.0

......................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................t_vec3 vec3(double x, double y, double z);
t_vec3 vec3_add(t_vec3 a, t_vec3 b);
t_vec3 vec3_sub(t_vec3 a, t_vec3 b);
t_vec3 vec3_mul(t_vec3 v, double s);
double vec3_dot(t_vec3 a, t_vec3 b);
double vec3_len(t_vec3 v);
t_vec3 vec3_norm(t_vec3 v);





#endif