/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 19:39:53 by ghalvors          #+#    #+#             */
/*   Updated: 2019/01/26 19:51:22 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	set_rotation(int keycode, t_window *win)
{
	if (keycode == 83)
		win->rot_x += win->rot_speed;
	else if (keycode == 84)
		win->rot_x -= win->rot_speed;
	else if (keycode == 86)
		win->rot_y += win->rot_speed;
	else if (keycode == 87)
		win->rot_y -= win->rot_speed;
	else if (keycode == 89)
		win->rot_z += win->rot_speed;
	else
		win->rot_z -= win->rot_speed;
	construct_lines(win);
	render(win);
}

int		rotate_speed(int button, t_window *win)
{
	if (button == 4)
		if (win->rot_speed - 0.0174533 > 0.001)
			win->rot_speed -= 0.0174533;
	if (button == 5)
		if (win->rot_speed + 0.0174533 < 1.5708)
			win->rot_speed += 0.0174533;
	return (0);
}

int		auto_rotate(t_window *win)
{
	if (!win->auto_rotate)
		return (1);
	if (win->rot_z >= 6.28319)
		win->rot_z = 0;
	else
		win->rot_z += win->rot_speed;
	construct_lines(win);
	render(win);
	return (0);
}
