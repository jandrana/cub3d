/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:03:46 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/03 13:36:29 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "macros.h"
#include "parser.h"
#include <cub3d.h>
#include <libft.h>

int	check_color_dup(t_game *game, char identifier)
{
	if (identifier == 'F')
	{
		if (game->parser_state->floor_color == true)
			error_exit(game, E_COLOR_DUP, "Floor");
	}
	else if (identifier == 'C')
		if (game->parser_state->ceiling_color == true)
			error_exit(game, E_COLOR_DUP, "Ceiling");
	return (0);
}

t_color	get_color(t_game *game, char **rgb)
{
	int		val;
	int		i;
	char	*trimmed;
	t_color	color;

	i = -1;
	while (++i < 3)
	{
		trimmed = ft_strtrim(rgb[i], " \t\r\v\f");
		if (!trimmed && !free_array(&rgb))
			error_exit(game, E_MEM_ALLOC, "trimming color");
		val = ft_atoi(trimmed);
		if ((val < 0 || val > 255) && !free_str(&trimmed) && !free_array(&rgb))
			error_exit(game, E_COLOR_RANGE, val);
		if (i == 0)
			color.r = val;
		else if (i == 1)
			color.g = val;
		else if (i == 2)
			color.b = val;
		color.a = 255;
		free_str(&trimmed);
	}
	return (color);
}

bool	represents_number(char *str) // check this implementation, check leaks, etc
{
	int		i;
	bool	digit;

	i = 0;
	digit = false;
	while (str && str[i])
	{
		if (ft_strchr("0123456789", str[i]))
			digit = true;
		else if (!ft_strchr(WHITESPACE, str[i]))
			return (false);
		i++;
	}
	return (digit);
} // test this new implementation (see damage_report for current bugs) (fixed 8?)

bool	valid_color_format(char *content)
{
	bool	is_num;
	int		i;
	int		n;

	is_num = false;
	n = 0;
	if (!content || !content[0])
		return (1);
	i = -1;
	while (content[++i])
	{
		if (!is_num && ft_isdigit(content[i]) && ++n)
			is_num = true;
		else if (is_num && content[i] == ',')
			is_num = false;
		else if ((is_num && ft_isdigit(content[i])
				&& !ft_strchr(WHITESPACE, content[i - 1]))
			|| ft_strchr(WHITESPACE, content[i]))
			;
		else
			return (1);
	}
	if (!is_num || n != 3)
		return (1);
	return (0);
}

t_color	parse_color(t_game *game, char *content, char *identifier)
{
	char	**rgb;
	t_color	color;

	if (valid_color_format(content))
		error_exit(game, E_COLOR_FORMAT, identifier, content);
	rgb = ft_split(content, ',');
	if (!rgb)
		error_exit(game, E_MEM_ALLOC, "parsing color");
	if (array_len(rgb) != 3 || !represents_number(rgb[0])
		|| !represents_number(rgb[1]) || !represents_number(rgb[2]))
	{
		free_array(&rgb);
		error_exit(game, E_COLOR_FORMAT, identifier, content);
	}
	color = get_color(game, rgb);
	free_array(&rgb);
	if (!ft_strncmp(identifier, "F", 2))
		game->parser_state->floor_color = true;
	else if (!ft_strncmp(identifier, "C", 2))
		game->parser_state->ceiling_color = true;
	return (color);
}

void	parse_color_line(t_game *game, char *line)
{
	char	*identifier;
	char	*value;
	int		start;
	int		i;

	i = -1;
	while (line[++i] && ft_strchr(WHITESPACE, line[i]))
		;
	start = i;
	while (line[++i] && !ft_strchr(WHITESPACE, line[i]))
		;
	identifier = ft_substr(line, start, i - start);
	value = ft_substr(line, i, ft_strlen(line) - i - 1);
	game->parser_state->free_line = line;
	if (!identifier || (!value && !free_str(&identifier)))
		error_exit(game, E_MEM_ALLOC, "parsing color");
	if (!ft_strncmp(identifier, "F", 2) && !check_color_dup(game, 'F'))
		game->map->floor_color = parse_color(game, value, identifier);
	else if (!ft_strncmp(identifier, "C", 2) && !check_color_dup(game, 'C'))
		game->map->ceiling_color = parse_color(game, value, identifier);
	else
		error_exit(game, "Invalid Identifier", line);
	game->parser_state->free_line = NULL;
	free_str(&identifier);
	free_str(&value);
}
