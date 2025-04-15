/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_resize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:44:23 by jorvarea          #+#    #+#             */
/*   Updated: 2025/04/15 17:59:59 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	render_scene(game, width, height);
}
