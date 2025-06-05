/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:25:38 by ana-cast          #+#    #+#             */
/*   Updated: 2025/05/29 20:57:39 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "macros.h"
#include "parser.h"
#include <stdlib.h>

#ifdef BONUS
# include "cub3d_bonus.h"
#else
# include "cub3d.h"
#endif

static void	init_map(t_game *game)
{
	unsigned long	alloc_size;

	alloc_size = sizeof(t_map);
	game->map = safe_calloc(1, alloc_size, game, "map");
	game->map->rows = 0;
	game->map->cols = 0;
	game->map->mt = NULL;
	game->player.x = -1;
	game->player.y = -1;
	game->player.angle = 0;
	game->map->floor_color = (t_color){0, 0, 0, 0};
	game->map->ceiling_color = (t_color){0, 0, 0, 0};
}

static void	init_graphics(t_game *game)
{
	unsigned long	alloc_size;

	alloc_size = sizeof(t_graphics);
	game->graphics = safe_calloc(1, alloc_size, game, "graphics");
	game->graphics->mlx = NULL;
	game->graphics->img = NULL;
	game->graphics->fps = NULL;
	game->graphics->textures_lst[NORTH] = NULL;
	game->graphics->textures_lst[SOUTH] = NULL;
	game->graphics->textures_lst[EAST] = NULL;
	game->graphics->textures_lst[WEST] = NULL;
}

static void	init_parser_state(t_game *game)
{
	unsigned long	alloc_size;

	alloc_size = sizeof(t_parser_state);
	game->parser_state = safe_calloc(1, alloc_size, game, "parser state");
	game->parser_state->textures[NORTH] = false;
	game->parser_state->textures[SOUTH] = false;
	game->parser_state->textures[EAST] = false;
	game->parser_state->textures[WEST] = false;
	game->parser_state->free_line = NULL;
	game->parser_state->floor_color = false;
	game->parser_state->ceiling_color = false;
}

t_game	*init_game_core(void)
{
	t_game			*game;
	unsigned long	alloc_size;

	alloc_size = sizeof(t_game);
	game = safe_calloc(1, alloc_size, NULL, "game");
	game->map = NULL;
	game->graphics = NULL;
	game->parser_state = NULL;
	game->parser_temp = NULL;
	game->fps = INITIAL_FPS;
	game->frames = 0;
	init_parser_state(game);
	init_graphics(game);
	init_map(game);
	return (game);
}
