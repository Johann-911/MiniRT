/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stliu <stliu@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 19:52:54 by stliu             #+#    #+#             */
/*   Updated: 2026/03/25 21:59:40 by stliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/window.h"
#include "../inc/parser.h"
#include <fcntl.h>
#include "../inc/rt_math.h"

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

char	*cleanup_line(const char *line)
{
    char	*out;
    int		i;
    int		j;
    int		next;

    out = malloc(ft_strlen(line) + 1);
    if (!out)
        return (NULL);
    i = 0;
    j = 0;
    while (line[i])
    {
        if (ft_isspace(line[i]))
        {
            next = i;
            while (line[next] && ft_isspace(line[next]))
                next++;
            if ((j > 0 && out[j - 1] == ',') || line[next] == ',')
            {
                i = next;
                continue ;
            }
            if (j > 0 && out[j - 1] != ' ')
                out[j++] = ' ';
            i = next;
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
