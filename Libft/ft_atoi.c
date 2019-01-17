/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 14:38:38 by ghalvors          #+#    #+#             */
/*   Updated: 2018/12/29 17:05:21 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long long	nb;
	int			sign;

	sign = 1;
	nb = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v' ||
		*str == '\r' || *str == '\f')
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	while (*str >= '0' && *str <= '9')
	{
		nb *= 10;
		nb += *str++ - '0';
		if (nb < 0)
		{
			if (sign == -1)
				return (0);
			return (-1);
		}
	}
	return (nb * sign);
}
