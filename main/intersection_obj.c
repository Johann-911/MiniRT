/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_obj.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stliu <stliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 14:19:19 by stliu             #+#    #+#             */
/*   Updated: 2026/03/26 14:19:21 by stliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
#include "../inc/rt_math.h"

double	inter_cone(t_ray ray, t_cone co)
{
	double	ts;
	double	tb;
	t_vec3	bc;

	setup_cone(ray, &co);
	ts = -1;
	if (disc_cone(&co) >= 0.0 && fabs(co.a) > 1e-6)
		ts = test_cone_side(&co);
	bc = vec3_add(co.tip, vec3_scale(co.axis, co.height));
	tb = inter_cap(ray, bc, co.axis, co.radius);
	return (min_pos(ts, tb));
}

double	inter_cylinder(t_ray ray, t_cylinder cy)
{
	double	ts;
	double	tc1;
	double	tc2;
	t_vec3	cb;
	t_vec3	ct;

	setup_cyl(ray, &cy);
	ts = -1;
	if (disc_cyl(&cy) >= 0.0 && fabs(cy.a) > 1e-6)
		ts = test_side(ray, &cy);
	cb = vec3_sub(cy.center, vec3_scale(cy.axis, cy.height / 2.0));
	ct = vec3_add(cy.center, vec3_scale(cy.axis, cy.height / 2.0));
	tc1 = inter_cap(ray, cb, vec3_scale(cy.axis, -1.0), cy.radius);
	tc2 = inter_cap(ray, ct, cy.axis, cy.radius);
	return (min_pos(ts, min_pos(tc1, tc2)));
}

double	inter_plane(t_ray ray, t_plane plane)
{
	double	denominator;
	double	t;
	t_vec3	diff;

	denominator = vec3_dot(ray.direction, plane.normal);
	if (fabs(denominator) < 1e-6)
		return (-1);
	diff = vec3_sub(plane.point, ray.origin);
	t = vec3_dot(diff, plane.normal) / denominator;
	if (t < 0)
		return (-1);
	return (t);
}

double	inter_sphere(t_ray ray, t_sphere sphere)
{
	t_vec3	dis;
	double	a;
	double	b;
	double	c;
	double	disc;
	double	t1;
	double	t2;

	dis = vec3_sub(ray.origin, sphere.center);
	a = vec3_dot(ray.direction, ray.direction);
	b = 2.0 * vec3_dot(dis, ray.direction);
	c = vec3_dot(dis, dis) - sphere.r * sphere.r;
	disc = b * b - 4.0 * a * c;
	if (disc < 0.0 || fabs(a) < 1e-6)
		return (-1);
	t1 = (-b - sqrt(disc)) / (2.0 * a);
	t2 = (-b + sqrt(disc)) / (2.0 * a);
	return (min_pos(t1, t2));
}

double	inter_cap(t_ray ray, t_vec3 cap_center, t_vec3 cap_norm, double radius)
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
