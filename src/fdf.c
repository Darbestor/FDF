/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 16:40:11 by ghalvors          #+#    #+#             */
/*   Updated: 2019/01/26 19:52:40 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <stdlib.h>
#include "../Libft/libft.h"
#include "../minilibx/mlx.h"
#include <math.h>
#include <unistd.h>
#include <stdio.h>

t_window	*mlx_new(void)
{
	t_window	*win;

	if (!(win = ft_memalloc(sizeof(t_window))))
		return (NULL);
	if (!(win->mlx_ptr = mlx_init()))
		return (NULL);
	if (!(win->win_ptr = mlx_new_window(win->mlx_ptr, WIN_W, WIN_H, "FDF")))
		return (NULL);
	if (!(win->img = mlx_new_image(win->mlx_ptr, WIN_W, WIN_H)))
		return (NULL);
	win->data = (int*)mlx_get_data_addr(win->img, &win->bits, &win->pitch,
	&win->endian);
	win->pitch = win->pitch / (win->bits / 8);
	win->color = RED;
	win->bg = BLACK;
	win->proj = 0;
	win->auto_rotate = 0;
	win->min_h = 0;
	win->max_h = 0;
	return (win);
}

void		construct_lines(t_window *win)
{
	int		i;
	t_line	*line;
	int		map_size;

	i = -1;
	line = win->line;
	map_size = win->map_w * win->map_h;
	apply_coef(win);
	while (++i < map_size)
	{
		if ((i + 1) % win->map_w != 0)
			project(win->cur_map + i, win->cur_map + i + 1, win, line++);
		if (i + win->map_w < map_size)
			project(win->cur_map + i, win->cur_map + (i + win->map_w),
			win, line++);
	}
}

int			ft_error(int err)
{
	if (err == 1)
		write(2, "Memory allocation error\n", 24);
	if (err == 2)
		perror("Error reading map");
	if (err == 3)
		write(2, "usage: fdf ./source file\n", 25);
	if (err == 4)
		write(2, "Invalid map\n", 12);
	exit(0);
	return (0);
}

int			main(int argc, char **argv)
{
	t_window	*win;
	int			err;

	if (!(win = mlx_new()))
		return (ft_error(1));
	if ((err = read_map(argc, argv, &win->map_h, &win->map_w)))
		return (ft_error(err));
	if ((err = create_map(argv[1], win)))
		return (ft_error(err));
	set_coef(win);
	if (!(win->line = (t_line*)ft_memalloc(sizeof(t_line) *
	(((win->map_w - 1) * win->map_h) + (win->map_w * (win->map_h - 1))))))
		return (ft_error(1));
	construct_lines(win);
	set_center(win);
	render(win);
	mlx_hook(win->win_ptr, 2, 0, &key_press, win);
	mlx_hook(win->win_ptr, 4, 0, &mouse_press, win);
	mlx_hook(win->win_ptr, 3, 0, &key_release, win);
	mlx_loop_hook(win->mlx_ptr, &auto_rotate, win);
	mlx_loop(win->mlx_ptr);
	return (0);
}
