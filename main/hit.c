/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stliu <stliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 14:26:17 by stliu             #+#    #+#             */
/*   Updated: 2026/03/26 14:26:17 by stliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
#include "../inc/rt_math.h"

static t_rgb	checker_cone(t_vec3 p, t_cone *co)
{
	int		iu;
	int		iv;
	t_rgb	c;

	co->axis = vec3_norm(co->axis);
	co->oc = vec3_sub(p, co->tip);
	co->dv = vec3_dot(co->oc, co->axis);
	co->oc = vec3_sub(co->oc, vec3_scale(co->axis, co->dv));
	co->h = (atan2(co->oc.z, co->oc.x) + M_PI) / (2.0 * M_PI);
	co->disc = co->dv / co->height;
	iu = (int)floor(co->h * 10.0);
	iv = (int)floor(co->disc * 10.0);
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

void	set_color(t_hit *result, t_object *obj, t_vec3 hp, t_vec3 normal)
{
	if (obj->checker)
	{
		if (obj->type == OBJ_SPHERE)
			result->color = checker_sphere(normal);
		else if (obj->type == OBJ_CYLINDER)
			result->color = checker_cylinder(hp, &obj->data.cylinder);
		else if (obj->type == OBJ_CONE)
			result->color = checker_cone(hp, &obj->data.cone);
		else
			result->color = checker_planar(hp);
		return ;
	}
	if (obj->type == OBJ_SPHERE)
		result->color = obj->data.sphere.color;
	else if (obj->type == OBJ_PLANE)
		result->color = obj->data.plane.color;
	else if (obj->type == OBJ_CYLINDER)
		result->color = obj->data.cylinder.color;
	else
		result->color = obj->data.cone.color;
}

double	get_dist(t_ray ray, t_object *obj)
{
	if (obj->type == OBJ_SPHERE)
		return (inter_sphere(ray, obj->data.sphere));
	if (obj->type == OBJ_PLANE)
		return (inter_plane(ray, obj->data.plane));
	if (obj->type == OBJ_CYLINDER)
		return (inter_cylinder(ray, obj->data.cylinder));
	if (obj->type == OBJ_CONE)
		return (inter_cone(ray, obj->data.cone));
	return (-1);
}

t_hit	closest_hit(t_ray ray, t_scene *scene)
{
	t_hit		result;
	t_object	*obj;
	double		dist;
	t_vec3		hp;

	result.hit = 0;
	result.t = -1;
	obj = scene->objects;
	while (obj)
	{
		dist = get_dist(ray, obj);
		if (dist > 0 && (!result.hit || dist < result.t))
		{
			result.t = dist;
			result.hit = 1;
			hp = vec3_add(ray.origin, vec3_scale(ray.direction, dist));
			result.point = hp;
			set_normal(&result, obj, hp);
			set_color(&result, obj, hp, result.normal);
		}
		obj = obj->next;
	}
	return (result);
}

int	any_hit_before(t_ray ray, t_scene *scene, double max_t)
{
	t_object	*obj;
	double		dist;

	obj = scene->objects;
	while (obj)
	{
		dist = get_dist(ray, obj);
		if (dist > 1e-3 && dist < max_t)
			return (1);
		obj = obj->next;
	}
	return (0);
}
