/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stliu <stliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 14:19:19 by stliu             #+#    #+#             */
/*   Updated: 2026/03/26 14:19:21 by stliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
#include "../inc/rt_math.h"

double	test_side(t_ray ray, t_cylinder *cy)
{
	double	t1;
	double	t2;
	double	ts;
	double	sqrt_d;

	ts = -1;
	sqrt_d = sqrt(cy->disc);
	t1 = (-cy->b - sqrt_d) / (2.0 * cy->a);
	t2 = (-cy->b + sqrt_d) / (2.0 * cy->a);
	if (t1 > 0.0)
	{
		cy->h_check = vec3_dot(vec3_sub(vec3_add(ray.origin,
						vec3_scale(ray.direction, t1)), cy->center), cy->axis);
		if (fabs(cy->h_check) <= cy->height / 2.0)
			ts = t1;
	}
	if (t2 > 0.0)
	{
		cy->h_check = vec3_dot(vec3_sub(vec3_add(ray.origin,
						vec3_scale(ray.direction, t2)), cy->center), cy->axis);
		if (fabs(cy->h_check) <= cy->height / 2.0)
			ts = min_pos(ts, t2);
	}
	return (ts);
}

void	setup_cyl(t_ray ray, t_cylinder *cy)
{
	cy->axis = vec3_norm(cy->vector);
	cy->oc = vec3_sub(ray.origin, cy->center);
	cy->proj_dir = vec3_sub(ray.direction, vec3_scale(cy->axis,
				vec3_dot(ray.direction, cy->axis)));
	cy->proj_oc = vec3_sub(cy->oc, vec3_scale(cy->axis, vec3_dot(cy->oc,
					cy->axis)));
}

double	disc_cyl(t_cylinder *cy)
{
	cy->a = vec3_dot(cy->proj_dir, cy->proj_dir);
	cy->b = 2.0 * vec3_dot(cy->proj_oc, cy->proj_dir);
	cy->c = vec3_dot(cy->proj_oc, cy->proj_oc) - (cy->radius * cy->radius);
	cy->disc = cy->b * cy->b - 4.0 * cy->a * cy->c;
	return (cy->disc);
}

double	inter_cap(t_ray ray, t_vec3 cap_center, t_vec3 cap_norm,
		double radius)
{
	t_plane	cap;
	t_vec3	hit;
	t_vec3	diff;
	double	t;

	cap.point = cap_center;
	cap.normal = cap_norm;
	t = inter_plane(ray, cap);
	if (t < 0)
		return (-1);
	hit = vec3_add(ray.origin, vec3_scale(ray.direction, t));
	diff = vec3_sub(hit, cap_center);
	if (vec3_len(diff) > radius)
		return (-1);
	return (t);
}
