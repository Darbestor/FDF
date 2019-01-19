/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 16:39:50 by ghalvors          #+#    #+#             */
/*   Updated: 2019/01/19 20:22:11 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define SCREEN_SIZE_X 1000
# define SCREEN_SIZE_Y 1000

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
	int				map_size;
	struct s_window	*next;
}					t_window;

typedef struct		s_coords
{
	int				x1;
	int				x2;
	int				y1;
	int				y2;
}					t_coords;

typedef struct		s_point
{
	int				x;
	int				y;
	int				z;
}					t_point;

int	read_map(int argc, char **argv);

#endif