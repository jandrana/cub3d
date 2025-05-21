/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:16:11 by ana-cast          #+#    #+#             */
/*   Updated: 2025/05/21 12:53:25 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "libft.h"
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

void	parse_texture_line(t_game *game, char *line, t_direction dir)
{
	char	**content;
	char	*trimmed;
	int		fd;

	if (dir == INVALID)
		error_exit(game, E_TEX_INVALID, line);
	//else if (game->parser_state->textures[dir] == true)
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
