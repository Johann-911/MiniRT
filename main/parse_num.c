/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stliu <stliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 15:32:22 by stliu             #+#    #+#             */
/*   Updated: 2026/03/30 17:51:16 by stliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
#include "../inc/rt_math.h"

static int	end_ok(const char *s, int i, int has_digit)
{
	while (ft_isspace(s[i]))
		i++;
	return (s[i] == '\0' && has_digit);
}

static int	is_valid_double_token(const char *s)
{
	int	i;
	int	has_digit;
	int	has_dot;

	i = 0;
	has_digit = 0;
	has_dot = 0;
	if (!s)
		return (0);
	while (ft_isspace(s[i]))
		i++;
	i += (s[i] == '+' || s[i] == '-');
	while (s[i] && !ft_isspace(s[i]))
	{
		if (ft_isdigit((unsigned char)s[i]))
			has_digit = 1;
		else if (s[i] == '.' && !has_dot)
			has_dot = 1;
		else
			return (0);
		i++;
	}
	return (end_ok(s, i, has_digit));
}

static int	is_valid_int_token(const char *s)
{
	int	i;
	int	has_digit;

	i = 0;
	has_digit = 0;
	if (!s)
		return (0);
	while (ft_isspace(s[i]))
		i++;
	i += (s[i] == '+' || s[i] == '-');
	while (s[i] && !ft_isspace(s[i]))
	{
		if (!ft_isdigit((unsigned char)s[i]))
			return (0);
		has_digit = 1;
		i++;
	}
	return (end_ok(s, i, has_digit));
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
		sign = (s[i++] == '-') * -2 + 1;
	val = 0;
	while (ft_isdigit((unsigned char)s[i]))
	{
		val = val * 10 + (s[i++] - '0');
		if ((sign == 1 && val > 2147483647L)
			|| (sign == -1 && val > 2147483648L))
			return (1);
	}
	*out = (int)(val * sign);
	return (0);
}
