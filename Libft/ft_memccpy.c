/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 16:00:14 by ghalvors          #+#    #+#             */
/*   Updated: 2018/12/11 15:21:06 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	while (n)
	{
		*(unsigned char*)dst = *(unsigned char*)src;
		if (*(unsigned char*)src == (unsigned char)c)
			return ((unsigned char*)dst + 1);
		src++;
		dst++;
		n--;
	}
	return (NULL);
}
