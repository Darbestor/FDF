/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 11:54:11 by ghalvors          #+#    #+#             */
/*   Updated: 2019/01/26 20:15:52 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../Libft/libft.h"
#include <unistd.h>
#include <fcntl.h>

void	fill_point(t_point **point, char **split, int line, t_window *win)
{
	int		i;

	i = -1;
	while (++i < win->map_w)
	{
		(*point)->x = i;
		(*point)->y = line;
		if (((*point)->z = ft_atoi(split[i])) > win->max_h)
			win->max_h = (*point)->z;
		else if ((*point)->z < win->min_h)
			win->min_h = (*point)->z;
		(*point)++;
	}
}

int		create_map(char *file, t_window *win)
{
	t_point	*map;
	char	*str;
	char	**split;
	int		fd;
	int		line;

	fd = open(file, O_RDONLY);
	if (!(map = ft_memalloc(sizeof(t_point) * win->map_h * win->map_w)))
		return (1);
	line = 0;
	win->init_map = map;
	if (!(win->cur_map = ft_memalloc(sizeof(t_point) * win->map_h *
	win->map_w)))
		return (1);
	while (get_next_line(fd, &str) > 0)
	{
		if (!(split = ft_strsplit(str, ' ')))
			return (1);
		fill_point(&map, split, line++, win);
		ft_arrdel(split, win->map_w);
		ft_strdel(&str);
	}
	ft_memcpy(win->cur_map, win->init_map,
	sizeof(t_point) * win->map_h * win->map_w);
	return (close(fd) ? 2 : 0);
}

int		check_err(char *s)
{
	int i;

	i = -1;
	while (s[++i])
		if (s[i] != ' ' && !(s[i] >= '0' && s[i] <= '9'))
		{
			if ((s[i] == '-' || s[i] == '+') && s[i + 1] &&
			(s[i + 1] >= '0' && s[i + 1] <= '9'))
			{
				i++;
				continue;
			}
			if (i && (s[i - 1] >= '0' && s[i - 1] <= '9') && s[i] == ',')
			{
				while (s[i] != ' ' && s[i + 1])
					i++;
				continue;
			}
			return (1);
		}
	return (0);
}

int		check_map(int fd, int *width, int *height)
{
	char **split;
	char *string;

	if (get_next_line(fd, &string) != 1)
		return (2);
	if (check_err(string))
		return (4);
	if (!(split = ft_strsplit(string, ' ')))
		return (1);
	*width = ft_count_words((const char**)split);
	*height = 1;
	ft_arrdel(split, *width);
	ft_strdel(&string);
	while (get_next_line(fd, &string) > 0)
	{
		if (!(split = ft_strsplit(string, ' ')))
			return (1);
		if (check_err(string) ||
		(*width != ft_count_words((const char**)split)))
			return (4);
		ft_arrdel(split, *width);
		ft_strdel(&string);
		(*height)++;
	}
	return (0);
}

int		read_map(int argc, char **argv, int *map_h, int *map_w)
{
	int		fd;
	int		err;

	if (argc != 2)
		return (3);
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (2);
	if ((err = check_map(fd, map_w, map_h)))
		return (err);
	close(fd);
	return (0);
}
