/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:57:43 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/18 17:56:38 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "error.h"
#include "libft.h"
#include <cub3d.h>
#include <fcntl.h>

void	free_parser(t_parser *parser)
{
	if (!parser)
		return ;
	if (parser->fd > 0)
	{
		close(parser->fd);
		parser->fd = -1;
	}
	safe_free(parser->line);
	if (parser->element)
		free_array(&parser->element);
	safe_free(parser);
}

void	update_map_sizes(t_game *game, char *filename)
{
	int		fd;
	char	*line;
	size_t	len;

	fd = open_map_file(game, filename);
	line = get_next_line(fd);
	while (line)
	{
		if (get_line_type(line) == MAP_LINE
			|| (game->map->rows && get_line_type(line) == EMPTY_LINE))
		{
			len = ft_strlen(line);
			if (len > 0 && line[len - 1] == '\n')
				len--;
			if (len > game->map->cols)
				game->map->cols = len;
			game->map->rows++;
		}
		free_str(&line);
		line = get_next_line(fd);
	}
	close(fd);
	if (game->map->rows == 0)
		error_exit(game, E_MAP_EMPTY);
}
