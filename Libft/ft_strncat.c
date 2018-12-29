/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 17:51:40 by ghalvors          #+#    #+#             */
/*   Updated: 2018/12/11 14:13:09 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*temp;

	temp = s1;
	s1 += ft_strlen(s1);
	while (*s2 && n)
	{
		*s1++ = *s2++;
		n--;
	}
	*s1 = 0;
	return (temp);
}
