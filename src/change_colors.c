/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 19:43:07 by ghalvors          #+#    #+#             */
/*   Updated: 2019/01/26 19:50:38 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	change_line_color(t_window *win)
{
	if (win->color == RED)
		win->color = GREEN;
	else if (win->color == GREEN)
		win->color = BLUE;
	else if (win->color == BLUE)
		win->color = RED;
	render(win);
}

void	change_background(t_window *win)
{
	if (win->bg == BLACK)
		win->bg = YELLOW;
	else if (win->bg == YELLOW)
		win->bg = WHITE;
	else if (win->bg == WHITE)
		win->bg = BLACK;
	render(win);
}
