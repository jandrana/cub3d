/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:16:11 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/05 14:14:08 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "error.h"
#include "libft.h"
#include "macros.h"
#include <cub3d.h>
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
	if (!ft_strncmp(dir, "NO ", 3))
		return (NORTH);
	else if (!ft_strncmp(dir, "SO ", 3))
		return (SOUTH);
	else if (!ft_strncmp(dir, "WE ", 3))
		return (WEST);
	else if (!ft_strncmp(dir, "EA ", 3))
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
	int	i;

	i = -1;
	while (++i < 4)
		if (game->parser_state->textures[i] == false)
			error_exit(game, E_TEX_MISSING, get_direction_name(i));
}

t_hlist	*hslt_new_node(void *content, t_hlist *head)
{
	t_hlist	*node;

	if (!content)
		return (NULL);
	node = (t_hlist *)malloc(sizeof(t_hlist));
	if (!node)
		return (NULL);
	node->content = content;
	if (!head)
		node->head = node;
	else
		node->head = head;
	node->next = NULL;
	return (node);
}

t_hlist	*hlst_last_node(t_hlist *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	hlstadd_back(t_hlist **lst, t_hlist *node)
{
	t_hlist	*last;

	if (!node)
		return ;
	if (!(*lst))
	{
		*lst = node;
		node->head = node;
	}
	else
	{
		last = hlst_last_node(*lst);
		if (last)
		{
			node->head = *lst;
			last->next = node;
		}
	}
}

bool	add_texture(mlx_texture_t *texture, t_hlist **txt_lst)
{
	t_hlist	*new_node;

	if (!texture || !txt_lst)
		return (1);
	new_node = hslt_new_node(texture, *txt_lst);
	if (!new_node)
		return (1);
	hlstadd_back(txt_lst, new_node);
	return (0);
}

bool	check_extension(char *filename, char *extension)
{
	char	*ext;

	ext = ft_strrchr(filename, '.');
	if (!ext)
		return (1);
	if (ft_strncmp(ext, extension, ft_strlen(extension) + 1) != 0)
		return (1);
	return (0);
}

void	parse_texture_line(t_game *game, char *line, t_direction dir)
{
	char	**content;
	char	*path;
	int		fd;

	if (dir == INVALID)
		error_exit(game, E_TEX_INVALID, line);
	else if (!ALLOW_SPRITES && game->parser_state->textures[dir] == true) // check allow sprites
		error_exit(game, E_TEX_DUP, get_direction_name(dir));
	content = ft_split(line, ' ');
	if (!content)
		error_exit(game, E_MEM_ALLOC, "parsing texture");
	if (!content[1])
		error_exit(game, E_TEX_MISSING, content[0]);
	path = ft_strtrim(content[1], WHITESPACE);
	if (!path && !free_array(&content))
		error_exit(game, E_TEX_MISSING, content[0]);
	fd = open(path, O_RDONLY);
	if (fd < 0 || check_extension(path, ".png"))
		error_exit(game, E_TEX_LOAD, path);
	close(fd);
	if (add_texture(mlx_load_png(path), &game->graphics->textures_lst[dir]))
		error_exit(game, E_TEX_LOAD, path);
	game->parser_state->textures[dir] = true;
	free_array(&content);
	free_str(&path);
}
