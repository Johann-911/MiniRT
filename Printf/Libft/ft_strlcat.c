/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:36:06 by jtoumani          #+#    #+#             */
/*   Updated: 2025/03/17 15:09:02 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t dstsize)
{
	size_t	a;
	size_t	b;

	a = 0;
	b = 0;
	while (dest[a] != '\0' && a < dstsize)
	{
		a++;
	}
	if (a == dstsize)
		return (dstsize + ft_strlen(src));
	while (src[b] != '\0' && a < dstsize - 1)
	{
		dest[a] = src[b];
		a++;
		b++;
	}
	dest[a] = '\0';
	return (a + ft_strlen(&src[b]));
}
// int main()
// {
//     size_t a;
//     char src[] = "welcome  ";
//     char dest[] = "to 42 ";
//     a = ft_strlcat(dest, src, 15);
//     printf("%s", dest);
//     return (0);
// }