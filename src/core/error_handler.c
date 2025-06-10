/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:42:29 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/10 17:22:21 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "cub3d.h"
#include "error.h"
#include "libft.h"
#include "parser.h"
#include "types.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	free_map_tiles(t_game *game)
{
	t_map	*map;
	int		i;

	if (!game->map)
		return ;
	map = game->map;
	i = -1;
	while (map->mt && ++i <= (int)map->rows)
		free(map->mt[i]);
	free(map->mt);
}

static void	free_core_graphics(t_game *game)
{
	t_graphics	*graphics;

	if (!game->graphics)
		return ;
	graphics = game->graphics;
	if (!graphics)
		return ;
	free_hlist(&(graphics->textures_lst[NORTH]), delete_texture);
	free_hlist(&(graphics->textures_lst[SOUTH]), delete_texture);
	free_hlist(&(graphics->textures_lst[EAST]), delete_texture);
	free_hlist(&(graphics->textures_lst[WEST]), delete_texture);
	if (graphics->img)
		mlx_delete_image(graphics->mlx, graphics->img);
	if (graphics->fps)
		mlx_delete_image(graphics->mlx, graphics->fps);
}

void	free_core_game(t_game *game)
{
	if (!game)
		return ;
	free_map_tiles(game);
	free_core_graphics(game);
	free_parser(game->parser_state);
}

void	error_exit(t_game *game, const char *msg, ...)
{
	va_list	args;

	ft_putstr_fd(RED BOLD "Error\n  " WHITE, STDERR_FILENO);
	va_start(args, msg);
	vfprintf(stderr, msg, args);
	va_end(args);
	ft_putstr_fd("\n", STDERR_FILENO);
	if (game)
		free_game(game);
	exit(EXIT_FAILURE);
}
