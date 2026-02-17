/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:19:35 by jtoumani          #+#    #+#             */
/*   Updated: 2025/03/28 16:06:22 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (i < len && haystack[i] != '\0')
	{
		j = 0;
		if (haystack[i] == needle[j])
		{
			while (haystack[i + j] == needle[j] && (i + j) < len)
			{
				j++;
				if (needle[j] == '\0')
					return ((char *)(haystack + i));
			}
		}
		i++;
	}
	return (NULL);
}
// int main()
// {
//     char str1 [] = "Hallo ich bin";
//     char str2 [] = "bin";
//     printf("%s", ft_strnstr(str1, str2, 13));
//     return (0);
// }
