/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stliu <stliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 14:43:39 by stliu             #+#    #+#             */
/*   Updated: 2026/03/25 14:31:06 by stliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt_math.h"
#include "../inc/parser.h"

//  a · b = ax · bx + ay · by + az · bz

double	min_pos(double t1, double t2)
{
    if (t1 > 0 && t2 > 0)
        return (t1 < t2 ? t1 : t2);
    if (t1 > 0)
        return (t1);
    if (t2 > 0)
        return (t2);
    return (-1);
}

t_vec3  norm_sphere(t_vec3 point, t_sphere *sphere)
{
    return (vec3_norm(vec3_sub(point, sphere->center)));
}

t_vec3  norm_plane(t_plane *plane)
{
    return (vec3_norm(plane->normal));
}

t_vec3  normal_cylinder(t_vec3 point, t_cylinder *cylinder)
{
    t_vec3 axis;
    t_vec3 to_point;
    t_vec3 proj;
    t_vec3 radial;
    
    axis = vec3_norm(cylinder->vector);
    to_point = vec3_sub(point, cylinder->center);
    proj = vec3_scale(axis, vec3_dot(to_point, axis));
    radial = vec3_sub(to_point, proj);
    return vec3_norm(radial);
}

t_vec3 normal_cone(t_vec3 point, t_cone *cone)
{
    t_vec3 axis;
    t_vec3 to_point;
    t_vec3 radial;
    double proj_len;
    double k;

    axis = vec3_norm(cone->axis);
    to_point = vec3_sub(point, cone->tip);
    proj_len = vec3_dot(to_point, axis);
    radial = vec3_sub(to_point, vec3_scale(axis, proj_len));
    k = cone->radius / cone->height;
    return(vec3_norm(vec3_sub(radial, vec3_scale(axis, vec3_len(radial) * k))));

}

double discriminant(double a, double b, double c)
{
    double  discriminant;

    discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return (-1);
    return ((-b - sqrt(discriminant)) / ( 2 * a));
}
//needs the solution of quadratic function
//  Camera
//   |
//   | ray
//   v
// O ----------- t1 ---- (sphere) ---- t2

void	set_normal(t_hit *result, t_object *obj, t_vec3 hit_point)
{
    t_vec3	local_p;

    if (obj->type == OBJ_SPHERE)
    {
        result->normal = norm_sphere(hit_point, &obj->data.sphere);
        local_p = vec3_sub(hit_point, obj->data.sphere.center);
    }
    else if (obj->type == OBJ_PLANE)
    {
        result->normal = norm_plane(&obj->data.plane);
        local_p = hit_point;
    }
    else if (obj->type == OBJ_CYLINDER)
    {
        result->normal = normal_cylinder(hit_point, &obj->data.cylinder);
        local_p = vec3_sub(hit_point, obj->data.cylinder.center);
    }
    else
    {
        result->normal = normal_cone(hit_point, &obj->data.cone);
        local_p = vec3_sub(hit_point, obj->data.cone.tip);
    }
    if (obj->bump)
        result->normal = perturb_normal(result->normal, local_p, 0.08, 1.0);
}

static t_rgb	checker_planar(t_vec3 p)
{
    double	size;
    int		ix;
    int		iz;
    t_rgb	c;

    size = 10.0;
    ix = (int)floor(p.x / size);
    iz = (int)floor(p.z / size);
    if ((ix + iz) % 2 == 0)
    {
        c.r = 255;
        c.g = 255;
        c.b = 255;
        return (c);
    }
    c.r = 0;
    c.g = 0;
    c.b = 0;
    return (c);
}

static t_rgb	checker_sphere(t_vec3 n)
{
    double	u;
    double	v;
    int		iu;
    int		iv;
    t_rgb	c;
    
    u = 0.5 + atan2(n.z, n.x) / (2.0 * M_PI);
    v = 0.5 - asin(n.y) / M_PI;
    iu = (int)floor(u * 8.0);
    iv = (int)floor(v * 8.0);
    if ((iu + iv) % 2 == 0)
    {
        c.r = 255;
        c.g = 255;
        c.b = 255;
        return (c);
    }
    c.r = 0;
    c.g = 0;
    c.b = 0;
    return (c);
}

static t_rgb	checker_cylinder(t_vec3 p, t_cylinder *cy)
{
    t_vec3	axis;
    t_vec3	rel;
    t_vec3	proj;
    t_vec3	radial;
    double	theta;
    double	u;
    double	v;
    int		iu;
    int		iv;
    t_rgb	c;

    axis = vec3_norm(cy->vector);
    rel = vec3_sub(p, cy->center);
    proj = vec3_scale(axis, vec3_dot(rel, axis));
    radial = vec3_sub(rel, proj);
    theta = atan2(radial.z, radial.x);
    u = (theta + M_PI) / (2.0 * M_PI);
    v = (vec3_dot(rel, axis) / cy->height) + 0.5;
    iu = (int)floor(u * 10.0);
    iv = (int)floor(v * 10.0);
    if ((iu + iv) % 2 == 0)
    {
        c.r = 255;
        c.g = 255;
        c.b = 255;
        return (c);
    }
    c.r = 0;
    c.g = 0;
    c.b = 0;
    return (c);
}

static t_rgb	checker_cone(t_vec3 p, t_cone *co)
{
    t_vec3	axis;
    t_vec3	rel;
    t_vec3	proj;
    t_vec3	radial;
    double	theta;
    double	u;
    double	v;
    int		iu;
    int		iv;
    t_rgb	c;

    axis = vec3_norm(co->axis);
    rel = vec3_sub(p, co->tip);
    proj = vec3_scale(axis, vec3_dot(rel, axis));
    radial = vec3_sub(rel, proj);
    theta = atan2(radial.z, radial.x);
    u = (theta + M_PI) / (2.0 * M_PI);
    v = vec3_dot(rel, axis) / co->height;
    iu = (int)floor(u * 10.0);
    iv = (int)floor(v * 10.0);
    if ((iu + iv) % 2 == 0)
    {
        c.r = 255;
        c.g = 255;
        c.b = 255;
        return (c);
    }
    c.r = 0;
    c.g = 0;
    c.b = 0;
    return (c);
}


void	set_color(t_hit *result, t_object *obj, t_vec3 hit_point, t_vec3 normal)
{
    if (obj->checker)
    {
        if (obj->type == OBJ_SPHERE)
            result->color = checker_sphere(normal);
        else if (obj->type == OBJ_CYLINDER)
            result->color = checker_cylinder(hit_point, &obj->data.cylinder);
        else if (obj->type == OBJ_CONE)
            result->color = checker_cone(hit_point, &obj->data.cone);
        else
            result->color = checker_planar(hit_point);
        return ;
    }
    if (obj->type == OBJ_SPHERE)
        result->color = obj->data.sphere.color;
    else if (obj->type == OBJ_PLANE)
        result->color = obj->data.plane.color;
    else if (obj->type == OBJ_CYLINDER)
        result->color = obj->data.cylinder.color;
    else
        result->color = obj->data.cone.color;
}

double	get_dist(t_ray ray, t_object *obj)
{
    if (obj->type == OBJ_SPHERE)
        return (inter_sphere(ray, obj->data.sphere));
    if (obj->type == OBJ_PLANE)
        return (inter_plane(ray, obj->data.plane));
    if (obj->type == OBJ_CYLINDER)
        return (inter_cylinder(ray, obj->data.cylinder));
    if (obj->type == OBJ_CONE)
        return (inter_cone(ray, obj->data.cone));
    return (-1);
}

t_hit closest_hit(t_ray ray, t_scene * scene)
{
    t_hit result;
    t_object *obj;
    double dist;
    t_vec3 hit_point;

    result.hit = 0;
    result.t = -1;
    obj = scene->objects;
    while(obj)
    {
        dist = get_dist(ray, obj);
        if(dist > 0 && (!result.hit || dist < result.t))
        {
            result.t = dist;
            result.hit = 1;
            hit_point = vec3_add(ray.origin, vec3_scale(ray.direction, dist));
            result.point = hit_point;
            set_normal(&result, obj, hit_point);
            set_color(&result, obj, hit_point, result.normal);
        }
        obj = obj->next;
    }
    return result;
}

int	any_hit_before(t_ray ray, t_scene *scene, double max_t)
{
    t_object	*obj;
    double		dist;

    obj = scene->objects;
    while (obj)
    {
        dist = get_dist(ray, obj);
        if (dist > 1e-3 && dist < max_t)
            return (1);
        obj = obj->next;
    }
    return (0);
}



double inter_sphere(t_ray ray, t_sphere sphere)
{
    t_vec3  dis;
    double  a;
    double  b;
    double  c;
    double  disc;
    double  t1;
    double  t2;

    dis = vec3_sub(ray.origin, sphere.center);
    a = vec3_dot(ray.direction, ray.direction);
    b = 2.0 * vec3_dot(dis, ray.direction);
    c = vec3_dot(dis, dis) - sphere.r * sphere.r;
    disc = b * b - 4.0 * a * c;
    if (disc < 0.0 || fabs(a) < 1e-6)
        return (-1);
    t1 = (-b - sqrt(disc)) / (2.0 * a);
    t2 = (-b + sqrt(disc)) / (2.0 * a);
    return (min_pos(t1, t2));
}
/*plane intersect is simpler than sphere, only needs linear solution
//denominator 0 means no hit, t < 0 plane is behind the ray
//            ray
//             \
//              \
//               \   t
//                \------X (intersection)
// ------------------------------*/
double inter_plane(t_ray ray, t_plane plane)
{
    double denominator;
    double t;
    t_vec3 diff;

    denominator = vec3_dot(ray.direction, plane.normal);
    if (fabs(denominator) < 1e-6)
        return (-1);
    diff = vec3_sub(plane.point, ray.origin);
    t = vec3_dot(diff, plane.normal) / denominator;
    if (t < 0)
        return (-1);
    return (t);
}
/*     intersections: side, top and bottom cap    */ 
double	inter_cap(t_ray ray, t_vec3 cap_center, t_vec3 cap_norm, double radius)
{
    t_plane cap;
    t_vec3 hit;
    t_vec3 diff;
    double t;

    cap.point = cap_center;
    cap.normal = cap_norm;
    t = inter_plane(ray, cap);
    if(t < 0)
        return -1;
    hit = vec3_add(ray.origin, vec3_scale(ray.direction, t));
    diff = vec3_sub(hit, cap_center);
    if(vec3_len(diff) > radius)
        return -1;
    return t;
}

double inter_cylinder(t_ray ray, t_cylinder cylinder)
{
    t_vec3 axis;
    t_vec3 oc;
    t_vec3 proj_dir;
    t_vec3 proj_oc;
    double a;
    double b;
    double c;
    double disc;
    double t1;
    double t2;
    double t_side;
    double t_cap1;
    double t_cap2;
    t_vec3 hit_point;
    double height_check;
    t_vec3 cap_top;
    t_vec3 cap_bottom;

    axis = vec3_norm(cylinder.vector);
    oc = vec3_sub(ray.origin, cylinder.center);
    proj_dir = vec3_sub(ray.direction, vec3_scale(axis, vec3_dot(ray.direction, axis)));
    proj_oc = vec3_sub(oc, vec3_scale(axis, vec3_dot(oc, axis)));
    a = vec3_dot(proj_dir, proj_dir);
    b = 2.0 * vec3_dot(proj_oc, proj_dir);
    c = vec3_dot(proj_oc, proj_oc) - (cylinder.radius * cylinder.radius);
    t_side = -1;
    disc = b * b - 4.0 * a * c;
    if (disc >= 0.0 && fabs(a) > 1e-6)
    {
        t1 = (-b - sqrt(disc)) / (2.0 * a);
        t2 = (-b + sqrt(disc)) / (2.0 * a);

        if (t1 > 0.0)
        {
            hit_point = vec3_add(ray.origin, vec3_scale(ray.direction, t1));
            height_check = vec3_dot(vec3_sub(hit_point, cylinder.center), axis);
            if (fabs(height_check) <= cylinder.height / 2.0)
                t_side = t1;
        }
        if (t2 > 0.0)
        {
            hit_point = vec3_add(ray.origin, vec3_scale(ray.direction, t2));
            height_check = vec3_dot(vec3_sub(hit_point, cylinder.center), axis);
            if (fabs(height_check) <= cylinder.height / 2.0)
                t_side = min_pos(t_side, t2);
        }
    }
    cap_bottom = vec3_sub(cylinder.center, vec3_scale(axis, cylinder.height / 2.0));
    cap_top = vec3_add(cylinder.center, vec3_scale(axis, cylinder.height / 2.0));
    t_cap1 = inter_cap(ray, cap_bottom, vec3_scale(axis, -1.0), cylinder.radius);
    t_cap2 = inter_cap(ray, cap_top, axis, cylinder.radius);
    return (min_pos(t_side, min_pos(t_cap1, t_cap2)));
}

double inter_cone(t_ray ray, t_cone cone)
{
    t_vec3 axis;
    t_vec3 oc;
    t_vec3 base_center;
    double k;
    double dv;
    double ov;
    double dd;
    double od;
    double oo;
    double a;
    double b;
    double c;
    double disc;
    double t1;
    double t2;
    double t_side;
    double t_base;
    double h;

    axis = vec3_norm(cone.axis);
    oc = vec3_sub(ray.origin, cone.tip);

    k = cone.radius / cone.height;
    k = k * k;
    dv = vec3_dot(ray.direction, axis);
    ov = vec3_dot(oc, axis);
    dd = vec3_dot(ray.direction, ray.direction);
    od = vec3_dot(oc, ray.direction);
    oo = vec3_dot(oc, oc);

    a = (1.0 + k) * dv * dv - dd;
    b = 2.0 * ((1.0 + k) * dv * ov - od);
    c = (1.0 + k) * ov * ov - oo;
    t_side = -1.0;
    disc = b * b - 4.0 * a * c;
    if (disc >= 0.0 && fabs(a) > 1e-6)
    {
        t1 = (-b - sqrt(disc)) / (2.0 * a);
        t2 = (-b + sqrt(disc)) / (2.0 * a);
        if (t1 > 0.0)
        {
            h = ov + t1 * dv;
            if (h >= 0.0 && h <= cone.height)
                t_side = t1;
        }
        if (t2 > 0.0)
        {
            h = ov + t2 * dv;
            if (h >= 0.0 && h <= cone.height)
                t_side = min_pos(t_side, t2);
        }
    }
    base_center = vec3_add(cone.tip, vec3_scale(axis, cone.height));
    t_base = inter_cap(ray, base_center, axis, cone.radius);
    return (min_pos(t_side, t_base));
}
