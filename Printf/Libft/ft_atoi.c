/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:56:09 by jtoumani          #+#    #+#             */
/*   Updated: 2025/05/23 12:00:40 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	size_t	i;
	int		integer;
	int		sign;

	i = 0;
	integer = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * (-1);
		i++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		integer = (integer * 10) + (str[i] - '0');
		i++;
	}
	i++;
	return (sign * integer);
}

// int	main(void)
// {
// 	int i;
// 	char str[] = "+134443a523";
// 	i = ft_atoi(str);
// 	printf("%d", i);
// 	return (0);
// }