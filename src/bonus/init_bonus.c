/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:25:38 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/18 15:53:52 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>
#include <types.h>
#include <stdlib.h>

static void	init_map_bonus(t_game *game)
{
	game->map->items = NULL;
	game->map->n_items = 0;
	game->map->n_collected = 0;
	game->map->time_end = -1;
}

static void	init_graphics_bonus(t_game *game)
{
	int	i;

	game->graphics->minimap = NULL;
	game->graphics->items_img = NULL;
	i = -1;
	while (++i < 4)
		game->graphics->door_lst[i] = NULL;
	i = -1;
	while (++i < 9)
		game->graphics->items_lst[i] = NULL;
}

t_game	*init_game_bonus(void)
{
	t_game	*game;

	game = init_game_core();
	game->item_sprite_n = 0;
	game->cursor_locked = true;
	game->player.sprite_frame = 0;
	game->door_texture = false;
	game->item_texture = false;
	init_map_bonus(game);
	init_graphics_bonus(game);
	return (game);
}
