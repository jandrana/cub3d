/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hlst_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:46:41 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/11 17:47:07 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include <stdlib.h>

t_hlist	*hslt_new_node(void *content, t_hlist *head)
{
	t_hlist	*node;

	if (!content)
		return (NULL);
	node = (t_hlist *)malloc(sizeof(t_hlist));
	if (!node)
		return (NULL);
	node->content = content;
	if (!head)
		node->head = node;
	else
		node->head = head;
	node->next = NULL;
	return (node);
}

t_hlist	*hlst_last_node(t_hlist *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	hlstadd_back(t_hlist **lst, t_hlist *node)
{
	t_hlist	*last;

	if (!node)
		return ;
	if (!(*lst))
	{
		*lst = node;
		node->head = node;
	}
	else
	{
		last = hlst_last_node(*lst);
		if (last)
		{
			node->head = *lst;
			last->next = node;
		}
	}
}
