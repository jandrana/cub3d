/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_wall_direction.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:11:40 by jorvarea          #+#    #+#             */
/*   Updated: 2025/03/01 13:22:38 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static t_direction determine_wall_direction(int hit_side, double ray_direction[2])
{
    if (hit_side == 0)
    {
        if (ray_direction[0] > 0)
            return EAST;
        else
            return WEST;
    }
    else
    {
        if (ray_direction[1] > 0)
            return SOUTH;
        else
            return NORTH;
    }
}

static void calculate_delta(double position[2], double ray_direction[2], double delta[2])
{
    if (ray_direction[0] >= 0)
        delta[0] = (ceil(position[0]) - position[0]) / ray_direction[0];
    else
        delta[0] = (floor(position[0]) - position[0]) / ray_direction[0];
    if (ray_direction[1] >= 0)
        delta[1] = (ceil(position[1]) - position[1]) / ray_direction[1];
    else
        delta[1] = (floor(position[1]) - position[1]) / ray_direction[1];
}

t_direction find_wall_direction(t_game *game, double ray_direction[2])
{
    double delta[2];
    double position[2];
    int hit_side;
    
    position[0] = game->player.x;
    position[1] = game->player.y;
    while (game->map->mt[(int)position[0]][(int)position[1]] != WALL)
    {
        calculate_delta(position, ray_direction, delta);
        if (delta[0] < delta[1])
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
    return determine_wall_direction(hit_side, ray_direction);
}
