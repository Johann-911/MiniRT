/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:36:18 by jtoumani          #+#    #+#             */
/*   Updated: 2025/03/21 18:10:42 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		substr = (char *)malloc(sizeof(char) * (1));
		if (substr == NULL)
			return (NULL);
		*substr = '\0';
		return (substr);
	}
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (substr == NULL)
		return (NULL);
	while (s[i] != '\0' && i < len)
		substr[i++] = s[start++];
	substr[i] = '\0';
	return (substr);
}
// int main ()
// {
//     char *substr;
//     char str[] = "Macs sind scheise";
//     substr = ft_substr(str, 4, 5);
//     printf("%s", substr);
//     return (0);
// }