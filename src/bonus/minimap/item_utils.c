/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:52:15 by ana-cast          #+#    #+#             */
/*   Updated: 2025/05/27 16:09:18 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>
#include <stdlib.h>
#include <math.h>

void	clear_map_items(t_mini_item **lst)
{
	t_mini_item	*current;

	current = *lst;
	while (current)
	{
		*lst = current->next;
		free(current);
		current = *lst;
	}
}

t_mini_item	*last_mini_item(t_mini_item *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_minimap_items(t_game *g, t_mini_item **map_items, double *rel_pos)
{
	t_mini_item	*new_item;
	t_mini_item	*last_item;

	new_item = (t_mini_item *)malloc(sizeof(t_mini_item));
	if (!new_item)
		error_exit(g, E_MEM_ALLOC, "minimap item list");
	new_item->rel_x = rel_pos[0];
	new_item->rel_y = rel_pos[1];
	new_item->next = NULL;
	if (!(*map_items))
		*map_items = new_item;
	else
	{
		last_item = last_mini_item(*map_items);
		last_item->next = new_item;
	}
}

void	draw_items(t_game *game, t_mini_item *map_items)
{
	double	pos[2];
	int		i;

	if (!map_items)
		return ;
	i = 0;
	while (map_items && ++i)
	{
		pos[0] = 120 + map_items->rel_x * TILE_SIZE;
		pos[1] = 120 + map_items->rel_y * TILE_SIZE;
		if (sqrt(pow(120 - pos[0], 2) + pow(120 - pos[1], 2)) <= 5
			* TILE_SIZE - 5)
		{
			pos[0] -= fmod(game->player.x * TILE_SIZE, TILE_SIZE) - 10;
			pos[1] -= fmod(game->player.y * TILE_SIZE, TILE_SIZE) - 10;
			draw_circle(game->graphics->img, pos, 0, U_PINK, 5);
		}
		map_items = map_items->next;
	}
}
