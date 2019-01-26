/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 19:41:34 by ghalvors          #+#    #+#             */
/*   Updated: 2019/01/26 19:56:22 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	zoom_map(int keycode, t_window *win)
{
	if (keycode == 69)
	{
		if (win->coef / 0.9 < 2147483647)
			win->coef /= 0.9;
	}
	else
	{
		if (win->coef * 0.9 > 0.000001)
			win->coef *= 0.9;
	}
	if (win->line->x1 * win->coef < 2147483647)
	{
		construct_lines(win);
		render(win);
	}
}

void	wheel_zoom(int button, t_window *win)
{
	if (win->ctrl)
	{
		rotate_speed(button, win);
		return ;
	}
	if (button == 4)
	{
		if (win->coef * 0.9 < 2147483647)
			win->coef *= 0.9;
	}
	else
	{
		if (win->coef / 0.9 > 0.000001)
			win->coef /= 0.9;
	}
	if (win->line->x1 * win->coef < 2147483647)
	{
		construct_lines(win);
		render(win);
	}
}
