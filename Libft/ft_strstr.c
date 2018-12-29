/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 13:18:43 by ghalvors          #+#    #+#             */
/*   Updated: 2018/11/24 13:59:09 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t ind;
	size_t ind2;

	if (!*needle)
		return ((char*)haystack);
	while (*haystack)
	{
		ind = 0;
		ind2 = 0;
		if (*haystack++ == needle[ind++])
		{
			while (*(haystack + ind2) == needle[ind] && needle[ind])
			{
				ind2++;
				ind++;
			}
			if (!needle[ind])
				return ((char*)haystack - 1);
		}
	}
	return (NULL);
}
