#include "../inc/rt_math.h"
#include <math.h>
#include <stdint.h>

t_vec3 vec3_cross(t_vec3 a, t_vec3 b)
{	
	return(vec3(a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z, 
		a.x * b.y - a.y * b.x));
}

double	vec3_len(t_vec3 v)
{
	return (sqrt(vec3_dot(v, v)));
}

t_vec3	vec3_norm(t_vec3 v)
{
	double l;

	l = vec3_len(v);
	if (l == 0.0)
		return (vec3(0.0, 0.0, 0.0));
	return (vec3_mul(v, 1.0 / l));
}