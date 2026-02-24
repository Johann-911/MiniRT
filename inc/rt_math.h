#ifndef RT_MATH_H
# define RT_MATH_H

typedef struct s_vec3
{
	double x;
	double y;
	double z;
}	t_vec3;


t_vec3 vec3(double x, double y, double z);
t_vec3 vec3_add(t_vec3 a, t_vec3 b);
t_vec3 vec3_sub(t_vec3 a, t_vec3 b);
t_vec3 vec3_mul(t_vec3 v, double s);
double vec3_dot(t_vec3 a, t_vec3 b);
double vec3_len(t_vec3 v);
t_vec3 vec3_norm(t_vec3 v);





#endif