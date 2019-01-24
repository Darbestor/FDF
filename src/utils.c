/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 15:08:21 by ghalvors          #+#    #+#             */
/*   Updated: 2019/01/24 16:52:49 by ghalvors         ###   ########.fr       */
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
		win->move_x += 100;
	if (keycode == 124)
		win->move_x -= 100;
	if (keycode == 125)
		win->move_y -= 100;
	if (keycode == 126)
		win->move_y += 100;
	render(win);
}

void	zoom_map(int keycode, t_window *win)
{
	if (keycode == 69)
	{
		if (win->coef / 0.9 < 2147483647)
			win->coef /= 0.9;
	}
	else
		if (win->coef * 0.9 > 0.000001)
			win->coef *= 0.9;
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

void	wheel_zoom(int button, t_window *win)
{
	if (button == 4)
	{
		if (win->coef * 0.9 < 2147483647)
			win->coef *= 0.9;
	}
	else
		if (win->coef / 0.9 > 0.000001)
			win->coef /= 0.9;
	if (win->line->x1 * win->coef < 2147483647)
		construct_lines(win, win->points_map);
	render(win);
}

void	reset_map(t_window *win)
{
	printf("Called\n");
	set_coef(win);
	construct_lines(win, win->points_map);
	render(win);
	printf("Done\n");
}

void	change_line_color(t_window *win)
{
	if (win->color == RED)
		win->color = GREEN;
	else if (win->color == GREEN)
		win->color = BLUE;
	else if (win->color == BLUE)
		win->color = RED;
	render(win);
}

void	change_background(t_window *win)
{
	if (win->bg == BLACK)
		win->bg = YELLOW;
	else if (win->bg == YELLOW)
		win->bg = WHITE;
	else if (win->bg ==	WHITE)
		win->bg = BLACK;
	render(win);
}

/* void	rotate_x(int keycode, t_window *win)
{
	int	i;
	int map_size;
	int	prev_x;
	int	prev_y;
	int	prev_z;

	i = -1;
	map_size = win->map_width * win->map_height;
	if (keycode == 4)
	{
		while (i < map_size)
		{
			prev_y = win->points_map[i].y;
			prev_z = win->points_map[i].z;
			win->points_map[i].y = prev_y * cos(0.174533) + prev_z * 
		}
	}
} */

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
/* 	if (keycode == 83 || keycode == 84)
		rotate_x(keycode, win->points_map); */
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