/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 11:54:11 by ghalvors          #+#    #+#             */
/*   Updated: 2019/01/19 21:30:45 by ghalvors         ###   ########.fr       */
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

void	fill_coord(t_point **point, char **split, int line, int width)
{
	int i;

	i = -1;
	while (++i < width)
	{
		(*point)->x = i;
		(*point)->y = line;
		(*point)->z = ft_atoi(split[i]);
		(*point)++;
	}
}

t_point	*create_map(char *file, int height, int width)
{
	t_point	*point;
	char	*str;
	char	**split;
	int		fd;
	int		line;

	fd = open(file, O_RDONLY);
	point = ft_memalloc(sizeof(t_point) * (height * width));
	if (fd <= 0 || !(point))
		return (NULL);
	line = 0;
	while (get_next_line(fd, &str))
	{
		if (!(split = ft_strsplit(str, ' ')))
			return (NULL);
		fill_coord(&point, split, line++, width);
		ft_arrdel(split, width);
		ft_strdel(&str);
	}
	close(fd);
	return (point - (height * width));
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
		if (check_err(string))
			return (0);
		split = ft_strsplit(string, ' ');
		if (*width != ft_count_words((const char**)split))
			return (0);
		ft_arrdel(split, *width);
		ft_strdel(&string);
		(*height)++;
	}
	return (1);
}

int		read_map(int argc, char **argv)
{
	int		fd;
	int		width;
	int		height;
	t_point	*map;
	int		i;

	if (argc != 2 || !(fd = open(argv[1], O_RDONLY)))
		return (0);
	if (!check_map(fd, &width, &height))
		return (0);
	close(fd);
	if (!(map = create_map(argv[1], height, width)))
		return (0);
	i = 0;
	while (i < width * height)
	{
		printf("%d\t%d\t%d\n", map[i].x, map[i].y, map[i].z);
		i++;
	}
	return (1);
}
