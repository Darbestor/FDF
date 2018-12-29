/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 13:38:46 by ghalvors          #+#    #+#             */
/*   Updated: 2018/12/11 14:07:46 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_find_size(int n)
{
	int i;

	i = 1;
	while (n > 9 || n < -9)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*ft_strrev(char *str, int size)
{
	char *first;
	char *last;
	char buffer;

	first = str;
	last = str + size - 1;
	while (first < last)
	{
		buffer = *first;
		*first++ = *last;
		*last-- = buffer;
	}
	return (str);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		size;
	int		size_temp;

	size = ft_find_size(n);
	if (n < 0)
		size += 1;
	size_temp = size;
	str = ft_strnew(size);
	if (!str)
		return (NULL);
	while (size--)
	{
		if (n < 0)
			*str++ = '0' + (n % 10) * -1;
		else
			*str++ = '0' + n % 10;
		n /= 10;
		if (!n && size)
		{
			*str++ = '-';
			size--;
		}
	}
	return (ft_strrev(str - size_temp, size_temp));
}
