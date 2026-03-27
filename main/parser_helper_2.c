/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stliu <stliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 14:20:01 by stliu             #+#    #+#             */
/*   Updated: 2026/03/26 14:20:04 by stliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
#include "../inc/rt_math.h"
#include "../inc/window.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f')
		return (1);
	return (0);
}

int	parse_flags(char **tokens, int count, int base, t_object *obj)
{
	int	i;

	obj->checker = 0;
	obj->bump = 0;
	if (count == base)
		return (0);
	if (count != base + 2 && count != base + 4)
		return (1);
	i = base;
	while (i < count)
	{
		if (ft_strncmp(tokens[i], "cb", 2) == 0 && tokens[i][2] == '\0')
		{
			if (ft_strncmp(tokens[i + 1], "true", 4) != 0 || tokens[i
					+ 1][4] != '\0')
				return (1);
			obj->checker = 1;
		}
		else
			return (1);
		i = i + 2;
	}
	return (0);
}

double	ft_atod(const char *str)
{
	size_t	i;
	double	res;
	double	sign;
	double	div;

	i = 0;
	res = 0.0;
	sign = 1.0;
	div = 10.0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1.0;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10.0 + (double)(str[i] - '0');
		i++;
	}
	if (str[i] == '.')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res += (double)(str[i] - '0') / div;
		div *= 10.0;
		i++;
	}
	return (sign * res);
}
