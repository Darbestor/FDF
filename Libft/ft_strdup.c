/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 13:36:47 by ghalvors          #+#    #+#             */
/*   Updated: 2018/11/23 13:52:28 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*dup;

	size = ft_strlen(s1);
	dup = ft_strnew(size);
	if (!dup)
		return (NULL);
	return (ft_strcpy(dup, s1));
}
