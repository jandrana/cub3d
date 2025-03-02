/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:28:59 by jorvarea          #+#    #+#             */
/*   Updated: 2025/02/28 21:02:41 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_game *game)
{
	unsigned int	row;
	unsigned int	col;

	row = (unsigned int)game->player.y;
	col = (unsigned int)game->player.x;
	if (game->map->mt[row][col] == PLAYER_NORTH)
		game->player.angle = 3 * PI / 2;
	else if (game->map->mt[row][col] == PLAYER_SOUTH)
		game->player.angle = PI / 2;
	else if (game->map->mt[row][col] == PLAYER_EAST)
		game->player.angle = 0.0000001;
	else if (game->map->mt[row][col] == PLAYER_WEST)
		game->player.angle = PI;
	game->map->mt[row][col] = '0';
	game->player.speed = 0.0;
}
