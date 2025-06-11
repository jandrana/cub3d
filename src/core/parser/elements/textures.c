/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:16:11 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/10 17:31:25 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "error.h"
#include "libft.h"
#include "macros.h"
#include "parser.h"
#include "types.h"
#include "cub3d.h"
#include <stdbool.h>
#include <fcntl.h>

t_direction	get_texture_direction(char *content)
{
	char	*dir;
	int		i;

	i = -1;
	dir = content;
	while (ft_strchr(WHITESPACE, content[++i]))
		++dir;
	if (ft_strlen(dir) < 3 || !ft_strchr(WHITESPACE, dir[2]))
		return (INVALID);
	if (!ft_strncmp(dir, "NO", 2))
		return (NORTH);
	else if (!ft_strncmp(dir, "SO", 2))
		return (SOUTH);
	else if (!ft_strncmp(dir, "WE", 2))
		return (WEST);
	else if (!ft_strncmp(dir, "EA", 2))
		return (EAST);
	return (INVALID);
}

char	*get_direction_name(t_direction dir)
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

bool	add_texture(mlx_texture_t *texture, t_hlist **txt_lst)
{
	t_hlist	*new_node;

	if (!texture)
		return (1);
	if (!txt_lst)
		return (delete_texture(texture), 1);
	new_node = hslt_new_node(texture, *txt_lst);
	if (!new_node)
		return (delete_texture(texture), 1);
	hlstadd_back(txt_lst, new_node);
	return (0);
}

int	number_of_occurrences(char *str, int c)
{
	int	i;
	int	n;

	i = -1;
	n = 0;
	while ((char)str[++i])
	{
		if (str[i] == (char)c)
			n++;
	}
	if ((char)c == '\0')
		return (1);
	return (n);
}

bool	check_extension(char *path, char *extension)
{
	char	*ext;
	char	*file;

	if (!path || ft_strlen(path) < ft_strlen(extension))
		return (1);
	file = ft_strrchr(path, '/');
	if (!file)
		file = path;
	if (number_of_occurrences(file, '.') != 1)
		return (1);
	ext = ft_strrchr(file, '.');
	if (!ext)
		return (1);
	if (ft_strncmp(ext, extension, ft_strlen(extension) + 1) != 0)
		return (1);
	return (0);
}

char	*path_from_texture(t_game *game, t_parser *parser)
{
	char	*path;

	parser->element = ft_split(game->parser->line, ' ');
	if (!parser->element)
		error_exit(game, E_MEM_ALLOC, "parsing texture");
	if (!parser->element[1])
		error_exit(game, E_TEX_MISSING, parser->element[0]);
	path = ft_strtrim(parser->element[1], WHITESPACE);
	if (!path)
		error_exit(game, E_TEX_MISSING, parser->element[0]);
	if (check_extension(path, ".png"))
	{
		free_str(&path);
		error_exit(game, E_TEX_INVALID, parser->line);
	}
	return (path);
}

void	parse_texture_line(t_game *game, t_direction dir)
{
	t_parser		*parser;
	char			*path;
	int				fd;

	parser = game->parser;
	if (dir == INVALID)
		error_exit(game, E_TEX_INVALID, parser->line);
	else if (!ALLOW_SPRITES && parser->textures[dir] == true) // check sprites
		error_exit(game, E_TEX_DUP, get_direction_name(dir));
	path = path_from_texture(game, parser);
	free_str(&game->parser->line);
	game->parser->line = path;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_exit(game, E_TEX_LOAD, path);
	close(fd);
	if (add_texture(mlx_load_png(path), &game->graphics->textures_lst[dir]))
		error_exit(game, E_TEX_LOAD, path);
	parser->textures[dir] = true;
	free_array(&parser->element);
}

/*
void	parse_texture_line(t_game *game, char *line, t_direction dir)
{
	char	**content;
	char	*trimmed;
	int		fd;

	if (dir == INVALID)
		error_exit(game, E_TEX_INVALID, line);
	//else if (ALLOW_SPRITES && game->parser_state->textures[dir] == true) // check allow sprites
	//	error_exit(game, E_TEX_DUP, get_direction_name(dir));
	trimmed = ft_strtrim(line, "\n");
	if (!trimmed)
		error_exit(game, E_MEM_ALLOC, "trimming texture");
	content = ft_split(trimmed, ' ');
	if (!free_str(&trimmed) && !content)
		error_exit(game, E_MEM_ALLOC, "parsing texture");
	if (!content[1])
		error_exit(game, E_TEX_MISSING, content[0]);
	fd = open(content[1], O_RDONLY);
	if (fd < 0)
		error_exit(game, E_TEX_LOAD, content[1]);
	close(fd);
	if (add_texture(mlx_load_png(content[1]), &game->graphics->textures_lst[dir]))
		error_exit(game, E_TEX_LOAD, content[1]);
	game->parser_state->textures[dir] = true;
	free_array(&content);
}
*/