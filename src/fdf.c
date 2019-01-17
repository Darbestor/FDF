/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 16:40:11 by ghalvors          #+#    #+#             */
/*   Updated: 2019/01/17 20:14:40 by ghalvors         ###   ########.fr       */
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
	int			j;

	if (!(win = ft_memalloc(sizeof(t_window))) || !(win->mlx_ptr = mlx_init())
	|| !(win->win_ptr = mlx_new_window(win->mlx_ptr,
	SCREEN_SIZE_X, SCREEN_SIZE_Y, "FDF")) ||
	!(win->img_ptr = mlx_new_image(win->mlx_ptr, SCREEN_SIZE_X, SCREEN_SIZE_Y)))
		return NULL;
	win->data = mlx_get_data_addr(win->img_ptr, &win->bits, &win->pitch, &win->endian);
	win->draw_color = 0xffffff;
	win->bg = 0x000000;
	i = 0;
	while (i < SCREEN_SIZE_X)
	{
		j = 0;
		while (j < SCREEN_SIZE_Y)
		{
			mlx_pixel_put(win->mlx_ptr, win->win_ptr, i, j, win->bg);
			j++;
		}
		i++;
	}
	printf("%d\t%d\t%d\n", win->bits, win->pitch, win->endian);
	return (win);
}

int	set_intense(float intense, int color, int bg)
{
	int	R;
	int	G;
	int	B;
	int	hex;

	R = (((color >> 16) & 0xff) * intense) + (((bg >> 16) & 0xff) * (1 - intense));
	G = (((color >> 8) & 0xff) * intense) + (((bg >> 8) & 0xff) * (1 - intense));
	B = ((color & 0xff) * intense) + ((bg & 0xff) * (1 - intense));
	hex = (R << 16) + (G << 8) + B;
	return (hex);
}

int	check_axis(t_coords *coords)
{
	int steep;

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
	return (steep);
}

void	algorithm(t_coords *coords, t_window* win)
{
	float dx;
	float dy;
	float gradient;
	float intery;

	int steep = check_axis(coords);
	dx = coords->x2 - coords->x1;
	dy = coords->y2 - coords->y1;
	gradient = dy / dx;
	intery = coords->y1 + gradient;
	while (coords->x1 < coords->x2)
	{
		mlx_pixel_put(win->mlx_ptr, win->win_ptr, steep ? (int)intery :
		coords->x1, steep ? coords->x1 : (int)intery,
		set_intense(1 - (intery - (int)intery), win->draw_color, win->bg));
		mlx_pixel_put(win->mlx_ptr, win->win_ptr, steep ? (int)intery + 1 :
		coords->x1, steep ? coords->x1 : (int)intery + 1,
		set_intense(intery - (int)intery, win->draw_color, win->bg));
		intery += gradient;
		coords->x1++;
	}
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
		(coords)[i]->x2 = round((coords)[i]->x1 + cos(i) * 400);
		(coords)[i]->y1 = 500;
		(coords)[i]->y2 = round((coords)[i]->y1 + sin(i) * 400);
		algorithm(coords[i++], win);
	}
/* 		coords[i] = (t_coords*)malloc(sizeof(t_coords));
		(coords)[i]->x1 = 0;
		(coords)[i]->x2 = 1000;
		(coords)[i]->y1 = 500;
		(coords)[i]->y2 = 500;
		algorithm(coords[i], win, 0xffffff, 0xff0000); */
	mlx_key_hook(win->win_ptr, ft_exit, 0);
	printf("%d", mlx_get_color_value(win->mlx_ptr, 0x0000ff));
	mlx_loop(win->mlx_ptr);
	return (0);
}
