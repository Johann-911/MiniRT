/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stliu <stliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 14:43:39 by stliu             #+#    #+#             */
/*   Updated: 2026/03/26 14:26:17 by stliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
#include "../inc/rt_math.h"

double	min_pos(double t1, double t2)
{
	if (t1 > 0 && t2 > 0)
	{
		if (t1 < t2)
			return (t1);
		return (t2);
	}
	if (t1 > 0)
		return (t1);
	if (t2 > 0)
		return (t2);
	return (-1);
}

double	discriminant(double a, double b, double c)
{
	double	d;

	d = b * b - 4 * a * c;
	if (d < 0)
		return (-1);
	return ((-b - sqrt(d)) / (2 * a));
}

t_rgb	checker_planar(t_vec3 p)
{
	double	size;
	int		ix;
	int		iz;
	t_rgb	c;

	size = 10.0;
	ix = (int)floor(p.x / size);
	iz = (int)floor(p.z / size);
	if ((ix + iz) % 2 == 0)
	{
		c.r = 255;
		c.g = 255;
		c.b = 255;
		return (c);
	}
	c.r = 0;
	c.g = 0;
	c.b = 0;
	return (c);
}

t_rgb	checker_sphere(t_vec3 n)
{
	double	u;
	double	v;
	int		iu;
	int		iv;
	t_rgb	c;

	u = 0.5 + atan2(n.z, n.x) / (2.0 * M_PI);
	v = 0.5 - asin(n.y) / M_PI;
	iu = (int)floor(u * 8.0);
	iv = (int)floor(v * 8.0);
	if ((iu + iv) % 2 == 0)
	{
		c.r = 255;
		c.g = 255;
		c.b = 255;
		return (c);
	}
	c.r = 0;
	c.g = 0;
	c.b = 0;
	return (c);
}

t_rgb	checker_cylinder(t_vec3 p, t_cylinder *cy)
{
	int		iu;
	int		iv;
	t_rgb	c;

	cy->axis = vec3_norm(cy->vector);
	cy->proj_dir = vec3_sub(p, cy->center);
	cy->proj_oc = vec3_sub(cy->proj_dir, vec3_scale(cy->axis,
				vec3_dot(cy->proj_dir, cy->axis)));
	cy->h_check = (atan2(cy->proj_oc.z, cy->proj_oc.x) + M_PI)
		/ (2.0 * M_PI);
	cy->disc = (vec3_dot(cy->proj_dir, cy->axis) / cy->height) + 0.5;
	iu = (int)floor(cy->h_check * 10.0);
	iv = (int)floor(cy->disc * 10.0);
	if ((iu + iv) % 2 == 0)
	{
		c.r = 255;
		c.g = 255;
		c.b = 255;
		return (c);
	}
	c.r = 0;
	c.g = 0;
	c.b = 0;
	return (c);
}
