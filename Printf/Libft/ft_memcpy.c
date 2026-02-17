/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:15:24 by jtoumani          #+#    #+#             */
/*   Updated: 2025/03/17 14:18:48 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*srce;

	i = 0;
	dest = dst;
	srce = src;
	if (dest == srce)
		return (NULL);
	while (i < n)
	{
		dest[i] = srce[i];
		i++;
	}
	return (dest);
}

// int		main(void)
// {
// 	void	*mem;

// 	if (!(mem = malloc(sizeof(*mem) * 30)))
// 		return (0);
// 	memset(mem, 'j', 30);
//     ft_memcpy(mem, "zyxwvutsrqponmlkjihgfedcba", 14);
// 	return (0);
// }
