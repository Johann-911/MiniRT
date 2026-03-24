/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stliu <stliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 19:52:54 by stliu             #+#    #+#             */
/*   Updated: 2026/03/16 20:12:16 by stliu            ###   ########.fr       */
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

int ft_isspace(char c)
{
    if (c == ' ' || c == '\t' || c == '\n'
        || c == '\r' || c == '\v' || c == '\f')
        return (1);
    return (0);
}

int	parse_flags(char **tokens, int count, int base, t_object *obj)
{
    int i;

    obj->checker = 0;
    obj->bump = 0;
    if (count == base)
        return (0);
    if (count != base + 2 && count != base + 4)
        return (1);
    i = base;
    while (i < count)
    {
        if (ft_strncmp(tokens[i], "cb", 2) == 0 && tokens[i][2] == '\0')
        {
            if (ft_strncmp(tokens[i + 1], "true", 4) != 0
                || tokens[i + 1][4] != '\0')
                return (1);
            obj->checker = 1;
        }
        else if (ft_strncmp(tokens[i], "bm", 2) == 0 && tokens[i][2] == '\0')
        {
            if (ft_strncmp(tokens[i + 1], "true", 4) != 0
                || tokens[i + 1][4] != '\0')
                return (1);
            obj->bump = 1;
        }
        else
            return (1);
        i = i + 2;
    }
    return (0);
}