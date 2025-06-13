/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 20:13:14 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/12 21:18:47 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "types.h"
#include "libft.h"
#include <fcntl.h>
#include <stdlib.h>

static void	restore_map(t_map *map)
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
			if (map->mt[i][j] == 'C')
				map->mt[i][j] = 'I';
			if (map->mt[i][j] == 'P')
				map->mt[i][j] = 'D';
			j++;
		}
		i++;
	}
}

static bool	reach_player(t_game *game, size_t x, size_t y)
{
	char		player_char;
	char		position_char;

	if (!valid_tile(x, game->map->cols) || !valid_tile(y, game->map->rows))
		return (0);
	player_char = game->map->mt[(int)game->player.y][(int)game->player.x];
	position_char = game->map->mt[y][x];
	if (position_char == WALL || position_char == SPACE
		|| position_char == 'V' || position_char == 'C')
		return (0);
	if (position_char == player_char)
		return (1);
	if (position_char == EMPTY)
		game->map->mt[y][x] = 'V';
	else if (position_char == ITEM)
		game->map->mt[y][x] = 'C';
	else if (position_char == DOOR)
		game->map->mt[y][x] = 'P';
	if (reach_player(game, x - 1, y) || reach_player(game, x + 1, y)
		|| reach_player(game, x, y - 1)
		|| reach_player(game, x, y + 1))
		return (1);
	return (0);
}

static void	new_item(t_game *game, size_t y, size_t x, size_t item_no)
{
	game->map->items[item_no].x = x;
	game->map->items[item_no].y = y;
	game->map->items[item_no].collected = false;
	game->map->items[item_no].sprite_frame = 0;
	if (!reach_player(game, x, y))
		error_exit(game, E_ITEM_REACH, y, x);
	restore_map(game->map);
}

void	update_map_items(t_game *game)
{
	size_t	row;
	size_t	col;
	size_t	i;

	game->map->items = (t_item *)malloc(sizeof(t_item) * game->map->n_items);
	if (!game->map->items)
		error_exit(game, E_MEM_ALLOC, "map items");
	i = 0;
	row = 0;
	while (row <= game->map->rows)
	{
		col = 0;
		while (col <= game->map->cols)
		{
			if (game->map->mt[row][col] == ITEM)
				new_item(game, row, col, i++);
			col++;
		}
		row++;
	}
}

void	parse_bonus_textures(t_game *game, t_line_type type)
{
	char	*path;
	int		fd;
	t_hlist	**list_ptr;

	if (type == DOOR_LINE && game->door_texture == true)
		error_exit(game, E_TEX_DUP, "door texture");
	list_ptr = &game->graphics->door_lst[0];
	if (type == DOOR_LINE)
		game->door_texture = true;
	else if (type)
	{
		list_ptr = &game->graphics->items_lst[0];
		game->item_texture = true;
	}
	path = path_from_texture(game, game->parser);
	free_str(&game->parser->line);
	game->parser->line = path;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_exit(game, E_TEX_LOAD, path);
	close(fd);
	if (add_texture(mlx_load_png(path), list_ptr))
		error_exit(game, E_TEX_LOAD, path);
	free_array(&game->parser->element);
}
