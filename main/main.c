#include "../inc/window.h"
#include "../inc/parser.h"
#include <fcntl.h>
#include <sys/time.h>

static long	current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

int	render_loop(void *param)
{
	t_app		*app;
	static long	last_sample = 0;
	static int	frames = 0;
	static double	fps = 0.0;
	long		now;
	char		fps_text[32];

	app = (t_app *)param;
	now = current_time_ms();
	if (last_sample == 0)
		last_sample = now;
	frames++;
	if (now - last_sample >= 1000)
	{
		fps = (double)frames * 1000.0 / (double)(now - last_sample);
		frames = 0;
		last_sample = now;
	}
	render_scene(app, app->scene);
	snprintf(fps_text, sizeof(fps_text), "FPS: %.1f", fps);
	mlx_string_put(app->mlx, app->win, 12, 22, 0x000000, fps_text);
	mlx_string_put(app->mlx, app->win, 10, 20, 0x00FFFFFF, fps_text);
	return (0);
}

int	main(int ac, char **av)
{
	t_app app;
	int fd;
	t_scene scene;

	if (ac != 2)
		return (perror("Wrong Usage. ./miniRT <input_file.rt>"), 1);
	fd = open(av[1], O_RDONLY);
	scene.ambient.ratio = 0.0;
	scene.ambient.color.r = 0;
	scene.ambient.color.g = 0;
	scene.ambient.color.b = 0;
	scene.camera.origin = vec3(0, 0, 0);
	scene.camera.vector = vec3(0, 0, 1);
	scene.camera.fov = 60.0;
	scene.light = NULL;
	scene.objects = NULL;
	scene.nb_lights = 0;
	scene.nb_objects = 0;
	scene.has_ambient = 0;
	scene.has_camera = 0;
	if (validate(fd, &scene))
		return (close(fd), ft_printf("Invalid .rt file\n"), 1);
	close(fd);
	app.width = WIDTH;
	app.height = HEIGHT;
	app.mlx = mlx_init();
	if (!app.mlx)
	{
		perror("mlx_init");
		return (1);
	}
	app.win = mlx_new_window(app.mlx, app.width, app.height, "miniRT");
	if (!app.win)
	{
		perror("mlx_new_window");
		return (1);
	}
	app.img = mlx_new_image(app.mlx, app.width, app.height);
	if (!app.img)
	{
		perror("mlx_new_image");
		return (1);
	}
	app.scene = &scene;
	render_scene(&app, &scene);
	
	mlx_hook(app.win, 2, 1L << 0, handle_key, &app);
	mlx_hook(app.win, 17, 0, handle_close, &app);
	mlx_loop(app.mlx);
	return (0);
}
