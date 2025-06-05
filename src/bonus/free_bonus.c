/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:59:21 by ana-cast          #+#    #+#             */
/*   Updated: 2025/05/27 19:41:27 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "MLX42/MLX42.h"

static void	free_bonus_graphics(t_game *game)
{
	t_graphics	*graphics;

	if (!game->graphics)
		return ;
	graphics = game->graphics;
	free_hlist(graphics->door_lst, delete_texture);
	free_hlist(graphics->items_lst, delete_texture);
	if (graphics->minimap)
		mlx_delete_image(graphics->mlx, graphics->minimap);
	if (graphics->mlx)
		mlx_terminate(game->graphics->mlx);
}

static void	free_bonus_map(t_game *game)
{
	t_map	*map;

	if (!game->map)
		return ;
	map = game->map;
	safe_free(map->items);
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	free_core_game(game);
	free_bonus_map(game);
	free_bonus_graphics(game);
	safe_free(game->map);
	safe_free(game->graphics);
	safe_free(game);
}
