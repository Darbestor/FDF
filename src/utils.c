/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 15:08:21 by ghalvors          #+#    #+#             */
/*   Updated: 2019/01/26 19:57:26 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <stdlib.h>

int		close_win(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

void	get_max_min_xy(t_window *win)
{
	int		i;
	int		lines;

	i = -1;
	lines = ((win->map_w - 1) * win->map_h) + (win->map_w * (win->map_h - 1));
	while (++i < lines)
	{
		if (win->line[i].x1 < win->min_x)
			win->min_x = win->line[i].x1;
		else if (win->line[i].x2 < win->min_x)
			win->min_x = win->line[i].x2;
		if (win->line[i].x1 > win->off_x)
			win->off_x = win->line[i].x1;
		else if (win->line[i].x2 > win->off_x)
			win->off_x = win->line[i].x2;
		if (win->line[i].y1 < win->min_y)
			win->min_y = win->line[i].y1;
		else if (win->line[i].y2 < win->min_y)
			win->min_y = win->line[i].y2;
		if (win->line[i].y1 > win->off_y)
			win->off_y = win->line[i].y1;
		else if (win->line[i].y2 > win->off_y)
			win->off_y = win->line[i].y2;
	}
}

void	set_center(t_window *win)
{
	int		i;
	int		lines;

	i = -1;
	lines = ((win->map_w - 1) * win->map_h) + (win->map_w * (win->map_h - 1));
	win->min_x = win->line->x1;
	win->off_x = win->line->x2;
	win->min_y = win->line->y1;
	win->off_y = win->line->y2;
	get_max_min_xy(win);
	win->off_y = -(win->min_y - (WIN_H - (win->off_y - win->min_y)) / 2);
	win->off_x = -(win->min_x - (WIN_W - (win->off_x - win->min_x)) / 2);
	i = -1;
	while (++i < lines)
	{
		win->line[i].y1 += win->off_y;
		win->line[i].y2 += win->off_y;
		win->line[i].x1 += win->off_x;
		win->line[i].x2 += win->off_x;
	}
}

void	set_projection(t_window *win)
{
	win->proj = win->proj ? 0 : 1;
	construct_lines(win);
	render(win);
}

void	reset_map(t_window *win)
{
	set_coef(win);
	construct_lines(win);
	set_center(win);
	render(win);
}
