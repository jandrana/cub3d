/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:25:38 by ana-cast          #+#    #+#             */
/*   Updated: 2025/02/18 13:44:11 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_game	*init_game(void)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		error_exit(NULL, E_MEM_ALLOC, "game structure");
	game->map = NULL;
	game->graphics = NULL;
	game->map = (t_map *)malloc(sizeof(t_map));
	if (!game->map)
		error_exit(game, E_MEM_ALLOC, "map structure");
	game->map->rows = 0;
	game->map->cols = 0;
	game->map->player = (t_player){0, 0, 0, 0};
	game->map->floor_color = (t_color){0, 0, 0};
	game->map->ceiling_color = (t_color){0, 0, 0};
	game->graphics = (t_graphics *)malloc(sizeof(t_graphics));
	if (!game->graphics)
		error_exit(game, E_MEM_ALLOC, "graphics structure");
	game->graphics->mlx = NULL;
	game->graphics->img = NULL;
	game->graphics->textures[NORTH] = NULL;
	game->graphics->textures[SOUTH] = NULL;
	game->graphics->textures[EAST] = NULL;
	game->graphics->textures[WEST] = NULL;
	return (game);
}
