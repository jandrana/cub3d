/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:25:38 by ana-cast          #+#    #+#             */
/*   Updated: 2025/05/27 18:42:25 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "init.h"
#include <cub3d_bonus.h>
#include <stdlib.h>

static void	init_map_bonus(t_game *game)
{
	game->map->items = NULL;
	game->map->n_items = 0;
	game->map->n_collected = 0;
}

static void	init_graphics_bonus(t_game *game)
{
	// add check if game graphics exists
	game->graphics->minimap = NULL;
	game->graphics->door_lst[0] = NULL;
	game->graphics->door_lst[1] = NULL;
	game->graphics->door_lst[2] = NULL;
	game->graphics->door_lst[3] = NULL;
	game->graphics->items_lst[0] = NULL;
	game->graphics->items_lst[1] = NULL;
	game->graphics->items_lst[2] = NULL;
	game->graphics->items_lst[3] = NULL;
	game->graphics->items_lst[4] = NULL;
	game->graphics->items_lst[6] = NULL;
	game->graphics->items_lst[7] = NULL;
	game->graphics->items_lst[8] = NULL;
	game->graphics->skip_item = false;
}

t_game	*init_game_bonus(void)
{
	t_game	*game;

	game = init_game_core();
	game->item_sprite_n = 0;
	game->cursor_locked = true;
	game->player.sprite_frame = 0; // check
	init_map_bonus(game);
	init_graphics_bonus(game);
	return (game);
}
