/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:49:48 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/10 19:28:29 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <libft.h>

bool	valid_tile(size_t tile, size_t max_tile)
{
	return (tile < max_tile);
}

void	validate_walls(t_game *game, size_t row, size_t col, t_map_tile current)
{
	bool	is_edge;

	is_edge = false;
	if (row == 0 || row > game->map->rows
		|| col == 0 || col > game->map->cols)
		is_edge = true;
	if (is_edge && current != SPACE)
		error_exit(game, E_MAP_WALLS, row, col);
}

void	validate_tile(t_game *game, size_t row, size_t col, char *surrounding)
{
	t_map	*map;

	map = game->map;
	if (valid_tile(row, map->rows) && valid_tile(col, map->cols))
	{
		if (!ft_strchr(surrounding, map->mt[row][col]))
			error_exit(game, E_MAP_CHAR, map->mt[row][col], row, col);
	}
}

void	validate_near_tiles(t_game *game, size_t row, size_t col)
{
	t_map_tile	current;
	char		*surrounding;

	current = game->map->mt[row][col];
	if (current != WALL)
	{
		validate_walls(game, row, col, current);
		if (current == SPACE) // CHANGE TO ALL SPACE CHARS
			surrounding = NEAR_SPACE;
		else
			surrounding = NEAR_PLAYABLE;
		validate_tile(game, row - 1, col, surrounding);
		validate_tile(game, row + 1, col, surrounding);
		validate_tile(game, row, col - 1, surrounding);
		validate_tile(game, row, col + 1, surrounding);
		validate_tile(game, row - 1, col - 1, surrounding);
		validate_tile(game, row - 1, col + 1, surrounding);
		validate_tile(game, row + 1, col - 1, surrounding);
		validate_tile(game, row + 1, col + 1, surrounding);
	}
}
