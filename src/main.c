/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 16:27:29 by jorvarea          #+#    #+#             */
/*   Updated: 2025/03/06 21:08:58 by ana-cast         ###   ########.fr       */
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
	game->graphics->minimap = mlx_new_image(game->graphics->mlx, MINI, MINI);
	mlx_get_mouse_pos(game->graphics->mlx, &game->cursor.last_cursor_x,
		&game->cursor.last_cursor_y);
	render_scene(game, game->graphics->mlx->width, game->graphics->mlx->height);
	mlx_loop_hook(game->graphics->mlx, manage_key_pressed, game);
	mlx_mouse_hook(game->graphics->mlx, manage_mouse, game);
	mlx_resize_hook(game->graphics->mlx, manage_resize, game);
	mlx_loop(game->graphics->mlx);
	free_game(game);
	return (0);
}
