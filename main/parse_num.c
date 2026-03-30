/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stliu <stliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 15:32:22 by stliu             #+#    #+#             */
/*   Updated: 2026/03/26 14:14:06 by stliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
#include "../inc/rt_math.h"

static int	is_valid_double_token(const char *s)
{
	int	i;
	int	hd;
	int	hd2;

	i = 0;
	hd = 0;
	hd2 = 0;
	if (!s)
		return (0);
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (ft_isdigit((unsigned char)s[i]))
			hd = 1;
		else if (s[i] == '.' && hd2 == 0)
			hd2 = 1;
		else if (ft_isspace(s[i]))
		{
			while (ft_isspace(s[++i]))
				;
			return (s[i] == '\0' && hd);
		}
		else
			return (0);
		i++;
	}
	return (hd);
}

static int	is_valid_int_token(const char *s)
{
	int	i;
	int	hd;

	i = 0;
	hd = 0;
	if (!s)
		return (0);
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i] && (ft_isdigit((unsigned char)s[i])
			|| ft_isspace(s[i])))
	{
		if (ft_isdigit((unsigned char)s[i]))
			hd = 1;
		else if (hd)
		{
			while (ft_isspace(s[++i]))
				;
			return (s[i] == '\0' && hd);
		}
		else
			return (0);
		i++;
	}
	return (s[i] == '\0' && hd);
}

int	parse_double_strict(const char *s, double *out)
{
	if (!out || !is_valid_double_token(s))
		return (1);
	*out = ft_atod(s);
	return (0);
}

int	parse_int_strict(const char *s, int *out)
{
	long	val;
	int		sign;
	int		i;

	if (!out || !is_valid_int_token(s))
		return (1);
	i = 0;
	while (ft_isspace(s[i]))
		i++;
	sign = 1;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	val = 0;
	while (ft_isdigit((unsigned char)s[i]))
	{
		val = val * 10 + (s[i] - '0');
		if ((sign == 1 && val > 2147483647L)
			|| (sign == -1 && (-val) < -2147483648L))
			return (1);
		i++;
	}
	*out = (int)(val * sign);
	return (0);
}
