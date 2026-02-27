/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:18:25 by jtoumani          #+#    #+#             */
/*   Updated: 2025/06/04 19:22:20 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	int	a;

	a = 0;
	if (str == NULL)
		return (0);
	while (str[a] != '\0')
	{
		if (str[a] == '\n')
			return (a + 1);
		a++;
	}
	return (a);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*strjoin;
	int		i;
	int		j;

	i = 0;
	j = 0;
	strjoin = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (strjoin == NULL)
		return (NULL);
	while (s1 != NULL && s1[i] != '\0')
		strjoin[j++] = s1[i++];
	i = 0;
	while (s2[i])
	{
		strjoin[j] = s2[i];
		j++;
		i++;
		if (strjoin[j - 1] == '\n')
			break ;
	}
	strjoin[j] = '\0';
	return (strjoin);
}
