/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 12:12:42 by ghalvors          #+#    #+#             */
/*   Updated: 2019/01/26 20:01:14 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap(void *var1, void *var2, size_t n)
{
	unsigned char	*temp;

	temp = ft_memalloc(n);
	ft_memcpy(temp, var1, n);
	ft_memcpy(var1, var2, n);
	ft_memcpy(var2, temp, n);
	ft_memdel((void**)&temp);
}
