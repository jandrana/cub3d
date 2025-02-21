/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:03:46 by ana-cast          #+#    #+#             */
/*   Updated: 2025/02/21 17:10:21 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_color	parse_color(t_game *game, char *content, char *identifier)
{
	char	**rgb;
	t_color	color;

	rgb = ft_split(content, ',');
	if (!rgb)
		error_exit(game, E_MEM_ALLOC, "parsing color");
	if (array_len(rgb) != 3)
	{
		free_array(&rgb);
		error_exit(game, E_COLOR_FORMAT, identifier, content);
	}
	color.r = ft_atoi(rgb[0]);
	color.g = ft_atoi(rgb[1]);
	color.b = ft_atoi(rgb[2]);
	free_array(&rgb);
	if (check_color_value(color))
		error_exit(game, E_COLOR_FORMAT, identifier, content);
	return (color);
}

void	parse_color_line(t_game *game, char *line)
{
	char	**content;
	char	*identifier;

	content = ft_split(line, ' ');
	if (!content || !content[0] || !content[0][0])
		error_exit(game, E_MEM_ALLOC, "parsing color");
	identifier = content[0];
	if (!content[1])
		error_exit(game, E_COLOR_MISSING, identifier);
	if (ft_strncmp(identifier, "F", 2))
		game->map->floor_color = parse_color(game, content[1], identifier);
	else if (ft_strncmp(identifier, "C", 2))
		game->map->ceiling_color = parse_color(game, content[1], identifier);
	else
		error_exit(game, "Invalid Identifier", identifier);
}
