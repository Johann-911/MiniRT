/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:51:52 by jtoumani          #+#    #+#             */
/*   Updated: 2025/03/17 15:25:34 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		chr;
	unsigned const char	*str;
	size_t				i;

	chr = c;
	str = s;
	i = 0;
	while (i < n)
	{
		if (str[i] == chr)
		{
			return ((void *)(str + i));
		}
		s++;
		i++;
	}
	return (NULL);
}
// int main()
// {
// char *a;
// char *s = "Hallo";
// a = ft_memchr(s, '4', 6);
// printf("%s", a);
// return (0);
// }