/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:29:58 by jtoumani          #+#    #+#             */
/*   Updated: 2025/04/01 13:42:02 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *s, int j)
{
	if (s == NULL)
	{
		if (write(1, "(null)", 6) == -1)
			return (-1);
		return (j + 6);
	}
	while (*s)
	{
		if (write(1, s, 1) == -1)
			return (-1);
		s++;
		j++;
	}
	return (j);
}

int	ft_putchar(char c, int j)
{
	if (write(1, &c, 1) == -1)
		return (-1);
	j++;
	return (j);
}

int	ft_putnbr(int n, int j)
{
	char	output;

	if (n == -2147483648)
	{
		j = ft_putstr("-2147483648", j);
		if (j == -1)
			return (-1);
		return (j);
	}
	if (n < 0)
	{
		if (write(1, "-", 1) == -1)
			return (-1);
		n = -n;
		j++;
	}
	if (n > 9)
		j = ft_putnbr(n / 10, j);
	if (j == -1)
		return (-1);
	output = (n % 10) + '0';
	if (write(1, &output, 1) == -1)
		return (-1);
	return (j + 1);
}

int	ft_puthexa(size_t n, int j, char format)
{
	char	*lowercase;
	char	*uppercase;

	lowercase = "0123456789abcdef";
	uppercase = "0123456789ABCDEF";
	if (n >= 16)
		j = ft_puthexa(n / 16, j, format);
	if (j == -1)
		return (-1);
	if (format == 'X')
		j = ft_putchar(uppercase[n % 16], j);
	if (j == -1)
		return (-1);
	if (format == 'x')
		j = ft_putchar(lowercase[n % 16], j);
	if (j == -1)
		return (-1);
	return (j);
}

int	ft_unsignednbr(unsigned int n, int j)
{
	char	output;

	if (n > 9)
		j = ft_unsignednbr(n / 10, j);
	if (j == -1)
		return (-1);
	output = (n % 10) + '0';
	if (write(1, &output, 1) == -1)
		return (-1);
	j++;
	return (j);
}
