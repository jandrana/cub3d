/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:56:15 by ana-cast          #+#    #+#             */
/*   Updated: 2025/02/25 17:13:57 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_line_type	check_map_line(t_game *game, char *line, size_t row)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (!ft_strchr(VALID_MAP_CHARS, line[i]))
			error_exit(game, E_MAP_CHAR, line[i], row, i);
	}
	return (MAP_LINE);
}

void	allocate_map_tiles(t_game *game)
{
	size_t	i;
	size_t	j;

	game->map->mt = malloc(sizeof(t_map_tile *) * (game->map->rows + 1));
	if (!game->map->mt)
		error_exit(game, E_MEM_ALLOC, "map rows");
	i = 0;
	while (i <= game->map->rows)
	{
		game->map->mt[i] = malloc(sizeof(t_map_tile) * (game->map->cols + 1));
		if (!game->map->mt[i])
			error_exit(game, E_MEM_ALLOC, "map columns");
		j = 0;
		while (j <= game->map->cols)
		{
			game->map->mt[i][j] = SPACE;
			j++;
		}
		i++;
	}
}
void	set_player(t_game *game, t_map_tile tile, size_t row, size_t col)
{
	if (!(tile == PLAYER_EAST || tile == PLAYER_NORTH || tile == PLAYER_SOUTH
		|| tile == PLAYER_WEST))
		return ;
	if (game->map->player.x != -1 || game->map->player.y != -1)
		error_exit(game, E_MAP_MULTI_PLAYER);
	game->map->player.x = col + 0.5;
	game->map->player.y = row + 0.5;
}

// !!! SEGFAULT HERE (fix 1st time tommorrow)
void	fill_map_line(t_game *game, char *t_line, size_t row)
{
	size_t col;

	col = 0;
	while (t_line[col])
	{
		game->map->mt[row][col] = t_line[col]; // <- HERE
		set_player(game, t_line[col], row, col);
		col++;
	}
	while (col < game->map->cols)
	{
		game->map->mt[row][col] = SPACE;
		col++;
	}
}

void	parser_map(t_game *game, int fd, char *map_line)
{
	char	*line;
	int		row;
	char	*trimmed;
	
	allocate_map_tiles(game);
	line = map_line;
	row = 0;
	while (line)
	{
		trimmed = ft_strtrim(line, "\n");
		//fill_map_line(game, trimmed, row);
		row++;
		free_str(&trimmed);
		free_str(&line);
		line = get_next_line(fd);
	}
	validate_map(game);
}
