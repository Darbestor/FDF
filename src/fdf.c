/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 16:40:11 by ghalvors          #+#    #+#             */
/*   Updated: 2018/12/29 19:22:39 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <stdio.h>
#include <stdlib.h>
#include "../Libft/libft.h"
#include "../minilibx/mlx.h"

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

int ft_mouse_release(int button, int x, int y, void *param)
{
	x = 0;
	y = 0;
	button = 0;
	((t_window*)param)->state = 0;
	return (0);
}

int ft_mouse_move(int x, int y, void *param)
{
	if (((t_window*)param)->state)
		mlx_pixel_put(((t_window*)param)->mlx_ptr, ((t_window*)param)->win_ptr,
		x, y, 0xff0000);
	mlx_hook(((t_window*)param)->win_ptr, 5, 0, ft_mouse_release, param);
	return (0);
}

int	ft_draw_pixel(int button, int x, int y, void *param)
{
	((t_window*)param)->state = 1;
	if (button == 1)
	{
		mlx_pixel_put(((t_window*)param)->mlx_ptr,
			((t_window*)param)->win_ptr, x, y, 0xff0000);
		mlx_hook(((t_window*)param)->win_ptr, 6, 0, ft_mouse_move, param);
	}
	return (0);
}

int	main(void)
{
	t_window	*window;

	window = ft_memalloc(sizeof(t_window) * 1);
	int i = 0;
	int j;
	window->mlx_ptr = mlx_init();
	window->win_ptr = mlx_new_window(window->mlx_ptr, SCREEN_SIZE_X, SCREEN_SIZE_Y, "FDF");
	while (i < SCREEN_SIZE_X)
	{
		j = 0;
		while (j < SCREEN_SIZE_Y)
		{
			mlx_pixel_put(window->mlx_ptr, window->win_ptr, i, j, 0xff);
			j++;
		}
		i++;
	}
	mlx_key_hook(window->win_ptr, ft_exit, 0);
	mlx_hook(window->win_ptr, 4, 0, ft_draw_pixel, (void*)window);
	mlx_loop(window->mlx_ptr);
	return (0);
}