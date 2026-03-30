/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
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

static void	render_pixel(t_cam *cam, t_scene *scene, char *data, int *xy)
{
	t_ray	ray;
	t_hit	hit;
	int		color;

	ray = generate_ray(cam, scene, xy[0], xy[1]);
	hit = closest_hit(ray, scene);
	if (hit.hit && vec3_dot(hit.normal, ray.direction) > 0.0)
		hit.normal = vec3_scale(hit.normal, -1.0);
	color = 0x101020;
	if (hit.hit)
		color = shade_hit(scene, &hit, scene->camera.origin);
	put_pixel(data, xy[0], xy[1], color);
}

void	render_scene(t_app *app, t_scene *scene)
{
	int		x;
	int		y;
	int		xy[2];
	char	*data;
	t_cam	cam;

	init_cam(&cam, scene);
	data = mlx_get_data_addr(app->img, &x, &y, &x);
	y = 0;
	while (y < app->height)
	{
		x = 0;
		while (x < app->width)
		{
			xy[0] = x;
			xy[1] = y;
			render_pixel(&cam, scene, data, xy);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(app->mlx, app->win, app->img, 0, 0);
}
