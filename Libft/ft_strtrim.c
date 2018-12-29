/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 19:56:13 by ghalvors          #+#    #+#             */
/*   Updated: 2018/12/11 14:32:18 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	const char	*begin;
	const char	*end;

	if (!s)
		return (NULL);
	begin = s;
	end = s + ft_strlen(s) - 1;
	while (*begin == ' ' || *begin == ',' || *begin == '\n' ||
	*begin == '\t')
		begin++;
	if (!*begin)
		return (ft_strnew(ft_strlen(s)));
	while (*end == ' ' || *end == ',' || *end == '\n' || *end == '\t')
		end--;
	return (ft_strsub(s, begin - s, end - begin + 1));
}
