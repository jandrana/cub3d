/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:03:46 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/10 17:30:27 by ana-cast         ###   ########.fr       */
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
		if (game->parser->floor_color == true)
			error_exit(game, E_COLOR_DUP, "Floor");
	}
	else if (identifier == 'C')
		if (game->parser->ceiling_color == true)
			error_exit(game, E_COLOR_DUP, "Ceiling");
	return (0);
}

t_color	get_color(t_game *game, char **rgb)
{
	int		val;
	int		i;
	char	*line;
	t_color	color;

	i = -1;
	while (++i < 3)
	{
		line = ft_strtrim(rgb[i], " \t\r\v\f");
		free_str(&game->parser->line);
		game->parser->line = line;
		if (!line && !free_array(&rgb))
			error_exit(game, E_MEM_ALLOC, "trimming color");
		val = ft_atoi(line);
		if ((val < 0 || val > 255) && !free_array(&rgb))
			error_exit(game, E_COLOR_RANGE, val);
		if (i == 0)
			color.r = val;
		else if (i == 1)
			color.g = val;
		else if (i == 2)
			color.b = val;
		color.a = 255;
	}
	return (color);
}

bool	represents_number(char *str)
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
}

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
		game->parser->floor_color = true;
	else if (!ft_strncmp(identifier, "C", 2))
		game->parser->ceiling_color = true;
	return (color);
}

void	parse_color_line(t_game *game)
{
	t_parser		*parser;
	char			**element;
	int				start;
	int				i;

	i = -1;
	parser = game->parser;
	while (parser->line[++i] && ft_strchr(WHITESPACE, parser->line[i]))
		;
	start = i;
	while (parser->line[++i] && !ft_strchr(WHITESPACE, parser->line[i]))
		;
	parser->element = safe_calloc(3, sizeof(char *), game, "color");
	element = parser->element;
	element[0] = ft_substr(parser->line, start, i - start);
	element[1] = ft_substr(parser->line, i, ft_strlen(parser->line) - i - 1);
	if (!element[0] || !element[1])
		error_exit(game, E_MEM_ALLOC, "parsing color");
	if (!ft_strncmp(element[0], "F", 2) && !check_color_dup(game, 'F'))
		game->map->floor_color = parse_color(game, element[1], element[0]);
	else if (!ft_strncmp(element[0], "C", 2) && !check_color_dup(game, 'C'))
		game->map->ceiling_color = parse_color(game, element[1], element[0]);
	else
		error_exit(game, "Invalid Identifier", parser->line);
	free_array(&parser->element);
}
