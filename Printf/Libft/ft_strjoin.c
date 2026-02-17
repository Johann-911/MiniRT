/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:16:54 by jtoumani          #+#    #+#             */
/*   Updated: 2025/03/17 15:08:57 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*strjoin;
	int		i;
	int		j;

	i = 0;
	j = 0;
	strjoin = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (strjoin == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		strjoin[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		strjoin[j] = s2[i];
		i++;
		j++;
	}
	strjoin[j] = '\0';
	return (strjoin);
}
