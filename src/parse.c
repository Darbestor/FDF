/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 11:54:11 by ghalvors          #+#    #+#             */
/*   Updated: 2019/01/22 14:21:43 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../Libft/libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

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

int		parse_color(char *str)
{
	int	i;
	int	val;
	int	base;

	val = 0;
	base = 1;
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
	{
		i = 2;
		while (str[i] && i < 8)
		{
			if (str[i] >= '0' && str[i] <= '9')
				val += (str[i] - '0') * base;
			else if (str[i] >= 'A' && str[i] <= 'F')
				val += (str[i] - 55) * base;
			else if (str[i] >= 'a' && str[i] <= 'f')
				val += (str[i] - 87) * base;
			else
				break;
			i++;
			base *= 16;
		}
	}
	if (!val || str[i])
		return (-1);
	return (val);
}

void	fill_point(t_point **point, char **split, int line, t_window *win)
{
	int		i;
	char	*str;

	i = -1;
	while (++i < win->map_width)
	{
		(*point)->x = i;
		(*point)->y = line;
		if (((*point)->z = ft_atoi(split[i])) > win->max_h)
			win->max_h = (*point)->z;
		else if ((*point)->z < win->min_h)
			win->min_h = (*point)->z;
		if ((str = ft_strstr(split[i], ",")))
			(*point)->color = parse_color(str + 1);
		else
			(*point)->color = -1;
		(*point)++;
	}
}

t_point	*create_map(char *file, t_window *win)
{
	t_point	*point;
	char	*str;
	char	**split;
	int		fd;
	int		line;

	fd = open(file, O_RDONLY);
	if (fd <= 0 || !(point = ft_memalloc(sizeof(t_point) * (win->map_height * win->map_width))))
		return (NULL);
	line = 0;
	while (get_next_line(fd, &str))
	{
		if (!(split = ft_strsplit(str, ' ')))
			return (NULL);
		fill_point(&point, split, line++, win);
		ft_arrdel(split, win->map_width);
		ft_strdel(&str);
	}
	close(fd);
	return (point - (win->map_height * win->map_width));
}

int		check_map(int fd, int *width, int *height)
{
	char **split;
	char *string;

	if (get_next_line(fd, &string) == -1 || check_err(string))
		return (0);
	split = ft_strsplit(string, ' ');
	*width = ft_count_words((const char**)split);
	*height = 1;
	ft_arrdel(split, *width);
	ft_strdel(&string);
	while (get_next_line(fd, &string))
	{
		if (check_err(string) || !(split = ft_strsplit(string, ' ')))
			return (0);
		if (*width != ft_count_words((const char**)split))
			return (0);
		ft_arrdel(split, *width);
		ft_strdel(&string);
		(*height)++;
	}
	return (1);
}

int		read_map(int argc, char **argv, int *map_height, int *map_width)
{
	int		fd;
	int		width;
	int		height;

	if (argc != 2 || !(fd = open(argv[1], O_RDONLY)))
		return (0);
	if (!check_map(fd, &width, &height))
		return (0);
	close(fd);
	*map_height = height;
	*map_width = width;
	return (1);
}
