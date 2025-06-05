/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:26:58 by ana-cast          #+#    #+#             */
/*   Updated: 2025/05/29 19:12:28 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// bonus version of validate_map (n_items condition)

// bonus version adding add_item_textures to parser

// bonus version of map.c

// bonus version of elements/textures + refactor

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:57:43 by ana-cast          #+#    #+#             */
/*   Updated: 2025/05/26 20:28:02 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <cub3d.h>
#include <fcntl.h>

void	add_item_textures(t_game *game, int i) // add to bonus.h
{
	char	*str_i;
	char	*path;
	char	*file;

	i = 0;
	while (i <= 8)
	{
		str_i = ft_itoa(i);
		file = ft_strjoin(str_i, ".png");
		free_str(&str_i);
		path = ft_strjoin("assets/textures/item_sprites/", file);
		free_str(&file);
		open_map_file(game, path, 0);
		// if (add_texture(mlx_load_png(path), &game->graphics->items_lst[i]))
		// {
		// 	free_str(&path);
		// 	error_exit(game, E_TEX_LOAD, "Item Texture");
		// }
		free_str(&path);
		i++;
	}
}

t_map	*parser(t_game *game, int argc, char **argv)
{
	int		fd;
	char	*first_map_line;

	if (argc != 2)
		error_exit(game, E_ARGS_COUNT, argv[0]);
	update_map_sizes(game, argv[1]);
	fd = open_map_file(game, argv[1], 1);
	first_map_line = parse_elements(game, fd);
	//add_item_textures(game, 0);
	if (!first_map_line)
		error_exit(game, E_MAP_EMPTY);
	parser_map(game, fd, first_map_line);
	close(fd);
	return (game->map);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:56:15 by ana-cast          #+#    #+#             */
/*   Updated: 2025/05/26 20:18:59 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			if (map->mt[i][j] == 'C')
				map->mt[i][j] = 'I';
			j++;
		}
		i++;
	}
}

// void	new_item(t_game *game, size_t y, size_t x, size_t item_no)
// {
// 	game->map->items[item_no].x = x;
// 	game->map->items[item_no].y = y;
// 	game->map->items[item_no].collected = false;
// 	game->map->items[item_no].sprite_frame = 0;
// 	if (!reach_player(game, x, y))
// 		error_exit(game, E_ITEM_REACH, y, x);
// 	restore_map(game->map);
// }

// void	update_map_items(t_game *game)
// {
// 	size_t	row;
// 	size_t	col;
// 	size_t	i;

// 	i = 0;
// 	game->map->items = (t_item *)malloc(sizeof(t_item) * game->map->n_items);
// 	if (!game->map->items)
// 		error_exit(game, E_MEM_ALLOC, "map items");
// 	row = 0;
// 	while (row <= game->map->rows)
// 	{
// 		col = 0;
// 		while (col <= game->map->cols)
// 		{
// 			if (game->map->mt[row][col] == ITEM)
// 				new_item(game, row, col, i++);
// 			col++;
// 		}
// 		row++;
// 	}
// }

void	parser_map(t_game *game, int fd, char *map_line)
{
	char	*line;
	size_t	row;
	char	*trimmed;

	allocate_map_tiles(game);
	line = map_line;
	row = 0;
	while (line)
	{
		trimmed = ft_strtrim(line, "\n");
		fill_map_line(game, trimmed, row);
		row++;
		free_str(&trimmed);
		free_str(&line);
		line = get_next_line(fd);
	}
	validate_map(game);
	//update_map_items(game);
}
