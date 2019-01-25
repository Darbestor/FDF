/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 16:39:50 by ghalvors          #+#    #+#             */
/*   Updated: 2019/01/25 19:50:08 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define SCREEN_SIZE_X 1000
# define SCREEN_SIZE_Y 1000

#include <stdio.h>
typedef enum		e_color
{
	RED = 0xff0000,
	GREEN = 0x00ff00,
	BLUE = 0x0000ff,
	BLACK = 0x000000,
	WHITE = 0xffffff,
	YELLOW = 0xffff00,
	KHAKI = 0xf0e68c
}					t_color;

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
	t_color			bg;
	t_color			color;
	int				bits;
	int				pitch;
	int				endian;
	int				map_height;
	int				map_width;
	int				min_h;
	int				max_h;
	float			coef;
	int				gap;
	float			zoom;
	int				move_x;
	int				move_y;
	float			rot_x;
	float			rot_y;
	float			rot_z;
	float			rot_speed;
	int				auto_rotate;
	int				ctrl;
	t_line			*line;
	t_point			*points_map;
	t_point			*cur_map;
	int				smesh;
	struct s_window	*next;
}					t_window;

int		read_map(int argc, char **argv, int *map_heigth, int *map_width);
int		create_map(char *file, t_window *win);
void	project(t_point *begin, t_point *end, t_window *win, t_line *line);
int		key_press(int keycode, void *param);
int		render(t_window *win);
void	construct_lines(t_window *win, t_point *map);
int		mouse_press(int button, int x, int y, void *param);
void	set_coef(t_window *win);
void	apply_coef(t_window *win);
int		auto_rotate(t_window *win);
int		key_release(int keycode, void *param);

#endif