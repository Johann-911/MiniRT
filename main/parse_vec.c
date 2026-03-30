/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stliu <stliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 15:32:22 by stliu             #+#    #+#             */
/*   Updated: 2026/03/26 14:14:06 by stliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
#include "../inc/rt_math.h"

int	parse_vec3_token(const char *token, t_vec3 *out)
{
	char	**parts;

	parts = ft_split(token, ',');
	if (!parts || token_count(parts) != 3)
		return (free_split(parts), 1);
	if (parse_double_strict(parts[0], &out->x)
		|| parse_double_strict(parts[1], &out->y)
		|| parse_double_strict(parts[2], &out->z))
		return (free_split(parts), 1);
	free_split(parts);
	return (0);
}

int	parse_rgb_token(const char *token, t_rgb *out)
{
	char	**parts;

	parts = ft_split(token, ',');
	if (!parts || token_count(parts) != 3)
		return (free_split(parts), 1);
	if (parse_int_strict(parts[0], &out->r)
		|| parse_int_strict(parts[1], &out->g)
		|| parse_int_strict(parts[2], &out->b))
		return (free_split(parts), 1);
	free_split(parts);
	if (out->r < 0 || out->r > 255 || out->g < 0
		|| out->g > 255 || out->b < 0 || out->b > 255)
		return (1);
	return (0);
}

int	parse_dir_token(const char *token, t_vec3 *out)
{
	if (parse_vec3_token(token, out))
		return (1);
	if (out->x < -1.0 || out->x > 1.0 || out->y < -1.0
		|| out->y > 1.0 || out->z < -1.0 || out->z > 1.0)
		return (1);
	if (vec3_len(*out) < 1e-9)
		return (1);
	*out = vec3_norm(*out);
	return (0);
}
