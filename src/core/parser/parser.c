/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:57:43 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/05 14:12:12 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <cub3d.h>
#include <fcntl.h>

void	update_map_sizes(t_game *game, char *filename)
{
	int		fd;
	char	*line;
	size_t	len;

	fd = open_map_file(game, filename, 1);
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
	{
		close(fd);
		error_exit(game, E_MAP_EMPTY);
	}
	parser_map(game, fd, first_map_line);
	close(fd);
	return (game->map);
}
