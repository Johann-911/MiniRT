#include "../inc/parser.h"
#include "../inc/rt_math.h"
#include "../inc/window.h"

double	clamp01(double v)
{
	if (v < 0.0)
		return (0.0);
	if (v > 1.0)
		return (1.0);
	return (v);
}

t_vec3	color_from_rgb(t_rgb c)
{
	return (vec3(c.r / 255.0, c.g / 255.0, c.b / 255.0));
}
t_vec3	color_mul(t_vec3 a, t_vec3 b)
{
	return (vec3(a.x * b.x, a.y * b.y, a.z * b.z));
}

t_rgb	rgb_from_color(t_vec3 c)
{
	t_rgb	out;

	c.x = clamp01(c.x);
	c.y = clamp01(c.y);
	c.z = clamp01(c.z);
	out.r = (int)round(c.x * 255.0);
	out.g = (int)round(c.y * 255.0);
	out.b = (int)round(c.z * 255.0);
	return (out);
}

int	rgb_to_int_local(t_rgb c)
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
