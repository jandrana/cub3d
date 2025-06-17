/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:25:38 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/13 20:30:42 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "init.h"
#include "error.h"
#include "macros.h"
#include <stdlib.h>

static void	init_map(t_game *game)
{
	game->map = safe_calloc(1, sizeof(t_map), game, "map");
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
	game->graphics = safe_calloc(1, sizeof(t_graphics), game, "graphics");
	game->graphics->mlx = NULL;
	game->graphics->img = NULL;
	game->graphics->fps = NULL;
	game->graphics->textures_lst[NORTH] = NULL;
	game->graphics->textures_lst[SOUTH] = NULL;
	game->graphics->textures_lst[EAST] = NULL;
	game->graphics->textures_lst[WEST] = NULL;
}

static void	init_parser(t_game *game)
{
	game->parser = safe_calloc(1, sizeof(t_parser), game, "parser structure");
	game->parser->textures[NORTH] = false;
	game->parser->textures[SOUTH] = false;
	game->parser->textures[EAST] = false;
	game->parser->textures[WEST] = false;
	game->parser->floor_color = false;
	game->parser->ceiling_color = false;
	game->parser->line = NULL;
	game->parser->element = NULL;
	game->parser->fd = -1;
}

t_game	*init_game_core(void)
{
	t_game			*game;

	game = safe_calloc(1, sizeof(t_game), NULL, "game");
	game->map = NULL;
	game->graphics = NULL;
	game->parser = NULL;
	game->fps = INITIAL_FPS;
	game->frames = 0;
	init_parser(game);
	init_graphics(game);
	init_map(game);
	return (game);
}
