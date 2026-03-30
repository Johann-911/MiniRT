/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stliu <stliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 19:52:54 by stliu             #+#    #+#             */
/*   Updated: 2026/03/26 14:14:01 by stliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
#include "../inc/rt_math.h"
#include "../inc/window.h"
#include <fcntl.h>

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

static void	skip_spaces(const char *s, int *i)
{
	while (s[++(*i)] && ft_isspace(s[*i]))
		;
}

char	*cleanup_line(const char *line)
{
	char	*out;
	int		i;
	int		j;

	out = malloc(ft_strlen(line) + 1);
	if (!out)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
		{
			skip_spaces(line, &i);
			if ((j > 0 && out[j - 1] == ',') || line[i] == ',')
				continue ;
			if (j > 0 && out[j - 1] != ' ')
				out[j++] = ' ';
			continue ;
		}
		out[j++] = line[i++];
	}
	if (j > 0 && out[j - 1] == ' ')
		j--;
	out[j] = '\0';
	return (out);
}

char	**split_tokens(const char *line)
{
	char	*clean;
	char	**tokens;

	clean = cleanup_line(line);
	if (!clean)
		return (NULL);
	tokens = ft_split(clean, ' ');
	free(clean);
	return (tokens);
}
