/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:14:17 by jtoumani          #+#    #+#             */
/*   Updated: 2025/04/01 13:42:16 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	format_check(char c, va_list args, int len)
{
	if (c == 'c')
		len = ft_putchar(va_arg(args, int), len);
	else if (c == 's')
		len = ft_putstr(va_arg(args, char *), len);
	else if (c == 'p')
	{
		len = ft_putchar('0', len);
		if (len == -1)
			return (-1);
		len = ft_putchar('x', len);
		if (len == -1)
			return (-1);
		len = ft_puthexa(va_arg(args, size_t), len, 'x');
	}
	else if (c == 'd' || c == 'i')
		len = ft_putnbr(va_arg(args, int), len);
	else if (c == 'u')
		len = ft_unsignednbr(va_arg(args, int), len);
	else if (c == 'x' || c == 'X')
		len = ft_puthexa(va_arg(args, unsigned int), len, c);
	else if (c == '%')
		len = ft_putchar('%', len);
	return (len);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		j;
	va_list	args;

	i = 0;
	j = 0;
	va_start(args, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			j = format_check(str[i], args, j);
		}
		else
		{
			j = ft_putchar(str[i], j);
		}
		if (j == -1)
			return (-1);
		i++;
	}
	va_end(args);
	return (j);
}
