/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stliu <stliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 14:19:47 by stliu             #+#    #+#             */
/*   Updated: 2026/03/26 14:19:49 by stliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
#include "../inc/rt_math.h"

void	set_normal(t_hit *result, t_object *obj, t_vec3 hit_point)
{
	t_vec3	local_p;

	if (obj->type == OBJ_SPHERE)
	{
		result->normal = norm_sphere(hit_point, &obj->data.sphere);
		local_p = vec3_sub(hit_point, obj->data.sphere.center);
	}
	else if (obj->type == OBJ_PLANE)
	{
		result->normal = norm_plane(&obj->data.plane);
		local_p = hit_point;
	}
	else if (obj->type == OBJ_CYLINDER)
	{
		result->normal = normal_cylinder(hit_point, &obj->data.cylinder);
		local_p = vec3_sub(hit_point, obj->data.cylinder.center);
	}
	else
	{
		result->normal = normal_cone(hit_point, &obj->data.cone);
		local_p = vec3_sub(hit_point, obj->data.cone.tip);
	}
	if (obj->bump)
		result->normal = perturb_normal(result->normal, local_p, 0.08, 1.0);
}

t_vec3	norm_sphere(t_vec3 point, t_sphere *sphere)
{
	return (vec3_norm(vec3_sub(point, sphere->center)));
}

t_vec3	norm_plane(t_plane *plane)
{
	return (vec3_norm(plane->normal));
}

t_vec3	normal_cylinder(t_vec3 point, t_cylinder *cylinder)
{
	t_vec3	axis;
	t_vec3	to_point;
	t_vec3	proj;
	t_vec3	radial;

	axis = vec3_norm(cylinder->vector);
	to_point = vec3_sub(point, cylinder->center);
	proj = vec3_scale(axis, vec3_dot(to_point, axis));
	radial = vec3_sub(to_point, proj);
	return (vec3_norm(radial));
}

t_vec3	normal_cone(t_vec3 point, t_cone *cone)
{
	t_vec3 axis;
	t_vec3 to_point;
	t_vec3 radial;
	double proj_len;
	double k;

	axis = vec3_norm(cone->axis);
	to_point = vec3_sub(point, cone->tip);
	proj_len = vec3_dot(to_point, axis);
	radial = vec3_sub(to_point, vec3_scale(axis, proj_len));
	k = cone->radius / cone->height;
	return (vec3_norm(vec3_sub(radial, vec3_scale(axis, vec3_len(radial)
					* k))));
}
