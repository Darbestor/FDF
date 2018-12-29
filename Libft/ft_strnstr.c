/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 14:40:09 by ghalvors          #+#    #+#             */
/*   Updated: 2018/12/11 14:58:55 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t ind;
	size_t ind2;

	if (!*needle)
		return ((char*)haystack);
	while (*haystack && len)
	{
		ind = 0;
		ind2 = 0;
		if (*haystack++ == needle[ind++])
		{
			while (*(haystack + ind2) == needle[ind] && needle[ind] && len)
			{
				ind++;
				ind2++;
				len--;
			}
			if (!needle[ind])
				return ((char*)haystack - 1);
			len += ind2;
		}
		len--;
	}
	return (NULL);
}
