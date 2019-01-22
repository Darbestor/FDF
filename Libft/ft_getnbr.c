/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 13:03:41 by ghalvors          #+#    #+#             */
/*   Updated: 2019/01/22 13:05:33 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_getnbr(char **str)
{
	long long	nb;
	int			sign;

	sign = 1;
	nb = 0;
	while (**str == ' ' || **str == '\t' || **str == '\n' || **str == '\v' ||
		**str == '\r' || **str == '\f')
		str++;
	if (**str == '-' || **str == '+')
		if ((**str)++ == '-')
			sign = -1;
	while (**str >= '0' && **str <= '9')
	{
		nb *= 10;
		nb += (**str)++ - '0';
		if (nb < 0)
		{
			if (sign == -1)
				return (0);
			return (-1);
		}
	}
	return (nb * sign);
}