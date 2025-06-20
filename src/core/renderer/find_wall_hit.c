/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_wall_hit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:11:00 by jorvarea          #+#    #+#             */
/*   Updated: 2025/06/17 20:11:00 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"
#include "macros.h"
#include "types.h"
#include <math.h>

static t_wall_hit	determine_wall_direction(t_map_tile **mt, int hit_side,
		double ray_direction[2], double position[2])
{
	t_wall_hit	wall_hit;

	if (hit_side == 0)
	{
		if (ray_direction[0] > 0)
			wall_hit.direction = EAST;
		else
			wall_hit.direction = WEST;
	}
	else
	{
		if (ray_direction[1] > 0)
			wall_hit.direction = SOUTH;
		else
			wall_hit.direction = NORTH;
	}
	wall_hit.position[0] = position[0];
	wall_hit.position[1] = position[1];
	wall_hit.tile = mt[(int)position[1]][(int)position[0]];
	return (wall_hit);
}

void	calculate_delta(double position[2], double ray_direction[2],
		double delta[2])
{
	double	diff;

	if (ray_direction[0] > 0)
	{
		diff = ceil(position[0]) - position[0] + EPSILON;
		delta[0] = diff / ray_direction[0];
	}
	else
	{
		diff = position[0] - floor(position[0]) + EPSILON;
		delta[0] = diff / -ray_direction[0];
	}
	if (ray_direction[1] > 0)
	{
		diff = ceil(position[1]) - position[1] + EPSILON;
		delta[1] = diff / ray_direction[1];
	}
	else
	{
		diff = position[1] - floor(position[1]) + EPSILON;
		delta[1] = diff / -ray_direction[1];
	}
}

t_wall_hit	find_wall_hit(t_game *game, t_map_tile **mt,
		double ray_direction[2])
{
	double	delta[2];
	double	position[2];
	int		hit_side;
	bool	step_one;

	step_one = true;
	position[0] = game->player.x;
	position[1] = game->player.y;
	while (!stop_condition(mt, position, &step_one))
	{
		calculate_delta(position, ray_direction, delta);
		if (delta[0] <= delta[1])
		{
			position[0] += ray_direction[0] * delta[0];
			position[1] += ray_direction[1] * delta[0];
			hit_side = 0;
		}
		else
		{
			position[0] += ray_direction[0] * delta[1];
			position[1] += ray_direction[1] * delta[1];
			hit_side = 1;
		}
	}
	return (determine_wall_direction(mt, hit_side, ray_direction, position));
}
