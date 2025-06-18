/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 20:26:58 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/18 18:33:11 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include <libft.h>
#include <fcntl.h>
#include "MLX42/MLX42.h"
#include "cub3d_bonus.h"
#include "parser.h"
#include "types.h"

void	parse_elements(t_game *game)
{
	t_line_type		type;
	t_parser		*parser;

	type = EMPTY_LINE;
	parser = game->parser;
	parser->line = get_next_line(parser->fd);
	while (parser->line && type != INVALID_LINE)
	{
		type = get_line_type(parser->line);
		if (type == TEXTURE_LINE)
			parse_texture_line(game, get_texture_direction(parser->line));
		else if (type == COLOR_LINE)
			parse_color_line(game);
		else if (type == DOOR_LINE || type == ITEM_LINE)
			parse_bonus_textures(game, type);
		else if (type == MAP_LINE)
		{
			check_missing_values(game);
			return ;
		}
		else if (type == INVALID_LINE)
			error_exit(game, E_MAP_UNKNOWN, parser->line);
		free_str(&parser->line);
		parser->line = get_next_line(parser->fd);
	}
}

bool	check_wall(t_game *game, size_t row, size_t col)
{
	if (valid_tile(row, game->map->rows) && valid_tile(col, game->map->cols))
	{
		if (game->map->mt[row][col] == '1')
			return (0);
	}
	return (1);
}

void	check_door_tile(t_game *game, size_t row, size_t col)
{
	if (game->door_texture == false)
		error_exit(game, "Door found in map. Specify texture(s): 'P ./path'");
	if ((check_wall(game, row + 1, col) || check_wall(game, row - 1, col))
		&& (check_wall(game, row, col + 1) || check_wall(game, row, col - 1)))
		error_exit(game, "Door needs wall to hold it [%zu,%zu]", row, col);
}

void	validate_map(t_game *game)
{
	size_t	row;
	size_t	col;

	row = 0;
	while (row <= game->map->rows)
	{
		col = 0;
		while (col <= game->map->cols)
		{
			validate_near_tiles(game, row, col);
			if (game->map->mt[row][col] == ITEM)
				game->map->n_items += 1;
			if (game->map->mt[row][col] == 'D')
				check_door_tile(game, row, col);
			col++;
		}
		row++;
	}
	if (game->map->n_items > 0 && game->item_texture == false)
		error_exit(game, "Item found in map. Specify texture(s): 'S ./path'");
	if (game->player.x < 0 || game->player.y < 0)
		error_exit(game, E_MAP_NO_PLAYER);
}

t_map	*parser_bonus(t_game *game, int argc, char **argv)
{
	t_parser	*parser;

	parser = game->parser;
	if (argc != 2)
		error_exit(game, E_ARGS_COUNT, argv[0]);
	update_map_sizes(game, argv[1]);
	parser->fd = open_map_file(game, argv[1]);
	parse_elements(game);
	if (!parser->line)
		error_exit(game, E_MAP_EMPTY);
	parser_map(game);
	validate_map(game);
	update_map_items(game);
	free_parser(game->parser);
	game->parser = NULL;
	return (game->map);
}
