/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:55:38 by ana-cast          #+#    #+#             */
/*   Updated: 2025/02/18 19:45:41 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_direction	get_texture_direction(char *content)
{
	if (!ft_strncmp(content, "NO ", 3))
		return (NORTH);
	else if (!ft_strncmp(content, "SO ", 3))
		return (SOUTH);
	else if (!ft_strncmp(content, "WE ", 3))
		return (WEST);
	else if (!ft_strncmp(content, "EA ", 3))
		return (EAST);
	return (INVALID);
}

// todo: liberar el split, etc
void	parse_texture_line(t_game *game, char *line, t_direction dir)
{
	char		**content;

	content = ft_split(line, ' ');
	if (!content)
		error_exit(game, E_MEM_ALLOC, "parsing texture");
	if (!content[1])
		error_exit(game, E_TEX_MISSING, content[0]);
	else
	{
		game->graphics->textures[dir] = mlx_load_png(content[1]);
		if (!game->graphics->textures[dir])
			error_exit(game, E_TEX_LOAD, content[1]);
	}
}

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
