/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 16:40:11 by ghalvors          #+#    #+#             */
/*   Updated: 2019/01/22 21:33:40 by ghalvors         ###   ########.fr       */
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
	win->color = 0x00FF00;
	win->bg = 0x000000;
	win->min_h = 0;
	win->max_h = 0;
	win->zoom = 1;
	win->coef = 0;
	return (win);
}

//for test purpose
double percent(int start, int end, int current)
{
    double placement;
    double distance;

    placement = current - start;
    distance = end - start;
    return ((distance == 0) ? 1.0 : (placement / distance));
}

int get_light(int start, int end, double percentage)
{
    return ((int)((1 - percentage) * start + percentage * end));
}

int	get_color(t_line *line, int dx, int dy, int x, int y)
{
	int R;
	int G;
	int B;
	double percentage;

    if (dx > dy)
        percentage = percent(line->x1, line->x2, x);
    else
        percentage = percent(line->y1, line->y2, y);
	R = get_light((line->color_begin >> 16) & 0xFF, (line->color_end >> 16) & 0xFF, percentage);
    G = get_light((line->color_begin >> 8) & 0xFF, (line->color_end >> 8) & 0xFF, percentage);
    B = get_light(line->color_begin & 0xFF, line->color_end & 0xFF, percentage);
	return ((R << 16) | (G << 8) | B);
}

void	set_intense1(int *pixel, float intense, t_window *win, int color)
{
	*pixel = ((int)((((color >> 16) & 0xff) * intense) + (((win->bg >> 16)
	& 0xff) * (1 - intense))) << 16) | ((int)((((color >> 8) & 0xff)
	* intense) + (((win->bg >> 8) & 0xff) * (1 - intense))) << 8) |
	(int)(((color & 0xff) * intense) + ((win->bg & 0xff) * (1 - intense)));
}
//get_color(line, dx, dy, (int)intery, xi * win->pitch)
////////////////////////


// Сделать градиент в зависимости от цвета 2 точек заданных в координатах
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
				if (dx != 0 || xi == line->x2)
					set_intense((int*)(win->data + xi + ((int)intery
					* win->pitch)), 1 - (intery - (int)intery), win);
				if (dy != 0 || intery == line->y2)
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
	while (++xi <= line->x2 && xi < SCREEN_SIZE_X)
	{
		if ((int)intery >= 0 && intery < SCREEN_SIZE_Y &&
		(xi + (((int)intery + 1) * win->pitch)) < win->pitch * SCREEN_SIZE_Y)
		{
			if (dx != 0 || xi == line->x2)
				set_intense((int*)(win->data + ((int)intery + xi
				* win->pitch)), 1 - (intery - (int)intery), win);
			if (dy != 0 || intery == line->y2)
				set_intense((int*)(win->data + (((int)intery + 1) + xi
				* win->pitch)), intery - (int)intery, win);
		}
		intery += m;
	}
//	printf("x1: %d\n", xi);
}

void	algorithm(t_window* win, t_line line)
{
	int		steep;

//	printf("\n%d\t%d\n%d\t%d\n", line->x1, line->y1, line->x2, line->y2);
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
	}
//	printf("\notrisovka ");
	if (steep)
		draw_reverse(&line, win);
	else
		draw_straight(&line, win);
//	printf("zavershena ");
}

void		get_coef(t_window *win)
{
	int	max_z;
	int	max_xy;
	int	max_val;

	max_z = abs(win->min_h) + win->max_h;
	max_xy = win->map_height > win->map_width ? win->map_height :
	win->map_width;
	max_val = max_z > max_xy ? max_z : max_xy;
	if (max_val >= SCREEN_SIZE_Y)
		win->coef = ((max_val / SCREEN_SIZE_Y) / 2);
	else
		win->coef = ((SCREEN_SIZE_Y / max_val) / 2);
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
//	int k = 1;
	int f = 1;
	int j = 0;
	while (++i < map_size)
	{
		if (i % win->map_width == 0)
		{
			f =  1;
//			printf("\nline: %d\n", k++);
		}
		if ((i + 1) % win->map_width != 0)
		{
//			printf("%d\t", f++);
			j++;
			//printf("right: %d->%d\t", (map+ i)->z, (map + i + 1)->z);
			project(map + i, map + i + 1, win, line++);
		}
		if (i + win->map_width < map_size)
		{
			j++;
			//printf("%d\t", f++);
			//printf("bot: %d->%d\n", (map + i)->z, (map + (i + win->map_width))->z);
			project(map + i, map + (i + win->map_width), win, line++);
//			printf("coords: %d:%d-%d:%d,\t", line->x1, line->y1, line->x2, line->y2);
		}
//		printf("%d\t%d\t%d\n", map[i].x, map[i].y, map[i].z);
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
	get_coef(win);
	construct_lines(win, map);
	render(win);

	mlx_hook(win->win_ptr, 2, 0, &key_press, win);
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