#ifndef WINDOW_H
#define WINDOW_H


#include <stdlib.h>
#include <stdio.h>
#include "../minilibx-linux/mlx.h"
#include <X11/Xlib.h>


typedef struct s_app 
{
    void *mlx;
    void *win;
    void *img;
    int width;
    int height;
}	t_app;

# define HEIGHT 1000
# define WIDTH 1200
#define KEY_ESC 65307

void	put_pixel(char *data, int x, int y, int color, int bpp, int line);
void	fill_gradient(t_app *app);
int	handle_key(int keycode, void *param);
int	handle_mouse(int button, int x, int y, void *param);
int	handle_close(void *param);
void recreate_image_and_draw(t_app *app);

#endif
