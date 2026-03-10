/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stliu <stliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 14:43:39 by stliu             #+#    #+#             */
/*   Updated: 2026/03/04 15:22:06 by stliu            ###   ########.fr       */
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

t_hit closets_hit(t_ray ray, t_scene *scene)
{
    t_hit hit;
    t_object *obj;
    double t;
    t_vec3 pt;

    hit.hit = 0;
    hit.t = -1;
    obj = scene->objects;
    while(obj)
    {




        
    }



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


    
}
// inter cylinder echt ein scheis 