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
				player_coord[0] = col;
				player_coord[1] = row;
				return ;
			}
			col++;
		}
		row++;
	}
}

void	init_player(t_game *game)
{
	unsigned int player_coord[2];

    find_player_coord(game->map, player_coord);
    game->player.x = player_coord[0] + 0.5;
    game->player.y = player_coord[1] + 0.5;
    if (game->map->mt[player_coord[1]][player_coord[0]] == PLAYER_NORTH)
        game->player.angle = 3 * PI / 2;
    else if (game->map->mt[player_coord[1]][player_coord[0]] == PLAYER_SOUTH)
        game->player.angle = PI / 2;
    else if (game->map->mt[player_coord[1]][player_coord[0]] == PLAYER_EAST)
        game->player.angle = 0.0000001;
    else if (game->map->mt[player_coord[1]][player_coord[0]] == PLAYER_WEST)
        game->player.angle = PI;
	game->map->mt[player_coord[1]][player_coord[0]] = '0';
    game->player.speed = 0.0;
}
