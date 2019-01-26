/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 19:43:30 by ghalvors          #+#    #+#             */
/*   Updated: 2019/01/26 19:51:03 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	move_map(int keycode, t_window *win)
{
	int	i;
	int	lines;

	lines = ((win->map_w - 1) * win->map_h) +
	(win->map_w * (win->map_h - 1));
	i = -1;
	if (keycode == 123)
		win->move_x += 100;
	if (keycode == 124)
		win->move_x -= 100;
	if (keycode == 125)
		win->move_y -= 100;
	if (keycode == 126)
		win->move_y += 100;
	render(win);
}
