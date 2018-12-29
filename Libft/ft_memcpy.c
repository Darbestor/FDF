/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 16:53:39 by ghalvors          #+#    #+#             */
/*   Updated: 2018/12/11 14:10:18 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*temp;

	temp = (unsigned char*)dst;
	if (dst == src)
		return (temp);
	while (n--)
		*(unsigned char*)dst++ = *(unsigned char*)src++;
	return (temp);
}
