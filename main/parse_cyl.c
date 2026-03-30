/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cyl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stliu <stliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 15:32:22 by stliu             #+#    #+#             */
/*   Updated: 2026/03/26 14:14:06 by stliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
#include "../inc/rt_math.h"

static int	valid_cyl_attrs(char **tok, t_object *new)
{
	double	diameter;

	if (parse_double_strict(tok[3], &diameter)
		|| parse_double_strict(tok[4], &new->data.cylinder.height)
		|| parse_vec3_token(tok[1], &new->data.cylinder.center)
		|| parse_dir_token(tok[2], &new->data.cylinder.vector)
		|| diameter <= 0.0 || new->data.cylinder.height <= 0.0
		|| parse_rgb_token(tok[5], &new->data.cylinder.color))
		return (1);
	new->data.cylinder.radius = diameter / 2.0;
	return (0);
}

int	valid_cylinder(char *line, t_scene *scene)
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
	new->type = OBJ_CYLINDER;
	new->next = NULL;
	if (parse_flags(tokens, count, 6, new)
		|| valid_cyl_attrs(tokens, new))
		return (free(new), free_split(tokens), 1);
	add_object(scene, new);
	scene->nb_objects++;
	free_split(tokens);
	return (0);
}

static int	valid_cone_attrs(char **tok, t_object *new)
{
	double	diameter;

	if (parse_double_strict(tok[3], &diameter)
		|| parse_double_strict(tok[4], &new->data.cone.height)
		|| parse_vec3_token(tok[1], &new->data.cone.tip)
		|| parse_dir_token(tok[2], &new->data.cone.axis)
		|| diameter <= 0.0 || new->data.cone.height <= 0.0
		|| parse_rgb_token(tok[5], &new->data.cone.color))
		return (1);
	new->data.cone.radius = diameter / 2.0;
	return (0);
}

int	valid_cone(char *line, t_scene *scene)
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
	new->type = OBJ_CONE;
	new->next = NULL;
	if (parse_flags(tokens, count, 6, new)
		|| valid_cone_attrs(tokens, new))
		return (free(new), free_split(tokens), 1);
	add_object(scene, new);
	scene->nb_objects++;
	free_split(tokens);
	return (0);
}
