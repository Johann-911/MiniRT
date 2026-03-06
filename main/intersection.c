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
