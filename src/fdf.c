/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 16:40:11 by ghalvors          #+#    #+#             */
/*   Updated: 2019/01/18 20:21:42 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <stdio.h>
#include <stdlib.h>
#include "../Libft/libft.h"
#include "../minilibx/mlx.h"
#include <math.h>

int	ft_exit(int keycode, void *param)
{
	if (keycode == 53)
	{
		(void)param;
		exit(0);
		return(0);
	}
	return(1);
}

t_window*	mlx_new()
{
	t_window	*win;
	int			i;

	if (!(win = ft_memalloc(sizeof(t_window))) || !(win->mlx_ptr = mlx_init())
	|| !(win->win_ptr = mlx_new_window(win->mlx_ptr,
	SCREEN_SIZE_X, SCREEN_SIZE_Y, "FDF")) ||
	!(win->img_ptr = mlx_new_image(win->mlx_ptr, SCREEN_SIZE_X, SCREEN_SIZE_Y)))
		return NULL;
	win->data = (int*)mlx_get_data_addr(win->img_ptr, &win->bits, &win->pitch,
	&win->endian);
	win->pitch = win->pitch / (win->bits / 8);
	ft_bzero(win->data, win->pitch * SCREEN_SIZE_Y);
	win->color = 0x0000ff;
	win->bg = 0xff0000;
	i = 0;
	while (i < SCREEN_SIZE_Y * win->pitch)
		win->data[i++] = win->bg;
	return (win);
}

void	set_intense(int *pixel, float intense, t_window *win)
{
	*pixel = ((int)((((win->color >> 16) & 0xff) * intense) + (((win->bg >> 16)
	& 0xff) * (1 - intense))) << 16) | ((int)((((win->color >> 8) & 0xff)
	* intense) + (((win->bg >> 8) & 0xff) * (1 - intense))) << 8) |
	(int)(((win->color & 0xff) * intense) + ((win->bg & 0xff) * (1 - intense)));
}

void	draw_straight(t_coords *coords, t_window *win)
{
	int	dx;
	int	dy;
	float	m;
	float	intery;
	int		xi;

	dx = coords->x2 - coords->x1;
	dy = coords->y2 - coords->y1;
	m = (float)dy / dx;
	xi = coords->x1 > 0 ? coords->x1 - 1 : -1;
	intery = coords->x1 != xi + 1 ? coords->y1 - m * coords->x1 : coords->y1;
	while (++xi <= coords->x2)
	{
		if (intery >= 0 && xi < SCREEN_SIZE_X && intery < SCREEN_SIZE_Y)
		{
			if (dx != 0 || xi == coords->x2)
				set_intense((int*)(win->data + xi + ((int)intery
				* win->pitch)), 1 - (intery - (int)intery), win);
			if (dy != 0 || intery == coords->y2)
				set_intense((int*)(win->data + xi + (((int)intery + 1)
				* win->pitch)), intery - (int)intery, win);
		}
		intery += m;
	}
}

void	draw_reverse(t_coords *coords, t_window *win)
{
	int	dx;
	int	dy;
	float	m;
	float	intery;
	int		xi;

	dx = coords->x2 - coords->x1;
	dy = coords->y2 - coords->y1;
	m = (float)dy / dx;
	xi = coords->x1 > 0 ? coords->x1 - 1 : -1;
	intery = coords->x1 != xi + 1 ? coords->y1 - m * coords->x1 : coords->y1;
	while (++xi <= coords->x2)
	{
		if (intery >= 0 && xi < SCREEN_SIZE_X && intery < SCREEN_SIZE_Y)
		{
		if (dx != 0 || xi == coords->x2)
			set_intense((int*)(win->data + ((int)intery + xi
			* win->pitch)), 1 - (intery - (int)intery), win);
		if (dy != 0 || intery == coords->y2)
			set_intense((int*)(win->data + (((int)intery + 1) + xi
			* win->pitch)), intery - (int)intery, win);
		}
		intery += m;
	}
}

void	algorithm(t_coords *coords, t_window* win)
{
	int		steep;

	steep = abs(coords->y2 - coords->y1) > abs(coords->x2 - coords->x1);
	if (steep)
	{
		ft_swap(&(coords->x1), &(coords->y1), sizeof(coords->y1));
		ft_swap(&(coords->x2), &(coords->y2), sizeof(coords->y2));
	}
	if (coords->x1 > coords->x2)
	{
		ft_swap(&(coords->x1), &(coords->x2), sizeof(coords->y1));
		ft_swap(&(coords->y1), &(coords->y2), sizeof(coords->y2));
	}
	if (steep)
		draw_reverse(coords, win);
	else
		draw_straight(coords, win);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
}

int	main(void)
{
	t_window	*win;
	t_coords	**coords;
	int			i;

	i = 0;
	if (!(win = mlx_new()))
		return (1);
	coords = malloc(sizeof(t_coords**) * 360);
	while (i < 360)
	{
		coords[i] = (t_coords*)malloc(sizeof(t_coords));
		(coords)[i]->x1 = 500;
		(coords)[i]->x2 = round((coords)[i]->x1 + cos(i) * 500);
		(coords)[i]->y1 = 500;
		(coords)[i]->y2 = round((coords)[i]->y1 + sin(i) * 500);
		if ((coords)[i]->x2 || (coords)[i]->y2)
		algorithm(coords[i++], win);
	}
/* 		coords[i] = (t_coords*)malloc(sizeof(t_coords));
		(coords)[i]->x1 = 500;
		(coords)[i]->x2 = 501;
		(coords)[i]->y1 = 500;
		(coords)[i]->y2 = 501;
		algorithm(coords[i], win); */
	mlx_key_hook(win->win_ptr, ft_exit, 0);
	mlx_loop(win->mlx_ptr);
	return (0);
}
