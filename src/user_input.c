/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 19:30:04 by ghalvors          #+#    #+#             */
/*   Updated: 2019/01/26 19:39:11 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	key_release(int keycode, void *param)
{
	t_window *win;

	win = (t_window*)param;
	if (keycode == 256)
		win->ctrl = 0;
	return (0);
}

int	key_press(int keycode, void *param)
{
	t_window *win;

	win = (t_window*)param;
	if (keycode == 123 || keycode == 124 || keycode == 125 || keycode == 126)
		move_map(keycode, win);
	if (keycode == 69 || keycode == 78)
		zoom_map(keycode, win);
	if (keycode == 53)
		close_win(param);
	if (keycode == 15)
		reset_map(win);
	if (keycode == 8)
		change_line_color(win);
	if (keycode == 11)
		change_background(win);
	if (keycode == 83 || keycode == 84 || keycode == 86 || keycode == 87 ||
		keycode == 89 || keycode == 91)
		set_rotation(keycode, win);
	if (keycode == 256)
		win->ctrl = 1;
	if (keycode == 82)
		win->auto_rotate = win->auto_rotate ? 0 : 1;
	if (keycode == 35)
		set_projection(win);
	return (0);
}

int	mouse_press(int button, int x, int y, void *param)
{
	(void)x;
	(void)y;
	if (button == 4 || button == 5)
		wheel_zoom(button, (t_window*)param);
	return (0);
}
