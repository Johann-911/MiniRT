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
t_vec3 vec3_scale(t_vec3 v, double s)
{
    t_vec3  result;
    result.x = v.x * s;
    result.y = v.y * s;
    result.z = v.z * s;
    return (result);
}

bool    inter_sphere(t_ray ray, t_sphere *sphere, double *s)
{
    
}

bool    inter_plane(t_ray ray, t_plane *plane, double *s)
{
    
}

bool    inter_cylinder(t_ray ray, t_cylinder *cylinder, double *s)
{
    
}


t_vec3  norm_sphere(t_vec3 point, t_sphere *sphere)
{
    
}

t_vec3  norm_plane(t_plane *plane)
{
    
}

t_vec3  normal_cylinder(t_vec3 point, t_cylinder *cylinder)
{
    
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
double inter_cylinder(t_ray ray, t_cylinder cylinder)
{
    
}