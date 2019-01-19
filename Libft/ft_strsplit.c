/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 20:38:22 by ghalvors          #+#    #+#             */
/*   Updated: 2019/01/19 18:25:24 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_wordlen(char const *s, char *c)
{
	size_t	size;

	size = 0;
	while (s[size] != *c && s[size])
		size++;
	return (size);
}

static char		**ft_strarr(char const *s, char *c, size_t *size)
{
	char	**arr;
	size_t	i;
	int		flag;

	*size = 0;
	i = 0;
	while (s[i])
	{
		flag = 0;
		while (s[i] == *c)
			i++;
		while (s[i] != *c && s[i])
		{
			flag = 1;
			i++;
		}
		if (flag)
			*size += 1;
	}
	arr = (char**)malloc(sizeof(char*) * (*size) + 1);
	if (!arr)
		return (NULL);
	return (arr);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**strarr;
	char	**temp;
	size_t	size_of_arr;
	size_t	i;

	if (!s)
		return (NULL);
	strarr = ft_strarr(s, &c, &size_of_arr);
	temp = strarr;
	while (*s && strarr)
	{
		while (*s == c)
			s++;
		*strarr = ft_strnew(ft_wordlen(s, &c));
		if (!*strarr)
			return (ft_arrdel(temp, size_of_arr));
		i = 0;
		while ((*s != c) && *s)
			(*strarr)[i++] = *s++;
		if (size_of_arr--)
			strarr++;
	}
	if (strarr)
		*strarr = NULL;
	return (temp);
}
