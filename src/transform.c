/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 11:41:33 by ghalvors          #+#    #+#             */
/*   Updated: 2019/01/22 21:15:58 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../Libft/libft.h"
#include <math.h>

void	iso(t_point *begin, t_point *end, t_line **line, int coef)
{
	int	prev_x;
	int	prev_y;
	
	
	prev_x = begin->x * coef;
	prev_y = begin->y * coef;
	(*line)->x1 = (prev_x - prev_y) * cos(0.523599) + SCREEN_SIZE_X / 2;
	(*line)->y1 = -(begin->z * coef) + (prev_x + prev_y) * sin(0.523599) + SCREEN_SIZE_Y / 2;
	(*line)->color_begin = 0xFFFFFF;
	prev_x = end->x * coef;
	prev_y = end->y * coef;
	(*line)->x2 = (prev_x - prev_y) * cos(0.523599) + SCREEN_SIZE_X / 2;
	(*line)->y2 = -(end->z * coef) + (prev_x + prev_y) * sin(0.523599) + SCREEN_SIZE_Y / 2;
	(*line)->color_end = 0x0000FF;
}

void	project(t_point *begin, t_point *end, t_window *win, t_line *line)
{
//	(void)win;

	iso(begin ,end, &line, win->coef);
//	printf("begin coords:\t%d\t%d\t%d\nend coords:\t%d\t%d\t%d\n", begin->x,
//	begin->y, begin->z, end->x, end->y, end->z);
//	printf("\nTranformed:\t%d\t%d\n\t\t%d\t%d\n", line->x1, line->y1, line->x2, line->y2);
}