/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 15:19:00 by ghalvors          #+#    #+#             */
/*   Updated: 2018/12/05 16:25:52 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*lst;

	lst = malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->next = NULL;
	if (!content)
	{
		lst->content = NULL;
		lst->content_size = 0;
		return (lst);
	}
	lst->content_size = content_size;
	lst->content = ft_strnew(content_size);
	if (!lst->content)
	{
		free(&lst);
		return (NULL);
	}
	ft_strncpy(lst->content, content, content_size);
	return (lst);
}
