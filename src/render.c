/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 19:01:55 by ghalvors          #+#    #+#             */
/*   Updated: 2019/01/26 19:48:15 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../Libft/libft.h"
#include "../minilibx/mlx.h"
#include <math.h>

void	set_intense(int *pixel, float intense, t_window *win)
{
	*pixel = ((int)((((win->color >> 16) & 0xff) * intense) + (((win->bg >> 16)
	& 0xff) * (1 - intense))) << 16) | ((int)((((win->color >> 8) & 0xff)
	* intense) + (((win->bg >> 8) & 0xff) * (1 - intense))) << 8) |
	(int)(((win->color & 0xff) * intense) + ((win->bg & 0xff) * (1 - intense)));
}

void	draw_straight(t_line *line, t_window *win)
{
	int		dx;
	int		dy;
	float	m;
	float	intery;
	int		xi;

	dx = line->x2 - line->x1;
	dy = line->y2 - line->y1;
	m = (float)dy / dx;
	xi = line->x1 > 0 ? line->x1 - 1 : -1;
	intery = line->x1 != xi + 1 ? line->y1 - m * line->x1 : line->y1;
	while (++xi <= line->x2 && xi < WIN_W)
	{
		if ((int)intery >= 0 && intery < WIN_H)
		{
			if (dx != 0)
				set_intense((int*)(win->data + xi + ((int)intery
				* win->pitch)), 1 - (intery - (int)intery), win);
			if (dy != 0 && (xi + (((int)intery + 1) * win->pitch)) <
				win->pitch * WIN_H)
				set_intense((int*)(win->data + xi + (((int)intery + 1)
				* win->pitch)), intery - (int)intery, win);
		}
		intery += m;
	}
}

void	draw_reverse(t_line *line, t_window *win)
{
	int		dx;
	int		dy;
	float	m;
	float	intery;
	int		xi;

	dx = line->x2 - line->x1;
	dy = line->y2 - line->y1;
	m = (float)dy / dx;
	xi = line->x1 > 0 ? line->x1 - 1 : -1;
	intery = line->x1 != xi + 1 ? line->y1 - m * line->x1 : line->y1;
	while (++xi <= line->x2 && xi < WIN_H)
	{
		if ((int)intery > 0 && intery < WIN_W)
		{
			if (dx != 0)
				set_intense((int*)(win->data + ((int)intery + xi
				* win->pitch)), 1 - (intery - (int)intery), win);
			if (dy != 0 && (int)intery + 1 < WIN_W && (((int)intery + 1) +
				xi * win->pitch) < win->pitch * WIN_H)
				set_intense((int*)(win->data + (((int)intery + 1) + xi
				* win->pitch)), intery - (int)intery, win);
		}
		intery += m;
	}
}

void	algorithm(t_window *win, t_line line)
{
	int	steep;

	line.x1 += win->move_x;
	line.x2 += win->move_x;
	line.y1 += win->move_y;
	line.y2 += win->move_y;
	steep = ABS(line.y2 - line.y1) > ABS(line.x2 - line.x1);
	if (steep)
	{
		ft_swap(&(line.x1), &(line.y1), sizeof(line.y1));
		ft_swap(&(line.x2), &(line.y2), sizeof(line.y2));
	}
	if (line.x1 > line.x2)
	{
		ft_swap(&(line.x1), &(line.x2), sizeof(line.y1));
		ft_swap(&(line.y1), &(line.y2), sizeof(line.y2));
	}
	if (steep)
		draw_reverse(&line, win);
	else
		draw_straight(&line, win);
}

int		render(t_window *win)
{
	int		i;
	int		lines;
	t_line	*line;

	i = -1;
	while (++i < WIN_H * win->pitch)
		win->data[i] = win->bg;
	lines = ((win->map_w - 1) * win->map_h) +
	(win->map_w * (win->map_h - 1));
	line = win->line;
	i = -1;
	while (++i < lines)
		algorithm(win, line[i]);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img, 0, 0);
	return (0);
}
