/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 11:41:33 by ghalvors          #+#    #+#             */
/*   Updated: 2019/01/26 16:37:31 by ghalvors         ###   ########.fr       */
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
	(void)win;
	(*line)->x1 = (prev_x - prev_y) * cos(0.523599) + win->max_x;
	(*line)->y1 = -(begin->z) + (prev_x + prev_y) * sin(0.523599) + win->max_y;// + (SCREEN_SIZE_Y / 2 - win->map_height / 2);
	(*line)->color_begin = begin->color;
	prev_x = end->x;
	prev_y = end->y;
	(*line)->x2 = (prev_x - prev_y) * cos(0.523599) + win->max_x;// + (SCREEN_SIZE_X / 2);
	(*line)->y2 = -(end->z) + (prev_x + prev_y) * sin(0.523599) + win->max_y;// + (SCREEN_SIZE_Y / 2 - win->map_height / 2);
	(*line)->color_end = end->color;
	printf("coords: %d:%d\t%d:%d\n", (*line)->x1, (*line)->y1, (*line)->x2, (*line)->y2);
}

void	parallel(t_point *begin, t_point *end, t_line **line, t_window *win)
{
	(*line)->x1 = begin->x + win->max_x;
	(*line)->y1 = begin->y + win->max_y;
	(*line)->x2 = end->x + win->max_x;
	(*line)->y2 = end->y + win->max_y;
}

void	project(t_point *begin, t_point *end, t_window *win, t_line *line)
{
//	(void)win;
	if (win->proj)
		iso(begin ,end, &line, win);
	else
		parallel(begin ,end, &line, win);
//	printf("begin coords:\t%d\t%d\t%d\nend coords:\t%d\t%d\t%d\n", begin->x,
//	begin->y, begin->z, end->x, end->y, end->z);
//	printf("\nTranformed:\t%d\t%d\n\t\t%d\t%d\n", line->x1, line->y1, line->x2, line->y2);
}