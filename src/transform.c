/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 11:41:33 by ghalvors          #+#    #+#             */
/*   Updated: 2019/01/26 19:54:14 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../Libft/libft.h"
#include <math.h>

void	iso(t_point *begin, t_point *end, t_line **line, t_window *win)
{
	int	prev_x;
	int	prev_y;

	prev_x = begin->x;
	prev_y = begin->y;
	(*line)->x1 = (prev_x - prev_y) * cos(0.523599) + win->off_x;
	(*line)->y1 = -(begin->z) + (prev_x + prev_y) * sin(0.523599) + win->off_y;
	prev_x = end->x;
	prev_y = end->y;
	(*line)->x2 = (prev_x - prev_y) * cos(0.523599) + win->off_x;
	(*line)->y2 = -(end->z) + (prev_x + prev_y) * sin(0.523599) + win->off_y;
}

void	parallel(t_point *begin, t_point *end, t_line **line, t_window *win)
{
	(*line)->x1 = begin->x + win->off_x;
	(*line)->y1 = begin->y + win->off_y;
	(*line)->x2 = end->x + win->off_x;
	(*line)->y2 = end->y + win->off_y;
}

void	project(t_point *begin, t_point *end, t_window *win, t_line *line)
{
	if (win->proj)
		iso(begin, end, &line, win);
	else
		parallel(begin, end, &line, win);
}
