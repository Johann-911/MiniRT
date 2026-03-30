/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stliu <stliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 14:19:19 by stliu             #+#    #+#             */
/*   Updated: 2026/03/26 14:19:21 by stliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
#include "../inc/window.h"

void	setup_cone(t_ray ray, t_cone *co)
{
	co->axis = vec3_norm(co->axis);
	co->oc = vec3_sub(ray.origin, co->tip);
	co->k = co->radius / co->height;
	co->k = co->k * co->k;
	co->dv = vec3_dot(ray.direction, co->axis);
	co->ov = vec3_dot(co->oc, co->axis);
	co->dd = vec3_dot(ray.direction, ray.direction);
	co->od = vec3_dot(co->oc, ray.direction);
	co->oo = vec3_dot(co->oc, co->oc);
}

double	disc_cone(t_cone *co)
{
	co->a = (1.0 + co->k) * co->dv * co->dv - co->dd;
	co->b = 2.0 * ((1.0 + co->k) * co->dv * co->ov - co->od);
	co->c = (1.0 + co->k) * co->ov * co->ov - co->oo;
	co->disc = co->b * co->b - 4.0 * co->a * co->c;
	return (co->disc);
}

double	test_cone_side(t_cone *co)
{
	double	t1;
	double	t2;
	double	ts;
	double	sqrt_d;

	ts = -1;
	sqrt_d = sqrt(co->disc);
	t1 = (-co->b - sqrt_d) / (2.0 * co->a);
	t2 = (-co->b + sqrt_d) / (2.0 * co->a);
	if (t1 > 0.0)
	{
		co->h = co->ov + t1 * co->dv;
		if (co->h >= 0.0 && co->h <= co->height)
			ts = t1;
	}
	if (t2 > 0.0)
	{
		co->h = co->ov + t2 * co->dv;
		if (co->h >= 0.0 && co->h <= co->height)
			ts = min_pos(ts, t2);
	}
	return (ts);
}
