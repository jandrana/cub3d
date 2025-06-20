/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:25:52 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/18 15:41:27 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"
#include "types.h"

bool	stop_condition(t_map_tile **mt, double position[2],
		bool *step_one)
{
	if (*step_one)
	{
		*step_one = false;
		return (false);
	}
	return (mt[(int)position[1]][(int)position[0]] == WALL);
}

void	select_texture(t_game *game, t_wall_info *wall)
{
	t_direction	dir;

	dir = wall->hit.direction;
	if (wall->hit.tile == WALL)
		wall->texture = game->graphics->textures_lst[dir]->content;
}
