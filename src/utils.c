/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 15:08:21 by ghalvors          #+#    #+#             */
/*   Updated: 2019/01/25 19:54:32 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <stdlib.h>
#include <math.h>
#include <mlx.h>

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
		apply_coef(win);
		construct_lines(win, win->cur_map);
//	printf("Render\n");
		render(win);
//	printf("Complete\n");
	}
}

int		rotate_speed(int button, t_window *win)
{
	if (button == 4)
		if (win->rot_speed - 0.0174533 > 0.001)
			win->rot_speed -= 0.0174533;
	if (button == 5)
		if (win->rot_speed + 0.0174533 < 1.5708)
			win->rot_speed += 0.0174533;
		printf("\nspeed\t%f\n", win->rot_speed);
	return (0);
}

void	wheel_zoom(int button, t_window *win)
{
	if (win->ctrl)
		rotate_speed(button, win);
	else
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
		{
			apply_coef(win);
			construct_lines(win, win->cur_map);
		}
		render(win);
	}
}

void	reset_map(t_window *win)
{
	printf("Called\n");
	set_coef(win);
	apply_coef(win);
	construct_lines(win, win->cur_map);
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
	apply_coef(win);
	construct_lines(win, win->cur_map);
	render(win);
}

int	auto_rotate(t_window *win)
{
/* 	if (win->auto_rotate)
		win->auto_rotate = 0;
	else
		win->auto_rotate = 1; */
/* 	while (win->auto_rotate)
	{ */
	if (!win->auto_rotate)
		return (1);
		if (win->rot_z >= 6.28319)
			win->rot_z = 0;
		else
			win->rot_z += win->rot_speed;
		apply_coef(win);
		construct_lines(win, win->cur_map);
		render(win);
/* 		printf("CALLED\n");
	} */
	return (0);
}

int key_release(int keycode, void *param)
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
	{
		if (win->auto_rotate)
			win->auto_rotate = 0;
		else
			win->auto_rotate = 1;
	}
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