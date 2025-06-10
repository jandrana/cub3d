/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:55:38 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/10 17:30:50 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "parser.h"
#include "types.h"
#include <cub3d.h>
#include <libft.h>

static void	check_missing_values(t_game *game)
{
	check_textures(game);
	if (!game->parser->floor_color)
		error_exit(game, E_COLOR_MISSING, "Floor");
	if (!game->parser->ceiling_color)
		error_exit(game, E_COLOR_MISSING, "Ceiling");
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
		else if (type == INVALID_LINE)
			error_exit(game, E_MAP_UNKNOWN, parser->line);
		free_str(&parser->line);
		parser->line = get_next_line(parser->fd);
	}
}
