#ifndef WINDOW_H
#define WINDOW_H


#include <stdlib.h>
#include <stdio.h>
#include "../minilibx-linux/mlx.h"
#include <X11/Xlib.h>
#include "../Printf/ft_printf.h"
#include "rt_math.h"


typedef struct s_app 
{
    void *mlx;
    void *win;
    void *img;
    int width;
    int height;
    t_scene *scene;
}	t_app;

# define HEIGHT 1000
# define WIDTH 1200
#define KEY_ESC 65307

void	put_pixel(char *data, int x, int y, int color, int bpp, int line);
int	handle_key(int keycode, void *param);
int	handle_mouse(int button, int x, int y, void *param);
int	handle_close(void *param);
int	render_loop(void *param);
void recreate_image_and_draw(t_app *app);

double clamp01(double v);
int  rgb_to_int_local(t_rgb c);
t_rgb	checker_color_at(t_vec3 p);
int	parse_checker_flag(char **tokens, int count, int base, t_object *obj);
t_vec3	camera_right(t_vec3 forward);
t_ray	generate_ray(t_scene *scene, t_app *app, int x, int y);
int     shade_hit(t_scene *scene, t_hit hit, t_vec3 cam_pos);;
void	render_scene(t_app *app, t_scene *scene);
int     is_in_shadow(t_scene *scene, t_hit hit, t_light *light);


#endif 
