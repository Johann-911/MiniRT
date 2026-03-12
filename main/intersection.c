/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephan <stephan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 14:43:39 by stliu             #+#    #+#             */
/*   Updated: 2026/03/11 12:12:13 by stephan          ###   ########.fr       */
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
    if (obj->type == OBJ_SPHERE)
        result->normal = norm_sphere(hit_point, &obj->data.sphere);
    else if (obj->type == OBJ_PLANE)
        result->normal = norm_plane(&obj->data.plane);
    else if (obj->type == OBJ_CYLINDER)
        result->normal = normal_cylinder(hit_point, &obj->data.cylinder);
    else if (obj->type == OBJ_CONE)
        result->normal = normal_cone(hit_point, &obj->data.cone);
}

void	set_color(t_hit *result, t_object *obj)
{
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
            set_color(&result, obj);
        }
        obj = obj->next;
    }
    return result;
}

double inter_sphere(t_ray ray, t_sphere sphere)
{
    t_vec3 dis;
    double  a;
    double  b;
    double  c;
    double disc;

    dis = vec3_sub(ray.origin, sphere.center);
    a = vec3_dot(ray.direction, ray.direction);
    b = 2 * vec3_dot(dis, ray.direction);
    c = vec3_dot(dis,dis) - sphere.r * sphere.r;
    return (discriminant(a, b, c));
}
//plane intersect is simpler than sphere, only needs linear solution
//denominator 0 means no hit, t < 0 plane is behind the ray
//            ray
//             \
//              \
//               \   t
//                \------X (intersection)
// ------------------------------
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
// 3 intersections: side, top and bottom cap
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
    double a, b, c, disc;
    double t, t_side, t_cap1, t_cap2;
    t_vec3 hit_point;
    double height_check;
    t_vec3 cap_top, cap_bottom;
    axis = vec3_norm(cylinder.vector);
    oc = vec3_sub(ray.origin, cylinder.center);
    proj_dir = vec3_sub(ray.direction, vec3_scale(axis, vec3_dot(ray.direction, axis)));
    proj_oc = vec3_sub(oc, vec3_scale(axis, vec3_dot(oc, axis)));
    a = vec3_dot(proj_dir, proj_dir);
    b = 2.0 * vec3_dot(proj_oc, proj_dir);
    c = vec3_dot(proj_oc, proj_oc) - (cylinder.radius * cylinder.radius);
    t_side = -1;
    disc = b * b - 4 * a * c;
    if (disc >= 0 && fabs(a) > 1e-6)
    {
        t = (-b - sqrt(disc)) / (2.0 * a);
        if (t > 0)
        {
            hit_point = vec3_add(ray.origin, vec3_scale(ray.direction, t));
            height_check = vec3_dot(vec3_sub(hit_point, cylinder.center), axis);
            if (height_check >= 0 && height_check <= cylinder.height)
                t_side = t;
        }
    }
    cap_bottom = cylinder.center;
    cap_top = vec3_add(cylinder.center, vec3_scale(axis, cylinder.height));
    t_cap1 = inter_cap(ray, cap_bottom, vec3_scale(axis, -1), cylinder.radius);
    t_cap2 = inter_cap(ray, cap_top, axis, cylinder.radius);
    return (min_pos(t_side, min_pos(t_cap1, t_cap2)));
}

double inter_cone(t_ray ray, t_cone cone)
{
    t_vec3 axis;
    t_vec3 oc;
    double k;
    double dot_dir_axis;
    double dot_oc_axis;
    double dot_dir_oc;
    double a, b, c, disc;
    double t, t1, t2;
    t_vec3 hit;
    double h;

    axis = vec3_norm(cone.vector);
    oc = vec3_sub(ray.origin, cone.center);
    k = (cone.radius / cone.height) * (cone.radius / cone.height);
    dot_dir_axis = vec3_dot(ray.direction, axis);
    dot_oc_axis = vec3_dot(oc, axis);
    dot_dir_oc = vec3_dot(ray.direction, oc);
    a = dot_dir_axis * dot_dir_axis - k * vec3_dot(ray.direction, ray.direction);
    b = 2.0 * (dot_dir_axis * dot_oc_axis - k * dot_dir_oc);
    c = dot_oc_axis * dot_oc_axis - k * vec3_dot(oc, oc);
    disc = b * b - 4 * a * c;
    if (disc < 0 || fabs(a) < 1e-6)
        return (-1);
    t1 = (-b - sqrt(disc)) / (2.0 * a);
    t2 = (-b + sqrt(disc)) / (2.0 * a);
    if (t1 > 0)
    {
        hit = vec3_add(ray.origin, vec3_scale(ray.direction, t1));
        h = vec3_dot(vec3_sub(hit, cone.center), axis);
        if (h >= 0 && h <= cone.height)
            return (t1);
    }
    if (t2 > 0)
    {
        hit = vec3_add(ray.origin, vec3_scale(ray.direction, t2));
        h = vec3_dot(vec3_sub(hit, cone.center), axis);
        if (h >= 0 && h <= cone.height)
            return (t2);
    }
    return (-1);
}