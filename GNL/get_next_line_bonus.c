/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:28:52 by jtoumani          #+#    #+#             */
/*   Updated: 2025/04/23 18:39:35 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	update_buffer(char *buffer)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
	{
		i++;
		while (buffer[i])
			buffer[j++] = buffer[i++];
	}
	while (j <= BUFFER_SIZE)
		buffer[j++] = '\0';
}

int	build_line(char **line, char *buffer)
{
	char	*temp;
	int		i;

	i = 0;
	temp = ft_strjoin(*line, buffer);
	free(*line);
	if (temp == NULL)
		return (-1);
	*line = temp;
	if (*line == NULL)
		return (-1);
	while ((*line)[i] != '\0')
	{
		if ((*line)[i] == '\n')
		{
			if ((*line)[i + 1] != '\0')
				(*line)[i + 1] = '\0';
			return (1);
		}
		i++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	buffer[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*line;
	int			bytes_read;
	int			ready;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
		return (buffer[fd][0] = '0' NULL);
	while (1)
	{
		if (buffer[fd][0] == '\0')
		{
			bytes_read = read(fd, buffer[fd], BUFFER_SIZE);
			if (bytes_read == -1)
				return (free(line), NULL);
			if (bytes_read == 0)
				return (line);
		}
		ready = build_line(&line, buffer[fd]);
		update_buffer(buffer[fd]);
		if (ready == 1)
			return (line);
		if (ready == -1)
			return (NULL);
	}
}
