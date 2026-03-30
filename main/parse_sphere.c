/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stliu <stliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 15:32:22 by stliu             #+#    #+#             */
/*   Updated: 2026/03/26 14:14:06 by stliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
#include "../inc/rt_math.h"

int	valid_sphere(char *line, t_scene *scene)
{
	char		**tok;
	t_object	*new;
	double		diam;
	int			count;

	tok = split_tokens(line);
	if (!tok)
		return (1);
	count = token_count(tok);
	new = malloc(sizeof(t_object));
	if (!new)
		return (free_split(tok), 1);
	new->type = OBJ_SPHERE;
	new->next = NULL;
	if (parse_flags(tok, count, 4, new)
		|| parse_double_strict(tok[2], &diam)
		|| parse_vec3_token(tok[1], &new->data.sphere.center)
		|| diam <= 0.0
		|| parse_rgb_token(tok[3], &new->data.sphere.color))
		return (free(new), free_split(tok), 1);
	new->data.sphere.r = diam / 2.0;
	add_object(scene, new);
	scene->nb_objects++;
	free_split(tok);
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
	if (parse_flags(tokens, count, 4, new))
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
