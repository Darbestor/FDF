/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 17:54:40 by ghalvors          #+#    #+#             */
/*   Updated: 2018/12/11 17:13:44 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t len;
	size_t space;

	len = 0;
	while (dst[len] && (len++ <= size))
		;
	if (len >= size)
		return (size + ft_strlen(src));
	len = ft_strlen(dst) + ft_strlen(src);
	space = size - ft_strlen(dst) - 1;
	dst += ft_strlen(dst);
	while (*src && space)
	{
		*dst++ = *src++;
		space--;
	}
	*dst = 0;
	return (len);
}
