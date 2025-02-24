/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:49:48 by ana-cast          #+#    #+#             */
/*   Updated: 2025/02/24 21:31:25 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#define NEAR_SPACE " 1\n"
#define NEAR_PLAYABLE "10NSWE"

bool	valid_tile(size_t tile, size_t max_tile)
{
	if (tile > 0 && tile <= max_tile)
		return (1);
	return (0);
}

void	validate_walls(t_game *game, size_t row, size_t col)
{
	if (row == 0 || row == game->map->rows 
		|| col == 0 || col == game->map->cols)
		error_exit(game, E_MAP_WALLS);
}

// check if game->map->rows/cols es + 1 o no.
void	validate_near_tiles(t_game *game, size_t row, size_t col)
{
	t_map_tile	current;
	char		*surrounding;
	
	current = game->map->mt[row][col];
	if (current != WALL)
	{
		validate_walls(game, row, col);
		if (current == SPACE)
			surrounding = NEAR_SPACE;
		else
			surrounding = NEAR_PLAYABLE;
		if (valid_tile(row - 1, game->map->rows) 
			&& !ft_strchr(surrounding, game->map->mt[row - 1][col]))
			error_exit(game, E_MAP_CHAR, game->map->mt[row - 1][col], row, col);
		if (valid_tile(row + 1, game->map->rows) 
			&& !ft_strchr(surrounding, game->map->mt[row + 1][col]))
			error_exit(game, E_MAP_CHAR, game->map->mt[row - 1][col], row, col);
		if (valid_tile(col - 1, game->map->cols)
			&& !ft_strchr(surrounding, game->map->mt[row][col - 1]))
			error_exit(game, E_MAP_CHAR, game->map->mt[row - 1][col], row, col);
		if (valid_tile(col + 1, game->map->cols)
			&& !ft_strchr(surrounding, game->map->mt[row][col + 1]))
			error_exit(game, E_MAP_CHAR, game->map->mt[row - 1][col], row, col);
	}
}

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
			validate_near_tiles(game, row, col);
			col++;
		}
		row ++;
	}
	if (game->map->player.x < 0 || game->map->player.y < 0)
		error_exit(game, E_MAP_NO_PLAYER);
}