/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:04:04 by jorvarea          #+#    #+#             */
/*   Updated: 2025/06/13 17:57:49 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_mandatory.h"
#include <math.h>

static bool	move_player(t_game *game, double angle_offset)
{
	double	direction[2];
	double	move_angle;
	double	new_x;
	double	new_y;

	move_angle = game->player.angle + angle_offset;
	direction[0] = cos(move_angle);
	direction[1] = sin(move_angle);
	new_x = game->player.x + direction[0] * WALK_SPEED / game->fps;
	new_y = game->player.y + direction[1] * WALK_SPEED / game->fps;
	if (game->map->mt[(int)(new_y)][(int)(new_x)] != WALL)
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
	return (true);
}

static void	handle_movement(t_game *game, bool *moved)
{
	if (mlx_is_key_down(game->graphics->mlx, MLX_KEY_W))
		*moved = move_player(game, 0);
	if (mlx_is_key_down(game->graphics->mlx, MLX_KEY_S))
		*moved = move_player(game, PI);
	if (mlx_is_key_down(game->graphics->mlx, MLX_KEY_D))
		*moved = move_player(game, PI / 2.0);
	if (mlx_is_key_down(game->graphics->mlx, MLX_KEY_A))
		*moved = move_player(game, -PI / 2.0);
	if (mlx_is_key_down(game->graphics->mlx, MLX_KEY_RIGHT))
	{
		game->player.angle += ROTATION_SPEED / game->fps;
		*moved = true;
	}
	if (mlx_is_key_down(game->graphics->mlx, MLX_KEY_LEFT))
	{
		game->player.angle -= ROTATION_SPEED / game->fps;
		*moved = true;
	}
}

void	update_sprites(t_game *game)
{
	int		i;
	t_hlist	**txt_lst;

	i = 0;
	txt_lst = game->graphics->textures_lst;
	if (!(game->frames % 30))
	{
		while (txt_lst[i] && !(game->frames % 120))
		{
			if (!(txt_lst[i]->next))
				txt_lst[i] = txt_lst[i]->head;
			else
				txt_lst[i] = txt_lst[i]->next;
			i++;
		}
	}
}

void	manage_input(void *ptr)
{
	t_game	*game;
	bool	moved;

	game = (t_game *)ptr;
	if (mlx_is_key_down(game->graphics->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(game->graphics->mlx);
		return ;
	}
	moved = false;
	handle_movement(game, &moved);
	if (moved || !(game->frames % 15))
		render_scene(game, game->graphics->mlx->width,
			game->graphics->mlx->height);
	game->frames += 1;
}
