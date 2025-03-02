/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:11:40 by jorvarea          #+#    #+#             */
/*   Updated: 2025/03/02 17:20:37 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_wall_hit
{
	t_direction		direction;
	double			position[2];
}					t_wall_hit;

typedef struct s_wall_info
{
	t_wall_hit		hit;
	double			height;
	double			top;
	double			bottom;
	double			distance;
	mlx_texture_t	*texture;
}					t_wall_info;

static t_wall_hit	determine_wall_direction(int hit_side,
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
	return (wall_hit);
}

static void	calculate_delta(double position[2], double ray_direction[2],
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

static t_wall_hit	find_wall_hit(t_game *game, t_map_tile **mt,
		double ray_direction[2])
{
	double	delta[2];
	double	position[2];
	int		hit_side;

	position[0] = game->player.x;
	position[1] = game->player.y;
	while (mt[(int)position[1]][(int)position[0]] != WALL)
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
	return (determine_wall_direction(hit_side, ray_direction, position));
}

void	calculate_wall_info(t_game *game, double angle_offset,
		t_wall_info *wall)
{
	double	dx;
	double	dy;
	double	half_window;

	dx = wall->hit.position[0] - game->player.x;
	dy = wall->hit.position[1] - game->player.y;
	half_window = game->graphics->mlx->height / 2.0;
	wall->distance = sqrt(dx * dx + dy * dy) * cos(angle_offset);
	wall->height = half_window / wall->distance;
	wall->top = half_window - (wall->height / 2.0);
	wall->bottom = half_window + (wall->height / 2.0);
}

uint32_t	get_wall_color(t_wall_info *wall, unsigned int row)
{
	(void)wall;
	(void)row;
	return (0x0000FFFF);
}

uint32_t	calculate_color(t_game *game, unsigned int row, unsigned int col)
{
	double		angle_offset;
	double		ray_angle;
	double		ray_direction[2];
	t_wall_info	wall;

	angle_offset = (col - game->graphics->mlx->width / 2.0) * (FOV / game->graphics->mlx->width);
	ray_angle = angle_offset + game->player.angle;
	ray_direction[0] = cos(ray_angle);
	ray_direction[1] = sin(ray_angle);
	wall.hit = find_wall_hit(game, game->map->mt, ray_direction);
	calculate_wall_info(game, angle_offset, &wall);
	if (row < wall.top || row > wall.bottom)
	{
		if (row < (game->graphics->mlx->height / 2.0))
			return (color_to_uint32(game->map->ceiling_color));
		else
			return (color_to_uint32(game->map->floor_color));
	}
	wall.texture = game->graphics->textures[wall.hit.direction];
	return (get_wall_color(&wall, row));
}
