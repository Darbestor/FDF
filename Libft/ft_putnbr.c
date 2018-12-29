/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 13:45:33 by ghalvors          #+#    #+#             */
/*   Updated: 2018/11/22 18:30:41 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_find_pow10(int n)
{
	int i;

	i = 1;
	while (n > 9 || n < -9)
	{
		n /= 10;
		i *= 10;
	}
	return (i);
}

void		ft_putnbr(int n)
{
	int pow10;
	int digit;

	pow10 = ft_find_pow10(n);
	if (n < 0)
	{
		ft_putchar('-');
		digit = n / pow10;
		ft_putchar('0' + digit * -1);
		n %= pow10;
		n *= -1;
		pow10 /= 10;
	}
	while (pow10)
	{
		digit = n / pow10;
		ft_putchar('0' + digit);
		n %= pow10;
		pow10 /= 10;
	}
}
