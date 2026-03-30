/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
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

t_vec3	camera_right(t_vec3 forward)
{
	t_vec3	up;

	up = vec3(0.0, 1.0, 0.0);
	if (fabs(vec3_dot(forward, up)) > 0.999)
		up = vec3(1.0, 0.0, 0.0);
	return (vec3_norm(vec3_cross(forward, up)));
}

void	init_cam(t_cam *cam, t_scene *scene)
{
	cam->forward = vec3_norm(scene->camera.vector);
	cam->right = camera_right(cam->forward);
	cam->up = vec3_norm(vec3_cross(cam->right, cam->forward));
	cam->aspect = 1200.0 / 1000.0;
	cam->fov_scale = tan((scene->camera.fov * 0.5) * (M_PI / 180.0));
}

t_ray	generate_ray(t_cam *cam, t_scene *scene, int x, int y)
{
	t_ray	ray;
	double	px;
	double	py;

	px = (2.0 * ((x + 0.5) / 1200.0) - 1.0) * cam->aspect * cam->fov_scale;
	py = (1.0 - 2.0 * ((y + 0.5) / 1000.0)) * cam->fov_scale;
	ray.origin = scene->camera.origin;
	ray.direction = vec3_norm(vec3_add(cam->forward,
				vec3_add(vec3_scale(cam->right, px),
					vec3_scale(cam->up, py))));
	return (ray);
}
