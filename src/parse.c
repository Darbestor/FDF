/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 11:54:11 by ghalvors          #+#    #+#             */
/*   Updated: 2019/01/24 17:03:15 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../Libft/libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <math.h>

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

int		parse_color(char *str, int color)
{
	int	i;
	int	val;
	int	decimal;
	int	len;

	decimal = 0;
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
	{
		i = 2;
		len = ft_strlen(str + 2) - 1;
		while (str[i] && len < 6)
		{
			if (str[i] >= '0' && str[i] <= '9')
				val = str[i] - '0';
			else if (str[i] >= 'A' && str[i] <= 'F')
				val = str[i] - 55;
			else if (str[i] >= 'a' && str[i] <= 'f')
				val = str[i] - 87;
			else
				break;
			i++;
			decimal += val * pow(16, len--);
		}
	}
	if (!decimal || str[i])
		return (color);
	return (decimal);
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
			(*point)->color = parse_color(str + 1, (int)win->color);
		else
			(*point)->color = (int)win->color;
		(*point)++;
	}
}

int		create_map(char *file, t_window *win)
{
	t_point	*point;
	char	*str;
	char	**split;
	int		fd;
	int		line;

	fd = open(file, O_RDONLY);
	if (fd <= 0 || !(point = ft_memalloc(sizeof(t_point) * (win->map_height * win->map_width))))
		return (0);
	line = 0;
	win->points_map = point;
	if (!(win->cur_map = ft_memalloc(sizeof(t_point) * (win->map_height * win->map_width))))
		return (0);
	while (get_next_line(fd, &str))
	{
		if (!(split = ft_strsplit(str, ' ')))
			return (0);
		fill_point(&point, split, line++, win);
		ft_arrdel(split, win->map_width);
		ft_strdel(&str);
	}
	ft_memcpy(win->cur_map, win->points_map, sizeof(t_point) * (win->map_height * win->map_width));
	close(fd);
	return (1);
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
