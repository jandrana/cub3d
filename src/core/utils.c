/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:02:43 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/18 19:14:25 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include "MLX42/MLX42.h"
#include "types.h"

void	*safe_calloc(size_t count, size_t size, void *free_exit, char *type)
{
	void	*ptr;

	ptr = ft_calloc(count, size);
	if (!ptr)
		error_exit(free_exit, E_MEM_ALLOC, type);
	return (ptr);
}

void	safe_free(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
}

void	delete_texture(void *texture)
{
	mlx_delete_texture((mlx_texture_t *)texture);
}

void	free_hlist(t_hlist **lst, void (*del)(void *))
{
	t_hlist	*node;

	node = (*lst)->head;
	while (node)
	{
		*lst = node->next;
		(*del)(node->content);
		free(node);
		node = *lst;
	}
}
