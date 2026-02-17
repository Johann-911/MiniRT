/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:04:08 by jtoumani          #+#    #+#             */
/*   Updated: 2025/03/20 12:45:17 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	chr;
	char			*before;

	chr = c;
	before = NULL;
	while (*s)
	{
		if (*s == chr)
		{
			before = (char *)s;
		}
		s++;
	}
	if (chr == '\0')
		return ((char *)s);
	return (before);
}

// int main()
// {
//     char *a;
//     char *s = "Hallo";
//     a = ft_strrchr(s, 'k');
//     printf("%s", a);
//     return (0);
// }