/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stliu <stliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 14:19:31 by stliu             #+#    #+#             */
/*   Updated: 2026/03/26 14:19:33 by stliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
#include "../inc/window.h"
#include <fcntl.h>

int	render_loop(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	render_scene(app, app->scene);
	return (0);
}

static void	init_scene(t_scene *scene)
{
	scene->ambient.ratio = 0.0;
	scene->ambient.color.r = 0;
	scene->ambient.color.g = 0;
	scene->ambient.color.b = 0;
	scene->camera.origin = vec3(0, 0, 0);
	scene->camera.vector = vec3(0, 0, 1);
	scene->camera.fov = 60.0;
	scene->light = NULL;
	scene->objects = NULL;
	scene->nb_lights = 0;
	scene->nb_objects = 0;
	scene->has_ambient = 0;
	scene->has_camera = 0;
}

static int	init_app(t_app *app)
{
	app->mlx = mlx_init();
	if (!app->mlx)
		return (perror("mlx_init"), 1);
	app->win = mlx_new_window(app->mlx, app->width, app->height, "miniRT");
	if (!app->win)
		return (perror("mlx_new_window"), 1);
	app->img = mlx_new_image(app->mlx, app->width, app->height);
	if (!app->img)
		return (perror("mlx_new_image"), 1);
	return (0);
}

int	main(int ac, char **av)
{
	t_app	app;
	int		fd;
	t_scene	scene;

	if (ac != 2)
		return (perror("Wrong Usage. ./miniRT <input_file.rt>"), 1);
	fd = open(av[1], O_RDONLY);
	init_scene(&scene);
	if (validate(fd, &scene))
		return (close(fd), ft_printf("Invalid .rt file\n"), 1);
	close(fd);
	app.width = WIDTH;
	app.height = HEIGHT;
	if (init_app(&app))
		return (1);
	app.scene = &scene;
	render_scene(&app, &scene);
	mlx_hook(app.win, 2, 1L << 0, handle_key, &app);
	mlx_hook(app.win, 17, 0, handle_close, &app);
	mlx_loop(app.mlx);
	return (0);
}
