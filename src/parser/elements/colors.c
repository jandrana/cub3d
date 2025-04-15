/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:03:46 by ana-cast          #+#    #+#             */
/*   Updated: 2025/04/15 15:08:42 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	check_color_dup(t_game *game, char identifier)
{
	if (identifier == 'F')
	{
		if (game->parser_state->floor_color == true)
			error_exit(game, E_COLOR_DUP, "Floor");
	}
	else if (identifier == 'C')
		if (game->parser_state->floor_color == true)
			error_exit(game, E_COLOR_DUP, "Ceiling");
	return (0);
}

t_color	get_color(t_game *game, char **rgb)
{
	int		i;
	char	*trimmed;
	t_color	color;

	i = -1;
	while (++i < 3)
	{
		trimmed = ft_strtrim(rgb[i], " \t\r\v\f");
		if (!trimmed)
			error_exit(game, E_MEM_ALLOC, "trimming color");
		if (i == 0)
			color.r = ft_atoi(trimmed);
		else if (i == 1)
			color.g = ft_atoi(trimmed);
		else if (i == 2)
			color.b = ft_atoi(trimmed);
		free_str(&trimmed);
	}
	return (color);
}

t_color	parse_color(t_game *game, char *content, char *identifier)
{
	char	**rgb;
	t_color	color;

	rgb = ft_split(content, ',');
	if (!rgb)
		error_exit(game, E_MEM_ALLOC, "parsing color");
	if (array_len(rgb) != 3 || content[ft_strlen(content) - 1] == ',')
	{
		free_array(&rgb);
		error_exit(game, E_COLOR_FORMAT, identifier, content);
	}
	color = get_color(game, rgb);
	free_array(&rgb);
	if (check_color_value(color))
		error_exit(game, E_COLOR_FORMAT, identifier, content);
	if (ft_strncmp(identifier, "F", 2))
		game->parser_state->floor_color = true;
	else if (ft_strncmp(identifier, "C", 2))
		game->parser_state->ceiling_color = true;
	return (color);
}

void	parse_color_line(t_game *game, char *line)
{
	char	**content;
	char	*identifier;

	game->parser_temp = ft_split(line, ' ');
	content = game->parser_temp;
	if (!content || !content[0] || !content[0][0])
		error_exit(game, E_MEM_ALLOC, "parsing color");
	identifier = content[0];
	if (!content[1])
		error_exit(game, E_COLOR_MISSING, identifier);
	if (ft_strncmp(identifier, "F", 2) == 0 && !check_color_dup(game, 'F'))
		game->map->floor_color = parse_color(game, content[1], identifier);
	else if (ft_strncmp(identifier, "C", 2) == 0 && !check_color_dup(game, 'C'))
		game->map->ceiling_color = parse_color(game, content[1], identifier);
	else
		error_exit(game, "Invalid Identifier", identifier);
	free_array(&game->parser_temp);
}
