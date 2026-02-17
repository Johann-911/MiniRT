/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:01:55 by jtoumani          #+#    #+#             */
/*   Updated: 2025/03/17 15:08:45 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int x, size_t n)
{
	size_t			i;
	unsigned char	*y;

	i = 0;
	y = (unsigned char *)ptr;
	while (i < n)
	{
		y[i] = (unsigned char)x;
		i++;
	}
	return (ptr);
}
// int main()
// {
//     char str[] = "";
//     ft_memset(str, 'a', 4);
//     printf("%s", str);
//     return (0);
// }