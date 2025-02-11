/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 20:57:02 by ana-cast          #+#    #+#             */
/*   Updated: 2025/02/11 18:51:32 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstadd_back(t_list **lst, t_list *node)
{
	t_list	*last;

	if (!(*lst))
		*lst = node;
	else
	{
		last = ft_lstlast(*lst);
		last->next = node;
	}
}
