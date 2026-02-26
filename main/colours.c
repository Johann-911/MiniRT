#include "../inc/rt_math.h"
#include <math.h>
#include <stdint.h>


int	clamp_int(int val, int lo, int hi)
{
	if (val < lo)
		return (lo);
	if (val > hi)
		return (hi);
	return (val);
}

int	rgb_to_int(int r, int g, int b)
{
	r = clamp_int(r, 0, 255);
	g = clamp_int(g, 0, 255);
	b = clamp_int(b, 0, 255);
	return ((r << 16) | (g << 8) | b);
}

t_rgb	int_to_rgb(int color)
{
	t_rgb c;
	c.r = (color >> 16) & 0xFF;
	c.g = (color >> 8) & 0xFF;
	c.b = color & 0xFF;
	return (c);
}

int	rgb_scale_int(int color, double factor)
{
	t_rgb c;
	int	r, g, b;

	if (factor < 0.0)
		factor = 0.0;
	if (factor > 1.0)
		factor = 1.0;
	c = int_to_rgb(color);
	r = (int)(c.r * factor);
	g = (int)(c.g * factor);
	b = (int)(c.b * factor);
	return (rgb_to_int(r, g, b));
}
