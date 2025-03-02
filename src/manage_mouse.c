/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 17:49:42 by jorvarea          #+#    #+#             */
/*   Updated: 2025/03/02 19:50:23 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	manage_mouse(mouse_key_t button, action_t action, modifier_key_t mods,
		void *ptr)
{
	t_game	*game;
	int32_t	new_x;
	int32_t	new_y;

	(void)button;
	(void)action;
	(void)mods;
	game = (t_game *)ptr;
	mlx_get_mouse_pos(game->graphics->mlx, &new_x, &new_y);
	game->player.angle += (new_x - game->cursor.last_cursor_x)
		* MOUSE_SENSITIVITY;
	game->cursor.last_cursor_x = new_x;
	game->cursor.last_cursor_y = new_y;
	render_scene(game, game->graphics->mlx->width, game->graphics->mlx->height);
}
