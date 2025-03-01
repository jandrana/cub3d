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

#include <cub3d.h>

static void	find_player_coord(t_map *map, unsigned int player_coord[2])
{
	unsigned int	row;
	unsigned int	col;

	row = 0;
	while (row < map->rows)
	{
		col = 0;
		while (col < map->cols)
		{
			if (map->mt[row][col] == PLAYER_NORTH
				|| map->mt[row][col] == PLAYER_SOUTH
				|| map->mt[row][col] == PLAYER_EAST
				|| map->mt[row][col] == PLAYER_WEST)
			{
				player_coord[0] = row;
				player_coord[1] = col;
				map->mt[row][col] = 0;
				return ;
			}
			col++;
		}
		row++;
	}
}

void	init_player(t_game *game)
{
	unsigned int	player_coord[2];

	find_player_coord(game->map, player_coord);
	game->player.x = player_coord[0] + 0.5;
	game->player.y = player_coord[1] + 0.5;
	game->player.angle = 0.00001;
	game->player.speed = 0.0;
}
