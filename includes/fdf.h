/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 16:39:50 by ghalvors          #+#    #+#             */
/*   Updated: 2019/01/26 19:58:45 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIN_W 1000
# define WIN_H 1000
# define ABS(X) ((X)<0 ? -(X) : (X))

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
}					t_line;

typedef struct		s_point
{
	int				x;
	int				y;
	int				z;
}					t_point;

typedef struct		s_window
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img;
	int				*data;
	t_color			bg;
	t_color			color;
	int				bits;
	int				pitch;
	int				endian;
	int				map_h;
	int				map_w;
	int				min_h;
	int				max_h;
	float			coef;
	float			zoom;
	int				move_x;
	int				move_y;
	float			rot_x;
	float			rot_y;
	float			rot_z;
	float			rot_speed;
	int				auto_rotate;
	int				ctrl;
	int				min_x;
	int				off_x;
	int				min_y;
	int				off_y;
	int				proj;
	t_line			*line;
	t_point			*init_map;
	t_point			*cur_map;
}					t_window;

int					read_map(int argc, char **argv, int *map_heigth,
					int *map_w);
int					create_map(char *file, t_window *win);
void				project(t_point *begin, t_point *end, t_window *win,
					t_line *line);
int					key_press(int keycode, void *param);
int					render(t_window *win);
void				construct_lines(t_window *win);
int					mouse_press(int button, int x, int y, void *param);
void				set_coef(t_window *win);
void				apply_coef(t_window *win);
int					auto_rotate(t_window *win);
int					key_release(int keycode, void *param);
void				set_center(t_window *win);
void				change_background(t_window *win);
void				change_line_color(t_window *win);
void				reset_map(t_window *win);
int					auto_rotate(t_window *win);
void				set_rotation(int keycode, t_window *win);
void				wheel_zoom(int button, t_window *win);
int					rotate_speed(int button, t_window *win);
void				zoom_map(int keycode, t_window *win);
void				move_map(int keycode, t_window *win);
int					close_win(void *param);
void				set_projection(t_window *win);

#endif
