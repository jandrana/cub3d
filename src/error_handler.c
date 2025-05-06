/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:42:29 by ana-cast          #+#    #+#             */
/*   Updated: 2025/05/06 21:39:42 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include <cub3d.h>
#include <stdio.h>
#include <unistd.h>

static void delete_texture(void *texture)
{
	mlx_delete_texture((mlx_texture_t *)texture);
}

static void	free_hlist(t_hlist **lst, void (*del)(void *))
{
	t_hlist	*node;

	node = *lst;
	while (node)
	{
		*lst = node->next;
		(*del)(node->content);
		node->head = NULL;
		free(node);
		node = *lst;
	}
}

static void	end_mlx(t_graphics *graphics)
{
	if (!graphics)
		return ;
	if (graphics->img)
		mlx_delete_image(graphics->mlx, graphics->img);
	if (graphics->minimap)
		mlx_delete_image(graphics->mlx, graphics->minimap);
	if (graphics->fps)
		mlx_delete_image(graphics->mlx, graphics->fps);
	if (graphics->mlx)
		mlx_terminate(graphics->mlx);
	free_hlist(graphics->textures_lst, delete_texture);
	free(graphics);
}

static void	free_map(t_map	*map)
{
	int	i;

	i = -1;
	if (!map)
		return ;
	while (map->mt && ++i <= (int)map->rows)
		free(map->mt[i]);
	if (map->items)
		free(map->items);
	free(map->mt);
	free(map);
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	if (game->map)
		free_map(game->map);
	if (game->graphics)
		end_mlx(game->graphics);
	if (game->parser_state)
		free(game->parser_state);
	if (game->parser_temp)
		free_array(&game->parser_temp);
	free(game);
}

void	error_exit(t_game *game, const char *msg, ...)
{
	va_list	args;

	ft_putstr_fd(RED BOLD "Error\n  " WHITE, STDERR_FILENO);
	va_start(args, msg);
	vfprintf(stderr, msg, args);
	va_end(args);
	ft_putstr_fd("\n", STDERR_FILENO);
	if (game)
		free_game(game);
	exit(EXIT_FAILURE);
}
