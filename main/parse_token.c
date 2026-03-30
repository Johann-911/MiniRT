/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stliu <stliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 19:52:54 by stliu             #+#    #+#             */
/*   Updated: 2026/03/30 17:48:21 by stliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

static void	skip_spaces(const char *s, int *i)
{
	while (s[(*i)] && ft_isspace(s[*i]))
		(*i)++;
}

static int	should_insert_space(const char *out, int j, char next)
{
	if (!j)
		return (0);
	if (out[j - 1] == ' ' || out[j - 1] == ',')
		return (0);
	if (!next || next == ',')
		return (0);
	return (1);
}

static char	*finish_cleanup(char *out, int j)
{
	if (j && out[j - 1] == ' ')
		j--;
	out[j] = '\0';
	return (out);
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
			if (should_insert_space(out, j, line[i]))
				out[j++] = ' ';
			continue ;
		}
		if (line[i] == ',' && j && out[j - 1] == ' ')
			j--;
		out[j++] = line[i++];
	}
	return (finish_cleanup(out, j));
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
