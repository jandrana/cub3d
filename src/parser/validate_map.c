/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:49:48 by ana-cast          #+#    #+#             */
/*   Updated: 2025/02/24 21:31:01 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	validate_map(t_game *game)
{
	size_t	row;
	size_t	col;

	row = 0;
	while (row < game->map->rows)
	{
		col = 0;
		while (col < game->map->cols)
		{
			//validate_near_tiles(game, row, col);
			col++;
		}
		row ++;
	}
	if (game->map->player.x < 0 || game->map->player.y < 0)
		error_exit(game, E_MAP_NO_PLAYER);
}