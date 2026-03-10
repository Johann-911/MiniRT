#include "../inc/rt_math.h"
#include <math.h>
#include <stdint.h>
#include <aio.h>

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
t_vec3 vec3_mul(t_vec3 v, double scalar)
{
	return (vec3(v.x * scalar, v.y * scalar, v.z * scalar));
}

t_vec3	vec3_norm(t_vec3 v)
{
	double l;

	l = vec3_len(v);
	if (l == 0.0)
		return (vec3(0.0, 0.0, 0.0));
	return (vec3_mul(v, 1.0 / l));
}

double	ft_atod(const char *str)
{
	size_t i;
	double		integer;
	int		sign;
	int divisor;

	divisor = 10.0;
	i = 0;
	integer = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * (-1);
		i++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		integer = (integer * 10) + (str[i] - '0');
		i++;
	}
	if(str[i] == '.')
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
	    integer += (str[i] - '0') / divisor;
        divisor *= 10.0;
        i++;
	}
	return (sign * integer);
}
