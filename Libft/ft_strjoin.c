/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 19:45:10 by ghalvors          #+#    #+#             */
/*   Updated: 2018/12/11 14:12:05 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *conc;

	if (!s1 || !s2)
		return (NULL);
	conc = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	if (!conc)
		return (NULL);
	ft_strcat(conc, s1);
	ft_strcat(conc, s2);
	return (conc);
}
