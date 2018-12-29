/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 19:29:24 by ghalvors          #+#    #+#             */
/*   Updated: 2018/12/05 15:12:45 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*str_new;
	char	*temp;
	size_t	len;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	str_new = ft_strnew(len);
	temp = str_new;
	if (!str_new)
		return (NULL);
	while (*s)
		*str_new++ = f(*s++);
	*str_new = 0;
	return (temp);
}
