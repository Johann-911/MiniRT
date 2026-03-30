/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_gen_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stliu <stliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 14:20:09 by stliu             #+#    #+#             */
/*   Updated: 2026/03/26 14:20:11 by stliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
#include "../inc/rt_math.h"
#include "../inc/window.h"

int	is_in_shadow(t_scene *scene, t_hit *hit, t_light *light)
{
	t_ray	shadow_ray;
	t_vec3	to_light;
	double	light_dist;

	to_light = vec3_sub(light->pos, hit->point);
	light_dist = vec3_len(to_light);
	shadow_ray.origin = vec3_add(hit->point, vec3_scale(hit->normal, 1e-3));
	shadow_ray.direction = vec3_norm(to_light);
	return (any_hit_before(shadow_ray, scene, light_dist));
}

static t_vec3	specular_contrib(t_vec3 view_dir, t_hit *hit,
		t_light *light, double ndotl)
{
	t_vec3	reflect_dir;
	double	spec;

	reflect_dir = vec3_sub(vec3_scale(hit->normal, 2.0 * ndotl),
			vec3_norm(vec3_sub(light->pos, hit->point)));
	reflect_dir = vec3_norm(reflect_dir);
	spec = vec3_dot(view_dir, reflect_dir);
	if (spec > 0.0)
		return (vec3_scale(color_from_rgb(light->color),
				pow(spec, 32.0) * 0.25 * light->b));
	return (vec3(0.0, 0.0, 0.0));
}

static void	shade_one_light(t_vec3 *out, t_hit *hit, t_light *light,
		t_vec3 view_dir)
{
	t_vec3	light_dir;
	double	ndotl;
	t_vec3	obj;
	t_vec3	lc;

	obj = color_from_rgb(hit->color);
	light_dir = vec3_norm(vec3_sub(light->pos, hit->point));
	ndotl = vec3_dot(hit->normal, light_dir);
	if (ndotl > 0.0)
	{
		lc = color_from_rgb(light->color);
		*out = vec3_add(*out, vec3_scale(color_mul(obj, lc),
					ndotl * light->b * 0.7));
		*out = vec3_add(*out, specular_contrib(view_dir, hit, light, ndotl));
	}
}

static t_vec3	shade_ambient(t_scene *scene, t_hit *hit)
{
	t_vec3	obj_color;
	t_vec3	amb_color;
	t_vec3	out;

	obj_color = color_from_rgb(hit->color);
	amb_color = color_from_rgb(scene->ambient.color);
	out = vec3_scale(color_mul(obj_color, amb_color),
			scene->ambient.ratio);
	if (scene->ambient.ratio < 0.05)
		out = vec3_add(out, vec3_scale(obj_color, 0.05));
	return (out);
}

int	shade_hit(t_scene *scene, t_hit *hit, t_vec3 cam_pos)
{
	t_light	*light;
	t_vec3	out;
	t_vec3	view_dir;

	out = shade_ambient(scene, hit);
	view_dir = vec3_norm(vec3_sub(cam_pos, hit->point));
	light = scene->light;
	while (light)
	{
		if (!is_in_shadow(scene, hit, light))
			shade_one_light(&out, hit, light, view_dir);
		light = light->next;
	}
	return (rgb_to_int_local(rgb_from_color(out)));
}
