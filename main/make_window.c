/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stliu <stliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 14:19:40 by stliu             #+#    #+#             */
/*   Updated: 2026/03/26 14:19:41 by stliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
#include "../inc/window.h"

void	put_pixel(char *data, int x, int y, int color, int bpp, int line)
{
	int	offset;

	offset = y * line + x * (bpp / 8);
	*(int *)(data + offset) = color;
}

int	handle_key(int keycode, void *param)
{
	(void)param;
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

int	handle_close(void *param)
{
	(void)param;
	exit(0);
	return (0);
}
