/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:55:38 by ana-cast          #+#    #+#             */
/*   Updated: 2025/02/21 17:19:13 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// check last return line
char	*parse_elements(t_game *game, int fd)
{
	char		*line;
	t_line_type	type;

	line = get_next_line(fd);
	while (line)
	{
		type = get_line_type(line);
		if (type == TEXTURE_LINE)
			parse_texture_line(game, line, get_texture_direction(line));
		else if (type == COLOR_LINE)
			parse_color_line(game, line);
		else if (type == MAP_LINE)
			return (line);
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}
