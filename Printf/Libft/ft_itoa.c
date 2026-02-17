/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:05:21 by jtoumani          #+#    #+#             */
/*   Updated: 2025/03/20 15:48:41 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	numm_length(int n)
{
	int			i;
	long long	nb;

	nb = n;
	i = 1;
	if (nb < 0)
	{
		i++;
		nb = -nb;
	}
	while (nb > 9)
	{
		nb = (nb / 10);
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int			length;
	char		*str;
	long long	nb;

	nb = n;
	length = numm_length(n);
	str = (char *)malloc(sizeof(char) * (length + 1));
	if (str == NULL)
		return (NULL);
	str[length] = '\0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	while (nb > 9)
	{
		str[--length] = (nb % 10) + '0';
		nb = nb / 10;
	}
	str[--length] = (nb % 10) + '0';
	return (str);
}
