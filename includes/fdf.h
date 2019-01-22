/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 16:39:50 by ghalvors          #+#    #+#             */
/*   Updated: 2019/01/22 20:03:12 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define SCREEN_SIZE_X 1000
# define SCREEN_SIZE_Y 1000

#include <stdio.h>

typedef struct		s_line
{
	int				x1;
	int				x2;
	int				y1;
	int				y2;
	int				color_begin;
	int				color_end;
}					t_line;

typedef struct		s_point
{
	int				x;
	int				y;
	int				z;
	int				color;
}					t_point;

typedef struct		s_window
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	int				*data;
	int				bg;
	int				color;
	int				bits;
	int				pitch;
	int				endian;
	int				map_height;
	int				map_width;
	int				min_h;
	int				max_h;
	float				coef;
	int				gap;
	float				zoom;
	t_line			*line;
	t_point			*points_map;
	struct s_window	*next;
}					t_window;

int		read_map(int argc, char **argv, int *map_heigth, int *map_width);
t_point	*create_map(char *file, t_window *win);
void	project(t_point *begin, t_point *end, t_window *win, t_line *line);
int		key_press(int keycode, void *param);
int		render(void *param);
void	construct_lines(t_window *win, t_point *map);

#endif