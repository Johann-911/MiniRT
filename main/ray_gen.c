#include "../inc/rt_math.h"
#include "../inc/parser.h"
#include "../inc/window.h"

 double clamp01(double v)
 {
	if(v < 0.0)
		return 0.0;
	if(v > 1.0)
		return 1.0;
	return v;
}

int  rgb_to_int_local(t_rgb c)
{
    int	r;
    int	g;
    int	b;

    r = c.r;
    g = c.g;
    b = c.b;
    if (r < 0)
        r = 0;
    if (g < 0)
        g = 0;
    if (b < 0)
        b = 0;
    if (r > 255)
        r = 255;
    if (g > 255)
        g = 255;
    if (b > 255)
        b = 255;
    return ((r << 16) | (g << 8) | b);
}

t_vec3	camera_right(t_vec3 forward)
{
    t_vec3	up;

    up = vec3(0.0, 1.0, 0.0);
    if (fabs(vec3_dot(forward, up)) > 0.999)
        up = vec3(1.0, 0.0, 0.0);
    return (vec3_norm(vec3_cross(forward, up)));
}

t_ray	generate_ray(t_scene *scene, t_app *app, int x, int y)
{
    t_ray	ray;
    t_vec3	forward;
    t_vec3	right;
    t_vec3	up;
    double	aspect;
    double	fov_scale;
    double	px;
    double	py;
    double	pi;

    pi = acos(-1.0);
    forward = vec3_norm(scene->camera.vector);
    right = camera_right(forward);
    up = vec3_norm(vec3_cross(right, forward));
    aspect = (double)app->width / (double)app->height;
    fov_scale = tan((scene->camera.fov * 0.5) * (pi / 180.0));
    px = (2.0 * ((x + 0.5) / (double)app->width) - 1.0) * aspect * fov_scale;
    py = (1.0 - 2.0 * ((y + 0.5) / (double)app->height)) * fov_scale;
    ray.origin = scene->camera.origin;
    ray.direction = vec3_norm(vec3_add(forward,
                vec3_add(vec3_scale(right, px), vec3_scale(up, py))));
    return (ray);
}

int	shade_hit(t_scene *scene, t_hit hit)
{
    t_light	*light;
    t_vec3	light_dir;
    double	n_dot_l;
    double	intensity;
    t_rgb	c;

    intensity = scene->ambient.ratio;
    light = scene->light;
    while (light)
    {
        if (!is_in_shadow(scene, hit, light))
        {
            light_dir = vec3_norm(vec3_sub(light->pos, hit.point));
            n_dot_l = vec3_dot(hit.normal, light_dir);
            if (n_dot_l > 0.0)
                intensity += n_dot_l * light->b;
        }
        light = light->next;
    }
    intensity = clamp01(intensity);
    c.r = (int)(hit.color.r * intensity);
    c.g = (int)(hit.color.g * intensity);
    c.b = (int)(hit.color.b * intensity);
    return (rgb_to_int_local(c));
}

void	render_scene(t_app *app, t_scene *scene)
{
    int		x;
    int		y;
    int		bpp;
    int		line;
    int		endian;
    char	*data;
    t_ray	ray;
    t_hit	hit;
    int		color;

    data = mlx_get_data_addr(app->img, &bpp, &line, &endian);
    y = 0;
    while (y < app->height)
    {
        x = 0;
        while (x < app->width)
        {
            ray = generate_ray(scene, app, x, y);
            hit = closest_hit(ray, scene);
            color = 0x101020;
            if (hit.hit)
                color = shade_hit(scene, hit);
            put_pixel(data, x, y, color, bpp, line);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(app->mlx, app->win, app->img, 0, 0);
}