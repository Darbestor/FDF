/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 19:59:14 by ghalvors          #+#    #+#             */
/*   Updated: 2018/12/05 15:12:34 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str_new;
	size_t			len;
	unsigned int	ind;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	ind = -1;
	str_new = ft_strnew(len);
	if (!str_new)
		return (NULL);
	while (s[++ind])
		str_new[ind] = f(ind, s[ind]);
	str_new[ind] = 0;
	return (str_new);
}
