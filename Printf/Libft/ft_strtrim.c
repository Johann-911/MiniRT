/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:23:45 by jtoumani          #+#    #+#             */
/*   Updated: 2025/03/31 12:25:57 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, char const *set)
{
	size_t	i;
	size_t	length;

	if (s1 == NULL)
		return (NULL);
	length = ft_strlen(s1);
	i = 0;
	while (s1[i] != '\0' && ft_strrchr(set, s1[i]) != NULL)
		i++;
	while (length > i && ft_strrchr(set, s1[length - 1]) != NULL)
		length--;
	return (ft_substr(s1, i, length - i));
}
