/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 13:13:01 by ghalvors          #+#    #+#             */
/*   Updated: 2018/12/05 15:11:24 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *substr;

	if (!s)
		return (NULL);
	substr = ft_strnew(len);
	if (!substr)
		return (NULL);
	ft_strncpy(substr, s + start, len);
	return (substr);
}
