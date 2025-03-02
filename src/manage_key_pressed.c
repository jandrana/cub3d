/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_key_pressed.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:04:04 by jorvarea          #+#    #+#             */
/*   Updated: 2025/03/02 18:01:07 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_player(t_game *game, double angle_offset)
{
	double	direction[2];
	double	move_angle;

	move_angle = game->player.angle + angle_offset;
	direction[0] = cos(move_angle);
	direction[1] = sin(move_angle);
	game->player.x += direction[0] * WALK_FACTOR;
	game->player.y += direction[1] * WALK_FACTOR;
}

static bool	handle_movement(t_game *game)
{
	bool	moved;

	moved = false;
	if (mlx_is_key_down(game->graphics->mlx, MLX_KEY_W))
	{
		move_player(game, 0);
		moved = true;
	}
	if (mlx_is_key_down(game->graphics->mlx, MLX_KEY_S))
	{
		move_player(game, PI);
		moved = true;
	}
	if (mlx_is_key_down(game->graphics->mlx, MLX_KEY_D))
	{
		move_player(game, PI / 2.0);
		moved = true;
	}
	if (mlx_is_key_down(game->graphics->mlx, MLX_KEY_A))
	{
		move_player(game, -PI / 2.0);
		moved = true;
	}
	return (moved);
}

static bool	handle_rotation(t_game *game)
{
	bool	rotated;

	rotated = false;
	if (mlx_is_key_down(game->graphics->mlx, MLX_KEY_RIGHT))
	{
		game->player.angle += ROTATION_FACTOR;
		rotated = true;
	}
	if (mlx_is_key_down(game->graphics->mlx, MLX_KEY_LEFT))
	{
		game->player.angle -= ROTATION_FACTOR;
		rotated = true;
	}
	return (rotated);
}

void	manage_key_pressed(void *ptr)
{
	t_game	*game;
	bool	update_needed;

	game = (t_game *)ptr;
	if (mlx_is_key_down(game->graphics->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(game->graphics->mlx);
		return ;
	}
	update_needed = handle_movement(game) || handle_rotation(game);
	if (update_needed)
		render_scene(game, game->graphics->mlx->width,
			game->graphics->mlx->height);
}
