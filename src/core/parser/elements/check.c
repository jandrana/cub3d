/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:37:11 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/11 15:40:57 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "types.h"
#include "error.h"

bool	check_color_value(t_color color) // unused?
{
	if (color.r > 255 || color.g > 255 || color.b > 255)
		return (1);
	return (0);
}

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

void	check_missing_values(t_game *game)
{
	check_textures(game);
	if (!game->parser->floor_color)
		error_exit(game, E_COLOR_MISSING, "Floor");
	if (!game->parser->ceiling_color)
		error_exit(game, E_COLOR_MISSING, "Ceiling");
}

void	check_textures(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 4)
		if (game->parser->textures[i] == false)
			error_exit(game, E_TEX_MISSING, get_direction_name(i));
}
