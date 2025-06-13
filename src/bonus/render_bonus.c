/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:56:27 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/13 13:35:10 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "types.h"
#include "renderer.h"
#include "cub3d_bonus.h"
#include <stdlib.h>

bool	stop_condition(t_map_tile **mt, double position[2],
		bool *step_one, bool skip_item)
{
	if (*step_one)
	{
		*step_one = false;
		return (false);
	}
	return (mt[(int)position[1]][(int)position[0]] == WALL ||
		(mt[(int)position[1]][(int)position[0]] == DOOR && !skip_item)); // ||
		//(mt[(int)position[1]][(int)position[0]] == ITEM && !skip_item));
}

void	select_texture(t_game *game, t_wall_info *wall)
{
	double	*pos;

	if (wall->hit.tile == WALL)
	{
		wall->texture =
			game->graphics->textures_lst[wall->hit.direction]->content;
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
	//else if (wall->hit.tile == ITEM)
	//	wall->texture = game->graphics->items_lst[0]->content;
}

uint32_t	manage_color(t_game *game, unsigned int row, unsigned int col)
{
	uint32_t	color;

	game->graphics->skip_item = false;
	color = calculate_color(game, row, col);
	if ((color & 0x000000FF) != 0x000000FF)
	{
		game->graphics->skip_item = true;
		color = calculate_color(game, row, col);
		return (color);
	}
	return (color);
}

void	render_bonus(t_game *game, unsigned int width, unsigned int height)
{
	render_scene(game, width, height);
	draw_minimap(game);
}
