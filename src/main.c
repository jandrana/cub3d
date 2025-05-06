/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 16:27:29 by jorvarea          #+#    #+#             */
/*   Updated: 2025/05/06 21:32:29 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	game = init_game();
	game->map = parser(game, argc, argv);
	init_player(game);
	game->graphics->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d", true);
	if (!game->graphics->mlx)
		error_exit(game, E_MLX_INIT);
	mlx_set_mouse_pos(game->graphics->mlx, game->graphics->mlx->width / 2,
		game->graphics->mlx->height / 2);
	render_scene(game, game->graphics->mlx->width,
		game->graphics->mlx->height);
	mlx_loop_hook(game->graphics->mlx, manage_input, game);
	mlx_set_cursor_mode(game->graphics->mlx, MLX_MOUSE_HIDDEN);
	mlx_resize_hook(game->graphics->mlx, manage_resize, game);
	mlx_loop(game->graphics->mlx);
	free_game(game);
	return (0);
}
