/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 15:08:21 by ghalvors          #+#    #+#             */
/*   Updated: 2019/01/22 21:24:54 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <stdlib.h>
#include <math.h>

int	close_win(void *param)
{
		(void)param;
		exit(0);
		return(0);
}

void	move_map(int keycode, t_window *win)
{
	int	i;
	int	lines;

	lines = ((win->map_width - 1) * win->map_height) +
	(win->map_width * (win->map_height -1));
	i = -1;
	if (keycode == 123)
		while (++i < lines)
		{
			win->line[i].x1 -= 100;
			win->line[i].x2 -= 100;
		}
	if (keycode == 124)
		while (++i < lines)
		{
			win->line[i].x1 += 100;
			win->line[i].x2 += 100;
		}
	if (keycode == 125)
		while (++i < lines)
		{
			win->line[i].y1 += 100;
			win->line[i].y2 += 100;
		}
	if (keycode == 126)
		while (++i < lines)
		{
			win->line[i].y1 -= 100;
			win->line[i].y2 -= 100;
		}
	render(win);
}

void	zoom_map(int keycode, t_window *win)
{
	if (keycode == 69)
	{
		if (win->coef / 0.5 < 2147483647)
			win->coef /= 0.5;
	}
	else
		if (win->coef * 0.5 > 0.000001)
			win->coef *= 0.5;
	printf("%f\n", win->coef);
//	printf("Construct\n");
	if (win->line->x1 * win->coef < 2147483647)
	{
		construct_lines(win, win->points_map);
//	printf("Render\n");
		render(win);
//	printf("Complete\n");
	}
}


int	key_press(int keycode, void *param)
{
	if (keycode == 123 || keycode == 124 || keycode == 125 || keycode == 126)
		move_map(keycode, (t_window*)param);
	if (keycode == 69 || keycode == 78)
		zoom_map(keycode, (t_window*)param);
	if (keycode == 53)
			close_win(param);
	return (0);
}