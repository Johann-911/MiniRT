/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stliu <stliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 15:32:22 by stliu             #+#    #+#             */
/*   Updated: 2026/03/19 00:00:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/window.h"
#include "../inc/parser.h"
#include <fcntl.h>
#include "../inc/rt_math.h"

int	validate(int fd, t_scene *scene)
{
	char	*line;

	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (check_line(line, scene))
		{
			free(line);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (scene->has_ambient != 1 || scene->has_camera != 1
		|| scene->nb_lights <= 0 || scene->nb_objects <= 0)
		return (1);
	return (0);
}

static int	is_valid_double_token(const char *s)
{
	int	i;
	int	has_digit;
	int	has_dot;

	if (!s)
		return (0);
	i = 0;
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '+' || s[i] == '-')
		i++;
	has_digit = 0;
	has_dot = 0;
	while (s[i])
	{
		if (ft_isdigit((unsigned char)s[i]))
			has_digit = 1;
		else if (s[i] == '.' && has_dot == 0)
			has_dot = 1;
		else if (ft_isspace(s[i]))
		{
			while (ft_isspace(s[i]))
				i++;
			return (s[i] == '\0' && has_digit);
		}
		else
			return (0);
		i++;
	}
	return (has_digit);
}

static int	is_valid_int_token(const char *s)
{
	int	i;
	int	has_digit;

	if (!s)
		return (0);
	i = 0;
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '+' || s[i] == '-')
		i++;
	has_digit = 0;
	while (s[i])
	{
		if (ft_isdigit((unsigned char)s[i]))
			has_digit = 1;
		else if (ft_isspace(s[i]))
		{
			while (ft_isspace(s[i]))
				i++;
			return (s[i] == '\0' && has_digit);
		}
		else
			return (0);
		i++;
	}
	return (has_digit);
}

static int	parse_double_strict(const char *s, double *out)
{
	if (!out || !is_valid_double_token(s))
		return (1);
	*out = ft_atod(s);
	return (0);
}

static int	parse_int_strict(const char *s, int *out)
{
	long	val;
	int		sign;
	int		i;

	if (!out || !is_valid_int_token(s))
		return (1);
	i = 0;
	while (ft_isspace(s[i]))
		i++;
	sign = 1;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	val = 0;
	while (ft_isdigit((unsigned char)s[i]))
	{
		val = val * 10 + (s[i] - '0');
		if ((sign == 1 && val > 2147483647L)
			|| (sign == -1 && -val < -2147483648L))
			return (1);
		i++;
	}
	*out = (int)(val * sign);
	return (0);
}

static int	parse_vec3_token(const char *token, t_vec3 *out)
{
	char	**parts;

	parts = ft_split(token, ',');
	if (!parts || token_count(parts) != 3)
		return (free_split(parts), 1);
	if (parse_double_strict(parts[0], &out->x)
		|| parse_double_strict(parts[1], &out->y)
		|| parse_double_strict(parts[2], &out->z))
		return (free_split(parts), 1);
	free_split(parts);
	return (0);
}

static int	parse_rgb_token(const char *token, t_rgb *out)
{
	char	**parts;

	parts = ft_split(token, ',');
	if (!parts || token_count(parts) != 3)
		return (free_split(parts), 1);
	if (parse_int_strict(parts[0], &out->r)
		|| parse_int_strict(parts[1], &out->g)
		|| parse_int_strict(parts[2], &out->b))
		return (free_split(parts), 1);
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

int	valid_ident(char *ident, t_scene *scene)
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

int	check_line(char *line, t_scene *scene)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (0);
	return (valid_ident(&line[i], scene));
}

int	valid_ambient(char *line, t_scene *scene)
{
	char	**tokens;

	tokens = split_tokens(line);
	if (!tokens || token_count(tokens) != 3 || scene->has_ambient)
		return (free_split(tokens), 1);
	if (parse_double_strict(tokens[1], &scene->ambient.ratio)
		|| scene->ambient.ratio < 0.0 || scene->ambient.ratio > 1.0
		|| parse_rgb_token(tokens[2], &scene->ambient.color))
		return (free_split(tokens), 1);
	scene->has_ambient = 1;
	free_split(tokens);
	return (0);
}

int	valid_camera(char *line, t_scene *scene)
{
	char	**tokens;

	tokens = split_tokens(line);
	if (!tokens || token_count(tokens) != 4 || scene->has_camera)
		return (free_split(tokens), 1);
	if (parse_double_strict(tokens[3], &scene->camera.fov)
		|| parse_vec3_token(tokens[1], &scene->camera.origin)
		|| parse_dir_token(tokens[2], &scene->camera.vector)
		|| scene->camera.fov < 0.0 || scene->camera.fov > 180.0)
		return (free_split(tokens), 1);
	scene->has_camera = 1;
	free_split(tokens);
	return (0);
}

int	valid_light(char *line, t_scene *scene)
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
	if (parse_double_strict(tokens[2], &new_light->b)
		|| parse_vec3_token(tokens[1], &new_light->pos)
		|| new_light->b < 0.0 || new_light->b > 1.0
		|| parse_rgb_token(tokens[3], &new_light->color))
		return (free(new_light), free_split(tokens), 1);
	if (!scene->light)
		scene->light = new_light;
	else
	{
		t_light	*cur;

		cur = scene->light;
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
	int	i;

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

int	valid_sphere(char *line, t_scene *scene)
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
	if (parse_double_strict(tokens[2], &diameter)
		|| parse_vec3_token(tokens[1], &new->data.sphere.center)
		|| diameter <= 0.0
		|| parse_rgb_token(tokens[3], &new->data.sphere.color))
		return (free(new), free_split(tokens), 1);
	new->data.sphere.r = diameter / 2.0;
	add_object(scene, new);
	scene->nb_objects++;
	free_split(tokens);
	return (0);
}

int	valid_plane(char *line, t_scene *scene)
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

int	valid_cylinder(char *line, t_scene *scene)
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
	if (parse_double_strict(tokens[3], &diameter)
		|| parse_double_strict(tokens[4], &new->data.cylinder.height)
		|| parse_vec3_token(tokens[1], &new->data.cylinder.center)
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

int	valid_cone(char *line, t_scene *scene)
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
	if (parse_double_strict(tokens[3], &diameter)
		|| parse_double_strict(tokens[4], &new->data.cone.height)
		|| parse_vec3_token(tokens[1], &new->data.cone.tip)
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
