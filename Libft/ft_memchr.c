/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 17:22:43 by ghalvors          #+#    #+#             */
/*   Updated: 2018/12/11 14:05:59 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	c = (unsigned char)c;
	while (n--)
		if (*(unsigned char*)s++ == c)
			return ((unsigned char*)s - 1);
	return (NULL);
}
