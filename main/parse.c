/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stliu <stliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 15:32:22 by stliu             #+#    #+#             */
/*   Updated: 2026/03/26 14:14:06 by stliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
#include "../inc/rt_math.h"
#include "../inc/window.h"
#include <fcntl.h>

int	validate(int fd, t_scene *scene)
{
	char	*line;
	int		i;

	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		i = 0;
		while (ft_isspace(line[i]))
			i++;
		if (line[i] != '\0' && line[i] != '\n')
		{
			if (valid_ident(&line[i], scene))
				return (free(line), 1);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (scene->has_ambient != 1 || scene->has_camera != 1
		|| scene->nb_lights <= 0 || scene->nb_objects <= 0)
		return (1);
	return (0);
}
