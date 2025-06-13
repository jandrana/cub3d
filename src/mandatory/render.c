/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:25:52 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/12 17:50:51 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"
#include "types.h"

bool	stop_condition(t_map_tile **mt, double position[2],
		bool *step_one, bool skip_item)
{
	if (*step_one)
	{
		*step_one = false;
		return (false);
	}
	(void) skip_item;
	return (mt[(int)position[1]][(int)position[0]] == WALL);
}

void	select_texture(t_game *game, t_wall_info *wall)
{
	if (wall->hit.tile == WALL)
		wall->texture = 
			game->graphics->textures_lst[wall->hit.direction]->content;
}

uint32_t	manage_color(t_game *game, unsigned int row, unsigned int col)
{
	uint32_t	color;

	color = calculate_color(game, row, col);
	return (color);
}
