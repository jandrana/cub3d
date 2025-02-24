/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:55:38 by ana-cast          #+#    #+#             */
/*   Updated: 2025/02/24 21:18:42 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

//TODO: FIX COLOR: always getting E_COLOR_MISSING
static void	check_missing_values(t_game *game)
{
	check_textures(game);
	//if (!game->parser_state->floor_color)
	//	error_exit(game, E_COLOR_MISSING, "Floor");
	//if (!game->parser_state->ceiling_color)
	//	error_exit(game, E_COLOR_MISSING, "Ceiling");
}

// check last return line
char	*parse_elements(t_game *game, int fd)
{
	char		*line;
	t_line_type	type;

	line = get_next_line(fd);
	type = EMPTY_LINE;
	while (line && type != INVALID_LINE)
	{
		type = get_line_type(line);
		if (type == TEXTURE_LINE)
			parse_texture_line(game, line, get_texture_direction(line));
		else if (type == COLOR_LINE)
			parse_color_line(game, line);
		else if (type == MAP_LINE)
		{
			check_missing_values(game);
			return (line);
		}
		free_str(&line);
		line = get_next_line(fd);
	}
	return (line);
}
