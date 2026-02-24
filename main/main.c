#include "../inc/window.h"

void	put_pixel(char *data, int x, int y, int color, int bpp, int line)
{
	int	offset;

	offset = y * line + x * (bpp / 8);
	*(int *)(data + offset) = color;
}

void	draw_image(t_app *app)
{
	int		x;
	int		y;
	int		bpp;
	int		line;
	int		endian;
	char	*data;
	int r;
	int g;
	int b;
	int color;

	data = mlx_get_data_addr(app->img, &bpp, &line, &endian);
	y = 0;
	while (y < app->height)
	{
		x = 0;
		while (x < app->width)
		{
			r = (x * 255) / app->width;
			g = (y * 255) / app->height;
			b = 128;
			color = (r << 16) | (g << 8) | b;
			put_pixel(data, x, y, color, bpp, line);
			x++;
		}
		y++;
	}
}

void	fill_gradient(t_app *app)
{
	int		bpp;
	int		line;
	int		endian;
	char	*data;
	int		r;
	int		g;
	int		b;
	int		color;

	int x, y;
	data = mlx_get_data_addr(app->img, &bpp, &line, &endian);
	y = 0;
	while (y < app->height)
	{
		x = 0;
		while (x < app->width)
		{
			r = (x * 255) / app->width;
			g = (y * 255) / app->height;
			b = 128;
			color = (r << 16) | (g << 8) | b;
			put_pixel(data, x, y, color, bpp, line);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(app->mlx, app->win, app->img, 0, 0);
}

int	handle_key(int keycode, void *param)
{
	(void)param;
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

int	handle_close(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

int	main(void)
{
	t_app app;

	app.width = WIDTH;
	app.height = HEIGHT;
	app.mlx = mlx_init();
	if (!app.mlx)
	{
		perror("mlx_init");
		return (1);
	}
	app.win = mlx_new_window(app.mlx, app.width, app.height, "miniRT-MLX test");
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
	fill_gradient(&app);
	mlx_hook(app.win, 2, 1L << 0, handle_key, &app);
	mlx_hook(app.win, 17, 0, handle_close, &app);
	mlx_loop(app.mlx);
	return (0);
}
