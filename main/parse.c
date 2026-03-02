/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stliu <stliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 15:32:22 by stliu             #+#    #+#             */
/*   Updated: 2026/02/26 15:40:58 by stliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/window.h"
#include "../inc/parser.h"
#include <fcntl.h>


/*
Ambient lighting: 
- Identifier: A 
- light ratio : 0.1-1.0
- RGB: 0 - 255
*/

/*
Camera:
- Identifier: C
- coords x,y,z 
- vector : -1 - 1
- FOV: 0 - 180
*/

/*
Light:
- Identifier: L
- coords x,y,z
- brightness: 0 - 1.0
- RBG: 0 - 255
*/

/*
Sphere:
- Ident: sp
- coords x,y,z
- sphere diameter
- RBG: 255
*/

/*
Plane:
- Ident pl
- coords x,y,z
- 3D vector: - 1 - 1
- RGB: 255
*/

/*
Cylinder:
- Ident: cy
- coords x,y,z
- 3D vector: -1 - 1
- cylinder diamter
- cylinder height
- RBG: 255
*/

/*
Format of the input:
A  0.2 255,255,255
C -50,0,20 0,0,1 70
L -40,0,30 0.7 255,255,255
pl 0,0,0 0,1.0,0 255,0,225
sp 0,0,20 20 255,0,0
cy 50.0,0.0,20.6 0,0,1.0 14.2 21.42 10,0,255


*/

int validate(int fd, t_scene *scene)
{
    char    *line;

    if (fd < 0)
        return (1);
    line = get_next_line(fd);
    while (line != NULL)
    {
        if(check_line(line, scene))
        {
            free(line);
            return 1;
        }
        free(line);
        line = get_next_line(fd);
    }
    return (0);
}

int ft_isspace(char c)
{
    if (c == ' ' || c == '\t')
        return (1);
    return (0);
}
int valid_ident(char *ident, t_scene *scene)
{
    if (!ident)
        return (1);
    if (ft_strncmp(ident, "A", 1) == 0 && ft_isspace(ident[1]))
        return (valid_ambient(ident, scene));
    if (ft_strncmp(ident, "C", 1) == 0 && ft_isspace(ident[1]))
        return (valid_camera(ident, scene));
    if (ft_strncmp(ident, "L", 1) == 0 && ft_isspace(ident[1]))
        return (valid_light(ident, scene));
    if (ft_strncmp(ident, "sp", 2) == 0 && ft_isspace(ident[2]))
        return (valid_sphere(ident, scene));
    if (ft_strncmp(ident, "pl", 2) == 0 && ft_isspace(ident[2]))
        return (valid_plane(ident, scene));
    if (ft_strncmp(ident, "cy", 2) == 0 && ft_isspace(ident[2]))
        return (valid_cylinder(ident, scene));
    return (1);
}

int check_line(char *line, t_scene *scene)
{
    int i;

    i = 0;
    while (ft_isspace(line[i]))
        i++;
    if (line[i] == '\0' || line[i] == '\n')
        return (0);
    return (valid_ident(&line[i], scene));
}

int valid_ambient(char *line, t_scene *scene)
{
    int i;
    
    i = 1;
    while (ft_isspace(line[i]))
        i++;
    scene->ambient.ratio = ft_atod(&line[i]);
    while (line[i] && !ft_isspace(line[i]))
        i++;
    while (ft_isspace(line[i]))
        i++;
    scene->ambient.color.r = ft_atoi(&line[i]);
    while (line[i] && line[i] != ',')
        i++;
    if (line[i] == ',')
        i++;
    scene->ambient.color.g = ft_atoi(&line[i]);
    while (line[i] && line[i] != ',')
        i++;
    if (line[i] == ',')
        i++;
    scene->ambient.color.b = ft_atoi(&line[i]);
    return (0);
}

int valid_camera(char *line, t_scene *scene)
{
    
}

int valid_light(char *line, t_scene *scene)
{
    
}

int valid_sphere(char *line, t_scene *scene)
{
    
}

int valid_plane(char *line, t_scene *scene)
{
    
}
int valid_cylinder(char *line, t_scene *scene)
{
    
}
int valid_cone(char *line, t_scene *scene)
{
    
}