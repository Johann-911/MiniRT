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

int validate(int fd)
{
    char    *line;

    if (fd < 0)
        return (0);
    line = get_next_line(fd);
    while (line != NULL)
    {
        printf("%s", line);
        free(line);
        line = get_next_line(fd);
    }
    return (1);
}

int ft_isspace(char c)
{
    if (c == ' ' || c == '\t')
        return (1);
    return (0);
}

int valid_ident(char *ident)
{
    if (!ident)
        return (0);
    if (ft_strncmp(ident, "A", 2) == 0)
        return (1);
    if (ft_strncmp(ident, "C", 2) == 0)
        return (1);
    if (ft_strncmp(ident, "L", 2) == 0)
        return (1);
    if (ft_strncmp(ident, "sp", 3) == 0)
        return (1);
    if (ft_strncmp(ident, "pl", 3) == 0)
        return (1);
    if (ft_strncmp(ident, "cy", 3) == 0)
        return (1);
    if (ft_strncmp(ident, "co", 3) == 0)
        return (1);
    if (ft_strncmp(ident, "tr", 3) == 0)
        return (1);
    return (0);
}

int check_line(char *line)
{
    int i = 0;
    while(line[i] != '\n')
    {
        if (ft_isspace(line[i]))
            i++;
        if (valid_ident(line[i]))
            return (1);
        else if (valid_ident(line[i]))
            return 0;
        i++;  
    }
    return 0;
}

int valid_ambient(char *line)
{
    
}

int valid_camera(char *line)
{
    
}

int valid_light(char *line)
{
    
}

int valid_sphere(char *line)
{
    
}

int valid_plane(char *line)
{
    
}
int valid_cylinder(char *line)
{
    
}
int valid_cone(char *line)
{
    
}