/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coefficients.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 18:38:10 by ghalvors          #+#    #+#             */
/*   Updated: 2019/01/26 19:26:30 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <math.h>

void	set_coef(t_window *win)
{
	int	max_z;
	int	off_xy;
	int	max_val;
	int	screen_min;

	win->zoom = 1;
	win->move_x = 0;
	win->move_y = 0;
	win->off_x = 0;
	win->off_y = 0;
	win->rot_x = 0;
	win->rot_y = 0;
	win->rot_z = 0;
	win->rot_speed = 0.0174533;
	max_z = ABS(win->min_h) + win->max_h;
	off_xy = win->map_h > win->map_w ? win->map_h :
	win->map_w;
	max_val = max_z > off_xy ? max_z : off_xy;
	screen_min = WIN_H <= WIN_W ? WIN_H : WIN_W;
	if (max_val >= screen_min)
		win->coef = (max_val / screen_min) * 0.6;
	else
		win->coef = (screen_min / max_val) * 0.6;
}

void	rotate_x(t_point *cur, float angle)
{
	int	prev_y;
	int	prev_z;

	prev_y = cur->y;
	prev_z = cur->z;
	cur->y = prev_y * cos(angle) + prev_z * sin(angle);
	cur->z = -prev_y * sin(angle) + prev_z * cos(angle);
}

void	rotate_y(t_point *cur, float angle)
{
	int	prev_x;
	int	prev_z;

	prev_x = cur->x;
	prev_z = cur->z;
	cur->x = prev_x * cos(angle) + prev_z * sin(angle);
	cur->z = -prev_x * sin(angle) + prev_z * cos(angle);
}

void	rotate_z(t_point *cur, float angle)
{
	int	prev_x;
	int	prev_y;

	prev_x = cur->x;
	prev_y = cur->y;
	cur->x = prev_x * cos(angle) - prev_y * sin(angle);
	cur->y = prev_x * sin(angle) + prev_y * cos(angle);
}

void	apply_coef(t_window *win)
{
	int i;
	int	map_size;

	i = -1;
	map_size = win->map_w * win->map_h;
	while (++i < map_size)
	{
		win->cur_map[i].x = win->init_map[i].x * win->coef;
		win->cur_map[i].y = win->init_map[i].y * win->coef;
		win->cur_map[i].z = win->init_map[i].z * win->coef;
		rotate_x(&(win->cur_map[i]), win->rot_x);
		rotate_y(&(win->cur_map[i]), win->rot_y);
		rotate_z(&(win->cur_map[i]), win->rot_z);
	}
}
