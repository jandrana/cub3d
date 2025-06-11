/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 16:27:29 by jorvarea          #+#    #+#             */
/*   Updated: 2025/06/11 15:38:01 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_mandatory.h"
#include "MLX42/MLX42.h"
#include "error.h"
#include "init.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	game = init_game_core();
	game->map = parser(game, argc, argv);
	init_player(game);
	game->graphics->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d", true);
	if (!game->graphics->mlx)
		error_exit(game, E_MLX_INIT);
	render_scene(game, game->graphics->mlx->width,
		game->graphics->mlx->height);
	mlx_loop_hook(game->graphics->mlx, manage_input, game);
	mlx_set_cursor_mode(game->graphics->mlx, MLX_MOUSE_HIDDEN);
	mlx_resize_hook(game->graphics->mlx, manage_resize, game);
	mlx_loop(game->graphics->mlx);
	free_game(game);
	return (0);
}
