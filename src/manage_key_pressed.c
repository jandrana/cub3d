/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_key_pressed.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:04:04 by jorvarea          #+#    #+#             */
/*   Updated: 2025/03/06 21:06:09 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	move_player(t_game *game, double angle_offset)
{
	double	direction[2];
	double	move_angle;
	double	new_x;
	double	new_y;

	move_angle = game->player.angle + angle_offset;
	direction[0] = cos(move_angle);
	direction[1] = sin(move_angle);
	new_x = game->player.x + direction[0] * WALK_FACTOR;
	new_y = game->player.y + direction[1] * WALK_FACTOR;
	if (game->map->mt[(int)(new_y)][(int)(new_x)] != WALL)
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
	return (true);
}

static bool	handle_movement(t_game *game)
{
	bool	moved;

	moved = false;
	if (mlx_is_key_down(game->graphics->mlx, MLX_KEY_W))
		moved = move_player(game, 0);
	if (mlx_is_key_down(game->graphics->mlx, MLX_KEY_S))
		moved = move_player(game, PI);
	if (mlx_is_key_down(game->graphics->mlx, MLX_KEY_D))
		moved = move_player(game, PI / 2.0);
	if (mlx_is_key_down(game->graphics->mlx, MLX_KEY_A))
		moved = move_player(game, -PI / 2.0);
	if (mlx_is_key_down(game->graphics->mlx, MLX_KEY_RIGHT))
	{
		game->player.angle += ROTATION_FACTOR;
		moved = true;
	}
	if (mlx_is_key_down(game->graphics->mlx, MLX_KEY_LEFT))
	{
		game->player.angle -= ROTATION_FACTOR;
		moved = true;
	}
	return (moved);
}

void	manage_key_pressed(void *ptr)
{
	t_game	*game;

	game = (t_game *)ptr;
	if (mlx_is_key_down(game->graphics->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(game->graphics->mlx);
		return ;
	}
	if (handle_movement(game))
		render_scene(game, game->graphics->mlx->width,
			game->graphics->mlx->height);
}
