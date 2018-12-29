/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 17:41:42 by ghalvors          #+#    #+#             */
/*   Updated: 2018/12/11 14:13:43 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char *last;

	last = NULL;
	c = (char)c;
	while (*s)
	{
		if (*s == c)
			last = s;
		s++;
	}
	if (*s == c)
		return ((char*)s);
	return ((char*)last);
}
