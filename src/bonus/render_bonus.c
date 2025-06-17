/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:56:27 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/17 20:35:23 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "cub3d_bonus.h"
#include "renderer.h"
#include "types.h"
#include <stdlib.h>

bool	stop_condition(t_map_tile **mt, double position[2], bool *step_one)
{
	if (*step_one)
	{
		*step_one = false;
		return (false);
	}
	return (mt[(int)position[1]][(int)position[0]] == WALL
		|| mt[(int)position[1]][(int)position[0]] == DOOR);
}

void	select_texture(t_game *game, t_wall_info *wall)
{
	double	*pos;
	t_hlist	**textures_lst;

	textures_lst = game->graphics->textures_lst;
	if (wall->hit.tile == WALL)
	{
		wall->texture = textures_lst[wall->hit.direction]->content;
		if (wall->hit.direction == NORTH || wall->hit.direction == WEST)
		{
			pos = (double *)malloc(sizeof(double) * 2);
			pos[0] = wall->hit.position[0];
			pos[1] = wall->hit.position[1];
			if (wall->hit.direction == NORTH)
				pos[1] += 1;
			if (wall->hit.direction == WEST)
				pos[0] += 1;
			if (get_tile_pos_type(game->map, pos) == 'o')
				wall->texture = game->graphics->door_lst[0]->content;
			free(pos);
		}
	}
	else if (wall->hit.tile == DOOR)
		wall->texture = game->graphics->door_lst[0]->content;
}

void	render_bonus(t_game *g, unsigned int w, unsigned int h)
{

	if (!g->graphics->img)
		update_collected(g);
	if (g->map->time_end != -1 && mlx_get_time() - g->map->time_end > 3)
	{
		if (g->graphics->items_img)
			mlx_delete_image(g->graphics->mlx, g->graphics->items_img);
		g->map->time_end = -1;
	}
	render_scene(g, w, h);
	render_items(g);
	draw_minimap(g);
}
