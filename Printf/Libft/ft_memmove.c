/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:30:19 by jtoumani          #+#    #+#             */
/*   Updated: 2025/03/20 15:46:39 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (len == 0 || dst == src)
		return (dst);
	if (dst < src)
	{
		while (i < len)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	else
	{
		i = len;
		while (i > 0)
		{
			i--;
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		}
	}
	return (dst);
}

// int main() {
//     char src[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
//     char dst[5];

//     // Test der ft_memmove Funktion
//     ft_memmove(dst, src,5 * sizeof(int));

//     // Ausgabe des Ergebnisses
//     printf("Destination: %s", dst);

//     return (0);
// }
