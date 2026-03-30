/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_id.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stliu <stliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 15:32:22 by stliu             #+#    #+#             */
/*   Updated: 2026/03/26 14:14:06 by stliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
#include "../inc/rt_math.h"

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
