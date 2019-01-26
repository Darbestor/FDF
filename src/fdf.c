/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 16:40:11 by ghalvors          #+#    #+#             */
/*   Updated: 2019/01/26 16:38:02 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <stdlib.h>
#include "../Libft/libft.h"
#include "../minilibx/mlx.h"
#include <math.h>

t_window*	mlx_new()
{
	t_window	*win;

	if (!(win = ft_memalloc(sizeof(t_window))) || !(win->mlx_ptr = mlx_init())
	|| !(win->win_ptr = mlx_new_window(win->mlx_ptr,
	SCREEN_SIZE_X, SCREEN_SIZE_Y, "FDF")) ||
	!(win->img_ptr = mlx_new_image(win->mlx_ptr, SCREEN_SIZE_X, SCREEN_SIZE_Y)))
		return NULL;
	win->data = (int*)mlx_get_data_addr(win->img_ptr, &win->bits, &win->pitch,
	&win->endian);
	win->pitch = win->pitch / (win->bits / 8);
	ft_bzero(win->data, win->pitch * SCREEN_SIZE_Y);
	win->color = RED;
	win->bg = BLACK;
	win->min_h = 0;
	win->max_h = 0;
	win->zoom = 1;
	win->coef = 0;
	win->rot_x = 0;
	win->rot_y = 0;
	win->rot_z = 0;
	win->max_x = 0;
	win->max_y = 0;
	return (win);
}

void	set_intense(int *pixel, float intense, t_window *win)
{
	*pixel = ((int)((((win->color >> 16) & 0xff) * intense) + (((win->bg >> 16)
	& 0xff) * (1 - intense))) << 16) | ((int)((((win->color >> 8) & 0xff)
	* intense) + (((win->bg >> 8) & 0xff) * (1 - intense))) << 8) |
	(int)(((win->color & 0xff) * intense) + ((win->bg & 0xff) * (1 - intense)));
}

void	draw_straight(t_line *line, t_window *win)
{
	int	dx;
	int	dy;
	float	m;
	float	intery;
	int		xi;

	dx = line->x2 - line->x1;
	dy = line->y2 - line->y1;
	m = (float)dy / dx;
	xi = line->x1 > 0 ? line->x1 - 1 : -1;
	intery = line->x1 != xi + 1 ? line->y1 - m * line->x1 : line->y1;
	while (++xi <= line->x2 && xi < SCREEN_SIZE_X)
	{
		if ((int)intery >= 0 && intery < SCREEN_SIZE_Y)
		{
			if (dx != 0)
					set_intense((int*)(win->data + xi + ((int)intery
					* win->pitch)), 1 - (intery - (int)intery), win);
			if (dy != 0 && (xi + (((int)intery + 1) * win->pitch)) < win->pitch * SCREEN_SIZE_Y)
					set_intense((int*)(win->data + xi + (((int)intery + 1)
					* win->pitch)), intery - (int)intery, win);
		}
		intery += m;
	}
//	printf("x1: %d\n", xi);
}

void	draw_reverse(t_line *line, t_window *win)
{
	int	dx;
	int	dy;
	float	m;
	float	intery;
	int		xi;

	dx = line->x2 - line->x1;
	dy = line->y2 - line->y1;
	m = (float)dy / dx;
	xi = line->x1 > 0 ? line->x1 - 1 : -1;
	intery = line->x1 != xi + 1 ? line->y1 - m * line->x1 : line->y1;
	while (++xi <= line->x2 && xi < SCREEN_SIZE_Y)
	{
		if ((int)intery > 0 && intery < SCREEN_SIZE_X)
		{
			if (dx != 0)
				set_intense((int*)(win->data + ((int)intery + xi
				* win->pitch)), 1 - (intery - (int)intery), win);
			if (dy != 0 && (int)intery + 1 < SCREEN_SIZE_X && (((int)intery + 1) + xi * win->pitch) < win->pitch * SCREEN_SIZE_Y)
				set_intense((int*)(win->data + (((int)intery + 1) + xi
				* win->pitch)), intery - (int)intery, win);
		}
		intery += m;
	}
}

void	algorithm(t_window* win, t_line line)
{
	int		steep;

//	printf("\n%d\t%d\n%d\t%d\n", line->x1, line->y1, line->x2, line->y2);
//printf("%d\t%d\n", win->move_x, win->move_y);
	line.x1 += win->move_x;
	line.x2 += win->move_x;
	line.y1 += win->move_y;
	line.y2 += win->move_y;
//	printf("%d\t%d\n", line.x1, line.x2);
	steep = abs(line.y2 - line.y1) > abs(line.x2 - line.x1);
	if (steep)
	{
		ft_swap(&(line.x1), &(line.y1), sizeof(line.y1));
		ft_swap(&(line.x2), &(line.y2), sizeof(line.y2));
	}
	if (line.x1 > line.x2)
	{
		ft_swap(&(line.x1), &(line.x2), sizeof(line.y1));
		ft_swap(&(line.y1), &(line.y2), sizeof(line.y2));
		ft_swap(&(line.color_begin), &(line.color_end), sizeof(line.y1));
	}
//	printf("\notrisovka ");
	if (steep)
		draw_reverse(&line, win);
	else
		draw_straight(&line, win);
//	printf("zavershena ");
}

void		set_coef(t_window *win)
{
	int	max_z;
	int	max_xy;
	int	max_val;
	int	screen_min;

	win->move_x = 0;
	win->move_y = 0;
	win->rot_speed = 0.0174533;
	max_z = abs(win->min_h) + win->max_h;
	max_xy = win->map_height > win->map_width ? win->map_height :
	win->map_width;
	max_val = max_z > max_xy ? max_z : max_xy;
	screen_min = SCREEN_SIZE_Y <= SCREEN_SIZE_X ?
	SCREEN_SIZE_Y : SCREEN_SIZE_X ;
	if (max_val >= screen_min)
	{
		win->coef = (max_val / screen_min) * 0.6;
		printf("%f\n\n", win->coef);
	}
	else
	{
		win->coef = (screen_min / max_val) * 0.6;
		printf("%f\n\n", win->coef);
	}
		win->smesh = SCREEN_SIZE_Y / 2 - win->map_height / 2;
}

void	rotate_x(t_point *cur, float angle)
{
	int	prev_y;
	int	prev_z;


//printf("%f\n", angle);
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
	map_size = win->map_width * win->map_height;
	while (++i < map_size)
	{
		win->cur_map[i].x = win->points_map[i].x *  win->coef;
		win->cur_map[i].y = win->points_map[i].y * win->coef;
		win->cur_map[i].z = win->points_map[i].z * win->coef;
		rotate_x(&(win->cur_map[i]), win->rot_x);
		rotate_y(&(win->cur_map[i]), win->rot_y);
		rotate_z(&(win->cur_map[i]), win->rot_z);
	}
}

void	construct_lines(t_window *win, t_point *map)
{
	int		i;
	t_line	*line;
	int		map_size;

	i = -1;
	line = (t_line*)ft_memalloc(sizeof(t_line) *
	(((win->map_width - 1) * win->map_height) +
	(win->map_width * (win->map_height -1))));
	win->line = line;
	map_size = win->map_width * win->map_height;
//s	apply_coef(win);
	while (++i < map_size)
	{
		if ((i + 1) % win->map_width != 0)
			project(map + i, map + i + 1, win, line++);
		if (i + win->map_width < map_size)
			project(map + i, map + (i + win->map_width), win, line++);
	}
}

void	set_center(t_window *win)
{
	int		i;
	int		lines;
//	t_window*	win;
	t_line	*line;

	i = -1;
//	win = (t_window*)param;
	lines = ((win->map_width - 1) * win->map_height) +
	(win->map_width * (win->map_height -1));
	line = win->line;
	win->min_x = line->x1;
	win->max_x = line->x2;
	win->min_y = line->y1;
	win->max_y = line->y2;
	while (++i < lines)
	{
		if (line[i].x1 < win->min_x)
			win->min_x = line[i].x1;
		else if (line[i].x2 < win->min_x)
			win->min_x = line[i].x2;
		//////////////////////
		if (line[i].x1 > win->max_x)
			win->max_x = line[i].x1;
		else if (line[i].x2 > win->max_x)
			win->max_x = line[i].x2;
		////////////////
		if (line[i].y1 < win->min_y)
			win->min_y = line[i].y1;
		else if (line[i].y2 < win->min_y)
			win->min_y = line[i].y2;
		//////////////////////////
		if (line[i].y1 > win->max_y)
			win->max_y = line[i].y1;
		else if (line[i].y2 > win->max_y)
			win->max_y = line[i].y2;
	}
/* 	printf("\n%d\t%d\n", win->min_y, win->max_y);
	printf("\n%d\t%d\n", win->min_x, win->max_x); */
	win->max_y = -(win->min_y - (SCREEN_SIZE_Y - (win->max_y - win->min_y)) / 2);
	win->max_x = -(win->min_x - (SCREEN_SIZE_X - (win->max_x - win->min_x)) / 2);
	i = -1;
	while (++i < lines)
	{
		line[i].y1 += win->max_y;
		line[i].y2 += win->max_y;
		line[i].x1 += win->max_x;
		line[i].x2 += win->max_x;
	}
}

int	render(t_window *win)
{
	int		i;
	int		lines;
//	t_window*	win;
	t_line	*line;

	i = -1;
//	win = (t_window*)param;
	while (++i < SCREEN_SIZE_Y * win->pitch)
		win->data[i] = win->bg;
	lines = ((win->map_width - 1) * win->map_height) +
	(win->map_width * (win->map_height -1));
	line = win->line;
//	printf("%d:%d\t%d:%d\n", line->x1, line->y1, line->x2, line->y2);
	i = -1;
	while (++i < lines)
	{
		algorithm(win, line[i]);
//		printf("%d\n", i + 1);
	}
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_window	*win;
	int			i;

	i = 0;
	if (!(win = mlx_new()))
		return (1);
	if (!(read_map(argc, argv, &(win->map_height), &(win->map_width))) ||
	!(create_map(argv[1], win)))
	{
		perror("Error reading map");
		exit(0);
	}
//	win->points_map = map;
	win->proj = 0;
	set_coef(win);
	apply_coef(win);
	construct_lines(win, win->cur_map);
	set_center(win);
	render(win);
	win->auto_rotate = 0;
	mlx_hook(win->win_ptr, 2, 0, &key_press, win);
	mlx_hook(win->win_ptr, 4, 0, &mouse_press, win);
	mlx_hook(win->win_ptr, 3, 0, &key_release, win);
	mlx_loop_hook(win->mlx_ptr, &auto_rotate, win);
	mlx_loop(win->mlx_ptr);
//	mlx_loop_hook(win->mlx_ptr, &render, win);
	return (0);
}