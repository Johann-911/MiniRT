/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:56:29 by jtoumani          #+#    #+#             */
/*   Updated: 2025/03/20 15:48:08 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dupe;
	int		i;

	i = 0;
	while (s1[i])
		i++;
	dupe = (char *)malloc(i + 1 * sizeof(char));
	if (dupe == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		dupe[i] = s1[i];
		i++;
	}
	dupe[i] = '\0';
	return (dupe);
}
