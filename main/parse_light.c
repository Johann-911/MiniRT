/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stliu <stliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 15:32:22 by stliu             #+#    #+#             */
/*   Updated: 2026/03/26 14:14:06 by stliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
#include "../inc/rt_math.h"

static void	append_light(t_scene *scene, t_light *light)
{
	t_light	*cur;

	if (!scene->light)
		scene->light = light;
	else
	{
		cur = scene->light;
		while (cur->next)
			cur = cur->next;
		cur->next = light;
	}
	scene->nb_lights++;
}

int	valid_light(char *line, t_scene *scene)
{
	char	**tokens;
	t_light	*nl;

	tokens = split_tokens(line);
	if (!tokens || token_count(tokens) != 4)
		return (free_split(tokens), 1);
	nl = malloc(sizeof(t_light));
	if (!nl)
		return (free_split(tokens), 1);
	nl->next = NULL;
	if (parse_double_strict(tokens[2], &nl->b)
		|| parse_vec3_token(tokens[1], &nl->pos) || nl->b < 0.0
		|| nl->b > 1.0 || parse_rgb_token(tokens[3], &nl->color))
		return (free(nl), free_split(tokens), 1);
	append_light(scene, nl);
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
