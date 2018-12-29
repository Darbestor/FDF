/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 14:35:50 by ghalvors          #+#    #+#             */
/*   Updated: 2018/11/24 15:45:07 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	char *temp;

	temp = dst;
	while (*src && len)
	{
		len--;
		*dst++ = *src++;
	}
	while (len)
	{
		len--;
		*dst++ = 0;
	}
	return (temp);
}
