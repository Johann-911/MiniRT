#include "../inc/window.h"
#include "../inc/parser.h"

t_vec3	bump_gradient(t_vec3 p, double freq)
{
    t_vec3	g;
    double	sx;
    double	sy;
    double	sz;
    double	cx;
    double	cy;
    double	cz;

    sx = sin(freq * p.x);
    sy = sin(freq * p.y);
    sz = sin(freq * p.z);
    cx = cos(freq * p.x);
    cy = cos(freq * p.y);
    cz = cos(freq * p.z);
    g.x = freq * cx * sy * sz;
    g.y = freq * sx * cy * sz;
    g.z = freq * sx * sy * cz;
    return (g);
}

t_vec3	perturb_normal(t_vec3 base_n, t_vec3 p_local, double stren, double freq)
{
    t_vec3	n;
    t_vec3	g;
    t_vec3	g_tangent;
    double	proj;

    n = vec3_norm(base_n);
    g = bump_gradient(p_local, freq);
    proj = vec3_dot(g, n);
    g_tangent = vec3_sub(g, vec3_scale(n, proj));
    n = vec3_sub(n, vec3_scale(g_tangent, stren));
    return (vec3_norm(n));
}