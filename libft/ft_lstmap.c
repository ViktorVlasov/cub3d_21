/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 21:58:52 by efumiko           #+#    #+#             */
/*   Updated: 2020/05/24 10:33:58 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *head;
	t_list *node;

	if (!lst || !f || !del)
		return (NULL);
	if (!(node = ft_lstnew(f(lst->content))))
		return (NULL);
	head = node;
	lst = lst->next;
	while (lst)
	{
		node = ft_lstnew(f(lst->content));
		if (node)
		{
			ft_lstadd_back(&head, node);
			lst = lst->next;
		}
		else
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
	}
	return (head);
}
