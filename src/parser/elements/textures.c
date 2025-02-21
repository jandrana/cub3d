/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:16:11 by ana-cast          #+#    #+#             */
/*   Updated: 2025/02/21 17:21:06 by ana-cast         ###   ########.fr       */
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
	game->graphics->textures[dir] = mlx_load_png(content[1]);
	if (!game->graphics->textures[dir])
		error_exit(game, E_TEX_LOAD, content[1]);
}
