/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:30:00 by jtoumani          #+#    #+#             */
/*   Updated: 2025/03/17 15:09:05 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] != '\0' && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
// int main()
// {
//     int  a;
//     char src[] = "Hallo welt";
//     char dest[] = "wie geht es euch ";
//     size_t i = 6;
//     a = ft_strlcpy(dest, src, i);
//     // strlcpy(dest, src, i);
//     printf("%s\n", dest);
//     printf("%d", a);
//     return (0);
// }