/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 16:40:11 by ghalvors          #+#    #+#             */
/*   Updated: 2019/01/23 20:47:59 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <stdio.h>
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
		if ((int)intery >= 0 && intery < SCREEN_SIZE_Y &&
		(xi + (((int)intery + 1) * win->pitch)) < win->pitch * SCREEN_SIZE_Y)
		{
					set_intense((int*)(win->data + xi + ((int)intery
					* win->pitch)), 1 - (intery - (int)intery), win);
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
		if ((int)intery > 0 && intery < SCREEN_SIZE_X &&
		(((int)intery + 1) + xi * win->pitch) < win->pitch * SCREEN_SIZE_Y)
		{
//			printf("x1: %d\n", (int)intery);
				set_intense((int*)(win->data + ((int)intery + xi
				* win->pitch)), 1 - (intery - (int)intery), win);
			if ((int)intery + 1 < SCREEN_SIZE_X)
				set_intense((int*)(win->data + (((int)intery + 1) + xi
				* win->pitch)), intery - (int)intery, win);
		}
		intery += m;
	}
//	printf("NEXT\n");
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
	max_z = abs(win->min_h) + win->max_h;
	max_xy = win->map_height > win->map_width ? win->map_height :
	win->map_width;
	max_val = max_z > max_xy ? max_z : max_xy;
	screen_min = SCREEN_SIZE_Y <= SCREEN_SIZE_X ?
	SCREEN_SIZE_Y * sin(0.523599) : SCREEN_SIZE_X * cos(0.523599);
	if (max_val >= screen_min)
		win->coef = (max_val / screen_min);
	else
		win->coef = (screen_min / max_val);
}

void	construct_lines(t_window *win)
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
	while (++i < map_size)
	{
		if ((i + 1) % win->map_width != 0)
			project(win->points_map + i, win->points_map + i + 1, win, line++);
		if (i + win->map_width < map_size)
			project(win->points_map + i, win->points_map +
			(i + win->map_width), win, line++);
	}
}

int	render(void *param)
{
	int		i;
	int		lines;
	t_window*	win;
	t_line	*line;

	i = -1;
	win = (t_window*)param;
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
	t_point		*map;
//	t_line		*line;
	int			i;

	i = 0;
	if (!(win = mlx_new()))
		return (1);
	if (!(read_map(argc, argv, &(win->map_height), &(win->map_width))) ||
	!(map = create_map(argv[1], win)))
	{
		perror("Error reading map");
		exit(0);
	}
	win->points_map = map;
	set_coef(win);
	construct_lines(win);
	render(win);

	mlx_hook(win->win_ptr, 2, 0, &key_press, win);
	mlx_hook(win->win_ptr, 4, 0, &mouse_press, win);
//	mlx_loop_hook(win->mlx_ptr, &render, win);
	mlx_loop(win->mlx_ptr);
	return (0);
}


// print line 360 degrees test
/* 	line = malloc(sizeof(t_line**) * 360);
	while (i < 360)
	{
		line[i] = (t_line*)malloc(sizeof(t_line));
		(line)[i]->x1 = 500;
		(line)[i]->x2 = round((line)[i]->x1 + cos(i) * 500);
		(line)[i]->y1 = 500;
		(line)[i]->y2 = round((line)[i]->y1 + sin(i) * 500);
		if ((line)[i]->x2 || (line)[i]->y2)
		algorithm(line[i++], win);
	} */
/* 		map[i] = (t_map*)malloc(sizeof(t_map));
		(map)[i]->x1 = 500;
		(map)[i]->x2 = 501;
		(map)[i]->y1 = 500;
		(map)[i]->y2 = 501;
		algorithm(map[i], win); */