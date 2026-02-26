#include "../inc/rt_math.h"
#include <math.h>
#include <stdint.h>

t_vec3 vec3(double x, double y, double z)
{
	t_vec3 v;
	v.x = x;
	v.y = y;
	v.z = z;
	return v;
}

t_vec3 vec3_add(t_vec3 a, t_vec3 b)
{	
	return(vec3(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec3 vec3_sub(t_vec3 a, t_vec3 b)
{
	return(vec3(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vec3 vec3_mul(t_vec3 a, double s)
{
	return(vec3(a.x * s, a.y * s, a.z * s));
}

double vec3_dot(t_vec3 a, t_vec3 b)
{
	return(a.x - b.x, a.y - b.y, a.z - b.z);
}
