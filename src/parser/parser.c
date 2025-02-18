/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:57:43 by ana-cast          #+#    #+#             */
/*   Updated: 2025/02/18 19:12:24 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_map	*parser(t_game *game, int argc, char **argv)
{
	t_map	*map;
	int		fd;
	//char 	*first_map_line;

	map = (t_map *)malloc(sizeof(t_map));
	if (argc != 2)
		error_exit(game, E_ARGS_COUNT, argv[0]);
	fd = open_map_file(game, argv[1]);
	parse_elements(game, fd);
	//first_map_line = parse_elements(game, fd);
	//parse_map(game, fd, first_map_line);
	return (map);
}
