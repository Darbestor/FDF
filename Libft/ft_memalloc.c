/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 18:50:15 by ghalvors          #+#    #+#             */
/*   Updated: 2018/12/11 16:07:12 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	char	*mem;
	char	*temp;

	mem = (char*)malloc(sizeof(char) * size);
	if (!mem)
		return (NULL);
	temp = mem;
	while (size)
	{
		*mem++ = 0;
		size--;
	}
	return (temp);
}
