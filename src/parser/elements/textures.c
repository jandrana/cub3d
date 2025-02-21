/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:16:11 by ana-cast          #+#    #+#             */
/*   Updated: 2025/02/21 17:47:51 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <stdbool.h>

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

static char	*get_direction_name(t_direction dir)
{
	if (dir == NORTH)
		return ("NO");
	else if (dir == SOUTH)
		return ("SO");
	else if (dir == WEST)
		return ("WE");
	else if (dir == EAST)
		return ("EA");
	return ("INVALID DIRECTION");
}

void	check_textures(t_game *game)
{
	int i;

	i = -1;
	while (++i < 4)
		if (game->parser_state->textures[i] == false)
			error_exit(game, E_TEX_MISSING, get_direction_name(i));
}

// todo: liberar el split, etc
// todo: checkear que el path existe antes de llamar a la mlx
void	parse_texture_line(t_game *game, char *line, t_direction dir)
{
	char		**content;

	if (dir == INVALID)
		error_exit(game, E_TEX_INVALID, line);
	else if (game->parser_state->textures[dir] == true)
		error_exit(game, E_TEX_DUP, get_direction_name(dir));
	content = ft_split(line, ' ');
	if (!content)
		error_exit(game, E_MEM_ALLOC, "parsing texture");
	if (!content[1])
		error_exit(game, E_TEX_MISSING, content[0]);
	game->graphics->textures[dir] = mlx_load_png(ft_strtrim(content[1], "\n"));
	if (!game->graphics->textures[dir])
		error_exit(game, E_TEX_LOAD, content[1]);
	game->parser_state->textures[dir] = true;
	free_array(&content);
}
