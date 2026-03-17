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

static t_vec3	color_from_rgb(t_rgb c)
{
    return (vec3(c.r / 255.0, c.g / 255.0, c.b / 255.0));
}

static t_vec3	color_mul(t_vec3 a, t_vec3 b)
{
    return (vec3(a.x * b.x, a.y * b.y, a.z * b.z));
}

static t_rgb	rgb_from_color(t_vec3 c)
{
    t_rgb out;

    c.x = clamp01(c.x);
    c.y = clamp01(c.y);
    c.z = clamp01(c.z);
    out.r = (int)round(c.x * 255.0);
    out.g = (int)round(c.y * 255.0);
    out.b = (int)round(c.z * 255.0);
    return (out);
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

int shade_hit(t_scene *scene, t_hit hit, t_vec3 cam_pos)
{
    t_light *light;
    t_vec3 light_dir;
    t_vec3 view_dir;
    t_vec3 reflect_dir;
    double ndotl;
    double spec;
    t_vec3 out_color;
    t_vec3 obj_color;
    t_vec3 amb_color;
    t_vec3 light_color;
    double diffuse;
    double specular;

    obj_color = color_from_rgb(hit.color);
    amb_color = color_from_rgb(scene->ambient.color);
    out_color = vec3_scale(color_mul(obj_color, amb_color), scene->ambient.ratio);
    if (scene->ambient.ratio < 0.05)
        out_color = vec3_add(out_color, vec3_scale(obj_color, 0.05));
    view_dir = vec3_norm(vec3_sub(cam_pos, hit.point));
    light = scene->light;
    while (light)
    {
        if (!is_in_shadow(scene, hit, light))
        {
            light_dir = vec3_norm(vec3_sub(light->pos, hit.point));
            ndotl = vec3_dot(hit.normal, light_dir);
            if (ndotl > 0.0)
            {
                light_color = color_from_rgb(light->color);
                diffuse = ndotl * light->b * 0.7;
                out_color = vec3_add(out_color,
                        vec3_scale(color_mul(obj_color, light_color), diffuse));
                reflect_dir = vec3_sub(vec3_scale(hit.normal, 2.0 * ndotl), light_dir);
                reflect_dir = vec3_norm(reflect_dir);
                spec = vec3_dot(view_dir, reflect_dir);
                if (spec > 0.0)
				{
					specular = pow(spec, 32.0) * 0.25 * light->b;
					out_color = vec3_add(out_color, vec3_scale(light_color, specular));
				}
            }
        }
        light = light->next;
    }
    return (rgb_to_int_local(rgb_from_color(out_color)));
}

int	is_in_shadow(t_scene *scene, t_hit hit, t_light *light)
{
    t_ray	shadow_ray;
    t_hit	blocker;
    t_vec3	to_light;
    double	light_dist;

    to_light = vec3_sub(light->pos, hit.point);
    light_dist = vec3_len(to_light);
    shadow_ray.origin = vec3_add(hit.point, vec3_scale(hit.normal, 1e-3));
    shadow_ray.direction = vec3_norm(to_light);
    blocker = closest_hit(shadow_ray, scene);
    if (blocker.hit && blocker.t > 1e-3 && blocker.t < light_dist)
        return (1);
    return (0);
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
			if (hit.hit && vec3_dot(hit.normal, ray.direction) > 0.0)
    			hit.normal = vec3_scale(hit.normal, -1.0);
            color = 0x101020;
            if (hit.hit)
                color = shade_hit(scene, hit, scene->camera.origin);
            put_pixel(data, x, y, color, bpp, line);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(app->mlx, app->win, app->img, 0
}