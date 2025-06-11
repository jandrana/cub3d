/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:56:15 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/11 16:13:29 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include <cub3d.h>
#include <libft.h>

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
	if (game->player.x != -1 || game->player.y != -1)
		error_exit(game, E_MAP_MULTI_PLAYER);
	game->player.x = col + 0.5;
	game->player.y = row + 0.5;
}

void	fill_map_line(t_game *game, char *t_line, size_t row)
{
	size_t	col;

	col = 0;
	while (t_line[col])
	{
		if (col > game->map->cols || row > game->map->rows)
			error_exit(game, E_MAP_CHAR, t_line[col], row, col);
		game->map->mt[row][col] = t_line[col];
		set_player(game, t_line[col], row, col);
		col++;
	}
	while (col <= game->map->cols && row <= game->map->rows)
	{
		game->map->mt[row][col] = SPACE;
		col++;
	}
}

/* BONUS FUNCTION
bool	reach_player(t_game *game, size_t x, size_t y)
{
	char		player_char;
	char		position_char;

	player_char = game->map->mt[(int)game->player.y][(int)game->player.x];
	position_char = game->map->mt[y][x];
	if (x < 0 || y < 0 || x > game->map->cols || y > game->map->rows)
		return (0);
	if (ft_strchr(NO_REACH_PLAYER, position_char))
		return (0);
	if (position_char == player_char)
		return (1);
	if (position_char == EMPTY)
		game->map->mt[y][x] = 'V';
	else if (ft_strchr(VALID_MAP_CHARS, 'I') && position_char == 'I')
		game->map->mt[y][x] = 'C';
	if (reach_player(game, x - 1, y) || reach_player(game, x + 1, y)
		|| reach_player(game, x, y - 1)
		|| reach_player(game, x, y + 1))
		return (1);
	return (0);
}
*/

void	restore_map(t_map *map)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			if (map->mt[i][j] == 'V')
				map->mt[i][j] = '0';
			// if (map->mt[i][j] == 'C')
			// 	map->mt[i][j] = 'I';
			j++;
		}
		i++;
	}
}

void	parser_map(t_game *game)
{
	char	*line;
	size_t	row;

	allocate_map_tiles(game);
	line = ft_strdup(game->parser->line);
	if (!line)
		error_exit(game, E_MEM_ALLOC, "parsing map line");
	row = 0;
	while (line)
	{
		free_str(&game->parser->line);
		game->parser->line = ft_strtrim(line, "\n");
		free_str(&line);
		if (!game->parser->line)
			error_exit(game, E_MEM_ALLOC, "trimming map line");
		fill_map_line(game, game->parser->line, row);
		line = get_next_line(game->parser->fd);
		row++;
	}
}
