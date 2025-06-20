/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_input_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:04:04 by jorvarea          #+#    #+#             */
/*   Updated: 2025/06/13 18:54:41 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "types.h"
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include "MLX42/MLX42.h"
#include "libft.h"

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
	if (game->map->mt[(int)(new_y)][(int)(new_x)] != WALL
		&& game->map->mt[(int)(new_y)][(int)(new_x)] != DOOR)
	{
		game->player.x = new_x;
		game->player.y = new_y;
		if (game->map->mt[(int)(new_y)][(int)(new_x)] == ITEM)
			check_collected_item(game);
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
	if (mlx_is_key_down(game->graphics->mlx, MLX_KEY_Q))
	{
		game->cursor_locked = false;
		mlx_set_cursor_mode(game->graphics->mlx, MLX_MOUSE_NORMAL);
	}
}

void	handle_cursor_movement(t_game *game, bool *moved)
{
	int32_t	mouse_x;
	int32_t	mouse_y;
	double	delta_x;

	mlx_get_mouse_pos(game->graphics->mlx, &mouse_x, &mouse_y);
	if (mouse_x != game->graphics->mlx->width / 2)
	{
		delta_x = (mouse_x - game->graphics->mlx->width / 2);
		game->player.angle += delta_x * MOUSE_SENSITIVITY / game->fps;
		*moved = true;
	}
	mlx_set_mouse_pos(game->graphics->mlx,
		game->graphics->mlx->width / 2,
		game->graphics->mlx->height / 2);
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
		if (game->item_sprite_n < game->map->n_items && (game->frames % 120))
			game->item_sprite_n += 1;
		else
			game->item_sprite_n = 0;
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
	handle_door_toggle(game, &moved);
	handle_movement(game, &moved);
	if (game->cursor_locked)
		handle_cursor_movement(game, &moved);
	if (!(game->frames % 60))
		update_sprites(game);
	if (moved || !(game->frames % 15))
		render_bonus(game, game->graphics->mlx->width,
			game->graphics->mlx->height);
	game->frames += 1;
}
