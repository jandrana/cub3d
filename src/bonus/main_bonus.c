/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:38:03 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/11 18:00:31 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "macros.h"
#include "MLX42/MLX42.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	game = init_game_bonus();
	game->map = parser_bonus(game, argc, argv);
	init_player(game);
	game->graphics->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d", true);
	if (!game->graphics->mlx)
		error_exit(game, E_MLX_INIT);
	mlx_set_mouse_pos(game->graphics->mlx, game->graphics->mlx->width / 2,
		game->graphics->mlx->height / 2);
	render_bonus(game, game->graphics->mlx->width,
		game->graphics->mlx->height);
	mlx_loop_hook(game->graphics->mlx, manage_input, game);
	mlx_set_cursor_mode(game->graphics->mlx, MLX_MOUSE_HIDDEN);
	mlx_resize_hook(game->graphics->mlx, manage_resize, game);
	mlx_loop(game->graphics->mlx);
	free_game(game);
	return (0);
}
