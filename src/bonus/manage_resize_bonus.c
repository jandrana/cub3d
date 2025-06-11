/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_resize_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:44:23 by jorvarea          #+#    #+#             */
/*   Updated: 2025/05/27 16:04:31 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "MLX42/MLX42.h"

void	manage_resize(int32_t width, int32_t height, void *ptr)
{
	t_game	*game;

	game = (t_game *)ptr;
	mlx_delete_image(game->graphics->mlx, game->graphics->minimap);
	mlx_delete_image(game->graphics->mlx, game->graphics->fps);
	mlx_delete_image(game->graphics->mlx, game->graphics->img);
	game->graphics->minimap = NULL;
	game->graphics->fps = NULL;
	game->graphics->img = NULL;
	game->graphics->mlx->width = width;
	game->graphics->mlx->height = height;
	render_scene(game, width, height);
	if (game->cursor_locked)
		mlx_set_mouse_pos(game->graphics->mlx, width / 2, height / 2);
}
