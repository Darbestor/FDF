/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 16:26:29 by ghalvors          #+#    #+#             */
/*   Updated: 2018/12/11 14:04:56 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdelone(t_list **alst, void (*del)(void*, size_t))
{
	if (!*alst || !alst)
		return ;
	if (*alst != (*alst)->next)
	{
		if (del)
			del((*alst)->content, (*alst)->content_size);
		free(*alst);
		*alst = NULL;
	}
}
