/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:11:40 by jorvarea          #+#    #+#             */
/*   Updated: 2025/03/01 18:22:03 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
	if (ray_direction[0] >= 0)
		delta[0] = (ceil(position[0]) - position[0]) / ray_direction[0];
	else
		delta[0] = (floor(position[0]) - position[0]) / ray_direction[0];
	if (ray_direction[1] >= 0)
		delta[1] = (ceil(position[1]) - position[1]) / ray_direction[1];
	else
		delta[1] = (floor(position[1]) - position[1]) / ray_direction[1];
}

t_wall_hit	find_wall_hit(t_game *game, double ray_direction[2])
{
	double	delta[2];
	double	position[2];
	int		hit_side;

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
	return (determine_wall_direction(hit_side, ray_direction, position));
}

void	calculate_wall_info(t_game *game, double angle_offset,
		t_wall_info *wall)
{
	double	dx;
	double	dy;

	dx = wall->hit.position[0] - game->player.x;
	dy = wall->hit.position[1] - game->player.y;
	wall->distance = sqrt(dx * dx + dy * dy) * cos(angle_offset);
	wall->height = (WINDOW_HEIGHT * 0.5) / wall->distance;
	wall->top = (WINDOW_HEIGHT / 2.0) - (wall->height / 2.0);
	wall->bottom = (WINDOW_HEIGHT / 2.0) + (wall->height / 2.0);
}

uint32_t	calculate_color(t_game *game, unsigned int row, unsigned int col)
{
	double		angle_offset;
	double		ray_angle;
	double		ray_direction[2];
	t_wall_info	wall;

	// mlx_image_t *wall_img;
	angle_offset = (col - WINDOW_WIDTH / 2.0) * (FOV / WINDOW_WIDTH);
	ray_angle = angle_offset + game->player.angle;
	ray_direction[0] = cos(ray_angle);
	ray_direction[1] = sin(ray_angle);
	wall.hit = find_wall_hit(game, ray_direction);
	calculate_wall_info(game, angle_offset, &wall);
	if (row < wall.top || row > wall.bottom)
	{
		if (row < WINDOW_HEIGHT / 2)
			return (color_to_uint32(game->map->ceiling_color));
		else
			return (color_to_uint32(game->map->floor_color));
	}
	// wall_img = mlx_texture_to_image(game->graphics->mlx, game->graphics->textures[NORTH]);
	return (0xFFFFFF);
}
