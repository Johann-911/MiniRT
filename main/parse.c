/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stliu <stliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 15:32:22 by stliu             #+#    #+#             */
/*   Updated: 2026/03/17 17:37:44 by stliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/window.h"
#include "../inc/parser.h"
#include <fcntl.h>
#include "../inc/rt_math.h"


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

typedef struct s_cylinder
{
	t_vec3 center;
	t_vec3 vector;
	double radius;
	double height;
	t_rgb color;
}t_cylinder;

*/


void	append_object(t_scene *scene, t_object *new_obj)
{
    t_object	*cur;

    if (!scene->objects)
    {
        scene->objects = new_obj;
        return ;
    }
    cur = scene->objects;
    while (cur->next)
        cur = cur->next;
    cur->next = new_obj;
}

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

static int	parse_vec3_token(const char *token, t_vec3 *out)
{
    char	**parts;

    parts = ft_split(token, ',');
    if (!parts || token_count(parts) != 3)
    {
        free_split(parts);
        return (1);
    }
	out->x = ft_atod(parts[0]);
	out->y = ft_atod(parts[1]);
	out->z = ft_atod(parts[2]);
    free_split(parts);
    return (0);
}

static int	parse_rgb_token(const char *token, t_rgb *out)
{
    char	**parts;

    parts = ft_split(token, ',');
    if (!parts || token_count(parts) != 3)
    {
        free_split(parts);
        return (1);
    }
	out->r = ft_atoi(parts[0]);
	out->g = ft_atoi(parts[1]);
	out->b = ft_atoi(parts[2]);
    free_split(parts);
    if (out->r < 0 || out->r > 255 || out->g < 0 || out->g > 255
        || out->b < 0 || out->b > 255)
        return (1);
    return (0);
}

static int	parse_dir_token(const char *token, t_vec3 *out)
{
    if (parse_vec3_token(token, out))
        return (1);
    if (out->x < -1.0 || out->x > 1.0 || out->y < -1.0 || out->y > 1.0
        || out->z < -1.0 || out->z > 1.0)
        return (1);
    if (vec3_len(*out) < 1e-9)
        return (1);
    *out = vec3_norm(*out);
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
    if (ft_strncmp(ident, "co", 2) == 0 && ft_isspace(ident[2]))
        return (valid_cone(ident, scene));
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
	char	**tokens;

	tokens = split_tokens(line);
	if (!tokens || token_count(tokens) != 3 || scene->has_ambient)
		return (free_split(tokens), 1);
	scene->ambient.ratio = ft_atod(tokens[1]);
	if (scene->ambient.ratio < 0.0 || scene->ambient.ratio > 1.0
		|| parse_rgb_token(tokens[2], &scene->ambient.color))
		return (free_split(tokens), 1);
	scene->has_ambient = 1;
	free_split(tokens);
	return (0);
}

int valid_camera(char *line, t_scene *scene)
{
	char	**tokens;

	tokens = split_tokens(line);
	if (!tokens || token_count(tokens) != 4 || scene->has_camera)
		return (free_split(tokens), 1);
	scene->camera.fov = ft_atod(tokens[3]);
	if (parse_vec3_token(tokens[1], &scene->camera.origin)
		|| parse_dir_token(tokens[2], &scene->camera.vector)
		|| scene->camera.fov < 0.0 || scene->camera.fov > 180.0)
		return (free_split(tokens), 1);
	scene->has_camera = 1;
	free_split(tokens);
	return (0);
}

int valid_light(char *line, t_scene *scene)
{
	char	**tokens;
	t_light	*new_light;

	tokens = split_tokens(line);
	if (!tokens || token_count(tokens) != 4)
		return (free_split(tokens), 1);
	new_light = malloc(sizeof(t_light));
	if (!new_light)
		return (free_split(tokens), 1);
	new_light->next = NULL;
	new_light->b = ft_atod(tokens[2]);
	if (parse_vec3_token(tokens[1], &new_light->pos)
		|| new_light->b < 0.0 || new_light->b > 1.0
		|| parse_rgb_token(tokens[3], &new_light->color))
		return (free(new_light), free_split(tokens), 1);
	if (!scene->light)
		scene->light = new_light;
	else
	{
		t_light *cur = scene->light;
		while (cur->next)
			cur = cur->next;
		cur->next = new_light;
	}
	scene->nb_lights++;
	free_split(tokens);
	return (0);
}
int	parse_checker_flag(char **tokens, int count, int base, t_object *obj)
{
    int i;

    obj->checker = 0;
    if (count == base)
        return (0);
    if (count != base + 2)
        return (1);
    i = base;
    if (ft_strncmp(tokens[i], "cb", 2) != 0 || tokens[i][2] != '\0')
        return (1);
    i = base + 1;
    if (ft_strncmp(tokens[i], "true", 4) != 0 || tokens[i][4] != '\0')
        return (1);
    obj->checker = 1;
    return (0);
}

int valid_sphere(char *line, t_scene *scene)
{
    char		**tokens;
    t_object	*new;
    double		diameter;
    int			count;

    tokens = split_tokens(line);
    if (!tokens)
        return (1);
    count = token_count(tokens);
    new = malloc(sizeof(t_object));
    if (!new)
        return (free_split(tokens), 1);
    new->type = OBJ_SPHERE;
    new->next = NULL;
    if (parse_checker_flag(tokens, count, 4, new))
        return (free(new), free_split(tokens), 1);
    diameter = ft_atod(tokens[2]);
    if (parse_vec3_token(tokens[1], &new->data.sphere.center)
        || diameter <= 0.0
        || parse_rgb_token(tokens[3], &new->data.sphere.color))
        return (free(new), free_split(tokens), 1);
    new->data.sphere.r = diameter / 2.0;
    add_object(scene, new);
    scene->nb_objects++;
    free_split(tokens);
    return (0);
}

int valid_plane(char *line, t_scene *scene)
{
    char		**tokens;
    t_object	*new;
    int			count;

    tokens = split_tokens(line);
    if (!tokens)
        return (1);
    count = token_count(tokens);
    new = malloc(sizeof(t_object));
    if (!new)
        return (free_split(tokens), 1);
    new->type = OBJ_PLANE;
    new->next = NULL;
    if (parse_checker_flag(tokens, count, 4, new))
        return (free(new), free_split(tokens), 1);
    if (parse_vec3_token(tokens[1], &new->data.plane.point)
        || parse_dir_token(tokens[2], &new->data.plane.normal)
        || parse_rgb_token(tokens[3], &new->data.plane.color))
        return (free(new), free_split(tokens), 1);
    add_object(scene, new);
    scene->nb_objects++;
    free_split(tokens);
    return (0);
}

///stephan
int valid_cylinder(char *line, t_scene *scene)
{
    char		**tokens;
    t_object	*new;
    double		diameter;
    int			count;

    tokens = split_tokens(line);
    if (!tokens)
        return (1);
    count = token_count(tokens);
    new = malloc(sizeof(t_object));
    if (!new)
        return (free_split(tokens), 1);
    new->type = OBJ_CYLINDER;
    new->next = NULL;
    if (parse_checker_flag(tokens, count, 6, new))
        return (free(new), free_split(tokens), 1);
    diameter = ft_atod(tokens[3]);
    new->data.cylinder.height = ft_atod(tokens[4]);
    if (parse_vec3_token(tokens[1], &new->data.cylinder.center)
        || parse_dir_token(tokens[2], &new->data.cylinder.vector)
        || diameter <= 0.0
        || new->data.cylinder.height <= 0.0
        || parse_rgb_token(tokens[5], &new->data.cylinder.color))
        return (free(new), free_split(tokens), 1);
    new->data.cylinder.radius = diameter / 2.0;
    add_object(scene, new);
    scene->nb_objects++;
    free_split(tokens);
    return (0);
}
///stephan
int valid_cone(char *line, t_scene *scene)
{
    char		**tokens;
    t_object	*new;
    double		diameter;
    int			count;

    tokens = split_tokens(line);
    if (!tokens)
        return (1);
    count = token_count(tokens);
    new = malloc(sizeof(t_object));
    if (!new)
        return (free_split(tokens), 1);
    new->type = OBJ_CONE;
    new->next = NULL;
    if (parse_checker_flag(tokens, count, 6, new))
        return (free(new), free_split(tokens), 1);
    diameter = ft_atod(tokens[3]);
    new->data.cone.height = ft_atod(tokens[4]);
    if (parse_vec3_token(tokens[1], &new->data.cone.tip)
        || parse_dir_token(tokens[2], &new->data.cone.axis)
        || diameter <= 0.0
        || new->data.cone.height <= 0.0
        || parse_rgb_token(tokens[5], &new->data.cone.color))
        return (free(new), free_split(tokens), 1);
    new->data.cone.radius = diameter / 2.0;
    add_object(scene, new);
    scene->nb_objects++;
    free_split(tokens);
    return (0);
}




//mathe Janni
//grafik stjopka
