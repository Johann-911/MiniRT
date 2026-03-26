/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_math_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephan <stephan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 21:16:14 by stliu             #+#    #+#             */
/*   Updated: 2026/03/26 10:35:57 by stephan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/rt_math.h"
#include <math.h>
#include <stdint.h>
#include <stddef.h>


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
    size_t	i;
    double	res;
    double	sign;
    double	div;

    i = 0;
    res = 0.0;
    sign = 1.0;
    div = 10.0;
    while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1.0;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        res = res * 10.0 + (double)(str[i] - '0');
        i++;
    }
    if (str[i] == '.')
        i++;
    while (str[i] >= '0' && str[i] <= '9')
    {
        res += (double)(str[i] - '0') / div;
        div *= 10.0;
        i++;
    }
    return (sign * res);
}

t_vec3	perturb_normal(t_vec3 base_n, t_vec3 p_local, double stren, double freq)
{
    t_vec3	n;
    t_vec3	u;
    t_vec3	v;
    double	nx;
    double	ny;

    n = vec3_norm(base_n);
    if (fabs(n.x) < 0.9)
        u = vec3_norm(vec3_cross(vec3(1.0, 0.0, 0.0), n));
    else
        u = vec3_norm(vec3_cross(vec3(0.0, 1.0, 0.0), n));
    v = vec3_cross(n, u);
    nx = sin(p_local.x * freq) * cos(p_local.y * freq);
    ny = cos(p_local.z * freq) * sin(p_local.y * freq);
    return (vec3_norm(vec3_add(n, vec3_add(vec3_mul(u, nx * stren),
                vec3_mul(v, ny * stren)))));
}

