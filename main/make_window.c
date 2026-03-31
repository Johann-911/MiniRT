/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stliu <stliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 14:19:40 by stliu             #+#    #+#             */
/*   Updated: 2026/03/31 15:37:09 by stliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
#include "../inc/window.h"

void	put_pixel(char *data, int x, int y, int color)
{
	int	offset;

	offset = y * WIDTH * 4 + x * 4;
	*(int *)(data + offset) = color;
}

int	handle_key(int keycode, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (keycode == KEY_ESC)
		close_app(app);
	return (0);
}

int	handle_close(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	close_app(app);
	return (0);
}
