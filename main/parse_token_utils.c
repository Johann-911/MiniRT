/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stliu <stliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 00:00:00 by stliu             #+#    #+#             */
/*   Updated: 2026/03/30 17:45:31 by stliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	add_object(t_scene *scene, t_object *new_obj)
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

int	token_count(char **tokens)
{
	int	count;

	count = 0;
	if (!tokens)
		return (0);
	while (tokens[count])
		count++;
	return (count);
}
