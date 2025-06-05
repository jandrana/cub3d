/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:58:56 by ana-cast          #+#    #+#             */
/*   Updated: 2025/05/27 16:13:02 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include <cub3d_bonus.h>
#include <macros.h> // for null and other macros
#include <math.h>

void	draw_circle(mlx_image_t *img, double *pos, int radius, uint32_t color,
	int w)
{
	double	angle;
	double	x;
	double	y;

	angle = 0;
	while (angle < 360)
	{
		x = radius * cos(angle);
		y = radius * sin(angle);
		mlx_put_pixel(img, pos[0] + x, pos[1] + y, color);
		angle += 0.1;
	}
	while (w > 0 && w--)
		draw_circle(img, pos, radius + 1, color, w);
}

void	draw_vision(t_game *game, double center, double r_len)
{
	double	angle;
	double	r;
	double	pos[2];
	bool	hit;

	center = 120;
	angle = -FOV / 2;
	while (angle <= FOV / 2)
	{
		hit = false;
		r = 0;
		while (r <= r_len && r <= MINI_R && hit == false)
		{
			pos[0] = center + cos(game->player.angle + angle) * r;
			pos[1] = center + sin(game->player.angle + angle) * r;
			if (!vision_hits_wall(game, center, pos))
				mlx_put_pixel(game->graphics->img, pos[0], pos[1], 0xFFDE2180);
			else
				hit = true;
			r += 0.5;
		}
		angle += 0.05 / r;
	}
}

/*
distance = sqrt((x1 - x2)^2 + (y1 - y2)^2)
Comparison:
	Inside: distance < r
	Outside: distance > r
*/
void	draw_tile(t_game *game, double *pos, uint32_t color)
{
	double	pixel[2];
	double	center;
	double	r;

	center = 120;
	r = 5;
	pixel[0] = center + pos[0] * TILE_SIZE;
	pixel[1] = center + pos[1] * TILE_SIZE;
	if (pixel[0] >= 21 && pixel[0] < 219 && pixel[1] >= 21 && pixel[1] < 219)
	{
		if (sqrt(pow(center - pixel[0], 2) + pow(center - pixel[1], 2)) <= r
			* TILE_SIZE)
		{
			mlx_put_pixel(game->graphics->img, pixel[0], pixel[1], color);
			mlx_put_pixel(game->graphics->img, pixel[0] + 1, pixel[1], color);
			mlx_put_pixel(game->graphics->img, pixel[0], pixel[1] + 1, color);
			mlx_put_pixel(game->graphics->img, pixel[0] + 1, pixel[1] + 1,
				color);
		}
	}
}

void	draw_tiles(t_game *game, t_mini_item **map_items)
{
	double		rel_pos[2];
	double		abs_pos[2];

	rel_pos[1] = -6;
	while (rel_pos[1] <= 5)
	{
		rel_pos[0] = -6;
		while (rel_pos[0] <= 5)
		{
			abs_pos[0] = floor(game->player.x + rel_pos[0]);
			abs_pos[1] = floor(game->player.y + rel_pos[1]);
			if (get_tile_pos_type(game->map, abs_pos) == EMPTY
				|| get_tile_pos_type(game->map, abs_pos) == ITEM)
				draw_tile(game, rel_pos, 0x303030FF);
			else
				draw_tile(game, rel_pos, 0x606060FF);
			if (get_tile_pos_type(game->map, abs_pos) == ITEM
				&& fabs(rel_pos[0] - floor(rel_pos[0])) > 0.9999
				&& fabs(rel_pos[1] - floor(rel_pos[1])) > 0.9999)
				add_minimap_items(game, map_items, rel_pos);
			rel_pos[0] += 0.1;
		}
		rel_pos[1] += 0.1;
	}
}

void	draw_minimap(t_game *game)
{
	t_mini_item	*map_items;

	map_items = NULL;
	draw_circle(game->graphics->img, (double []){120, 120}, MINI_R, U_CLEAR, 5);
	draw_tiles(game, &map_items);
	draw_vision(game, 120, VISION_R);
	draw_items(game, map_items);
	clear_map_items(&map_items);
	draw_circle(game->graphics->img, (double []){120, 120}, 0, U_RED, 3);
}

/*
TODO: cardinal points draw (only once)

void	draw_cardinal_points(t_game *game)
{
draw_circle(game->graphics->img, (double[]){120, 18}, 0, U_RED, 13);
// 20-(8/2)=16
mlx_put_string(game->graphics->mlx, "N", 115, 8);
draw_circle(game->graphics->img, (double[]){16, 120}, 0, U_RED, 13);
mlx_put_string(game->graphics->mlx, "W", 10, 110);
draw_circle(game->graphics->img, (double[]){120, 225}, 0, U_RED, 13);
mlx_put_string(game->graphics->mlx, "S", 115, 215);
draw_circle(game->graphics->img, (double[]){221, 120}, 0, U_RED, 13);
mlx_put_string(game->graphics->mlx, "E", 217, 110);
}
*/
