#include "../inc/window.h"
#include "../inc/parser.h"

t_vec3	bump_gradient(t_vec3 p, double freq)
{
    t_vec3	g;

    g.x = cos(p.x * freq) * sin(p.z * freq);
    g.y = 0.0;
    g.z = sin(p.x * freq) * cos(p.z * freq);
    g = vec3_scale(g, 0.6);
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

t_vec3	apply_checker_bump(t_vec3 n, t_vec3 p)
{
    double	size;
    int		ix;
    int		iz;
    double	h;

    size = 8.0;
    ix = (int)floor(p.x / size);
    iz = (int)floor(p.z / size);
    if ((ix + iz) % 2 == 0)
        h = 0.05;
    else
        h = -0.05;
    n.x = n.x + h;
    n.y = n.y + h;
    n.z = n.z + h;
    return (vec3_norm(n));
}

int	parse_bump_flag(char **tokens, int count, int base, t_object *obj)
{
    int i;

    obj->bump = 0;
    if (count == base)
        return (0);
    if (count != base + 2)
        return (1);
    i = base;
    if (ft_strncmp(tokens[i], "bm", 2) != 0 || tokens[i][2] != '\0')
        return (1);
    i = base + 1;
    if (ft_strncmp(tokens[i], "true", 4) != 0 || tokens[i][4] != '\0')
        return (1);
    obj->bump = 1;
    return (0);
}
