/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 16:38:36 by ghalvors          #+#    #+#             */
/*   Updated: 2018/12/11 14:11:28 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char *temp;

	temp = (unsigned char*)dst;
	if (dst == src)
		return (temp);
	if ((unsigned char*)src > (unsigned char*)dst)
		while (len)
		{
			*(unsigned char*)dst++ = *(unsigned char*)src++;
			len--;
		}
	else if ((unsigned char*)src < (unsigned char*)dst)
		while (len--)
		{
			*(unsigned char*)(dst + len) = *(unsigned char*)(src + len);
		}
	return (temp);
}
