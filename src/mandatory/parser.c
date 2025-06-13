/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:57:43 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/13 13:23:26 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "error.h"
#include "cub3d_mandatory.h"
#include <fcntl.h>
#include <libft.h>

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
			col++;
		}
		row++;
	}
	if (game->player.x < 0 || game->player.y < 0)
		error_exit(game, E_MAP_NO_PLAYER);
}

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
		else if (type == MAP_LINE)
		{
			check_missing_values(game);
			return ;
		}
		else if (type == INVALID_LINE || type == DOOR_LINE || type == ITEM_LINE)
			error_exit(game, E_MAP_UNKNOWN, parser->line);
		free_str(&parser->line);
		parser->line = get_next_line(parser->fd);
	}
}

t_map	*parser(t_game *game, int argc, char **argv)
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
	free_parser(game->parser);
	game->parser = NULL;
	return (game->map);
}
