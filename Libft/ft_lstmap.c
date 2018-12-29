/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 12:48:26 by ghalvors          #+#    #+#             */
/*   Updated: 2018/12/11 14:05:27 by ghalvors         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	ft_del(void *content, size_t content_size)
{
	free(content);
	content_size = 0;
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*current;
	t_list	*temp;

	temp = NULL;
	while (lst && f)
	{
		if (!temp && f(lst))
		{
			current = ft_lstnew(f(lst)->content, f(lst)->content_size);
			temp = current;
		}
		else if (f(lst))
		{
			if (!(current->next = ft_lstnew(f(lst)->content,
			f(lst)->content_size)))
			{
				ft_lstdel(&temp, ft_del);
				return (NULL);
			}
			current = current->next;
		}
		lst = lst->next;
	}
	return (temp);
}
