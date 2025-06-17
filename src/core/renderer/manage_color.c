/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:11:40 by jorvarea          #+#    #+#             */
/*   Updated: 2025/06/13 20:35:18 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "renderer.h"
#include "macros.h"
#include <stdint.h>
#include <math.h>

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
	double			wall_x_fraction;
	int				tex_x;
	int				tex_y;
	double			screen_y_proportion;
	unsigned long	byte_index;

	if (wall->hit.direction == NORTH || wall->hit.direction == SOUTH)
		wall_x_fraction = wall->hit.position[0] - floor(wall->hit.position[0]);
	else
		wall_x_fraction = wall->hit.position[1] - floor(wall->hit.position[1]);
	tex_x = (int)(wall_x_fraction * wall->texture->width);
	screen_y_proportion = (double)(row - wall->top) / wall->height;
	tex_y = (int)(screen_y_proportion * wall->texture->height);
	byte_index = ((unsigned long)tex_y * wall->texture->width + tex_x) * 4;
	return (color_to_uint32(*(t_color *)&wall->texture->pixels[byte_index]));
}

uint32_t	calculate_color(t_game *game, unsigned int row, unsigned int col)
{
	double		angle_offset;
	double		ray_angle;
	double		ray_direction[2];
	t_wall_info	wall;

	angle_offset = (col - game->graphics->mlx->width / 2.0) * (FOV
			/ game->graphics->mlx->width);
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
	select_texture(game, &wall);
	return (get_wall_color(&wall, row));
}
