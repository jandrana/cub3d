/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:25:38 by ana-cast          #+#    #+#             */
/*   Updated: 2025/02/21 16:58:39 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include <cub3d.h>
#include <stdlib.h>

static void	init_map(t_game *game)
{
	game->map = (t_map*)malloc(sizeof(t_map));
	if (!game->map)
		error_exit(game, E_MEM_ALLOC, "map structure");
	game->map->rows = 0;
	game->map->cols = 0;
	game->map->mt = NULL;
	game->map->player = (t_player){0, 0, 0, 0};
	game->map->floor_color = (t_color){0, 0, 0};
	game->map->ceiling_color = (t_color){0, 0, 0};
}

static void	init_graphics(t_game *game)
{
	game->graphics = (t_graphics *)malloc(sizeof(t_graphics));
	if (!game->graphics)
		error_exit(game, E_MEM_ALLOC, "graphics structure");
	game->graphics->mlx = NULL;
	game->graphics->img = NULL;
	game->graphics->textures[NORTH] = NULL;
	game->graphics->textures[SOUTH] = NULL;
	game->graphics->textures[EAST] = NULL;
	game->graphics->textures[WEST] = NULL;
}

static void	init_parser_state(t_game *game)
{
	game->parser_state = (t_parser_state*)malloc(sizeof(t_parser_state));
	if (!game->parser_state)
		error_exit(game, E_MEM_ALLOC, "parser state structure");
	game->parser_state->textures[NORTH] = NULL;
	game->parser_state->textures[SOUTH] = NULL;
	game->parser_state->textures[EAST] = NULL;
	game->parser_state->textures[WEST] = NULL;
	game->parser_state->floor_color = NULL;
	game->parser_state->ceiling_color = NULL;
}

t_game	*init_game(void)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		error_exit(NULL, E_MEM_ALLOC, "game structure");
	game->map = NULL;
	game->graphics = NULL;
	game->parser_state = NULL;
	init_map(game);
	init_graphics(game);
	init_parser_state(game);
	return (game);
}
