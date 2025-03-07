/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:58:56 by ana-cast          #+#    #+#             */
/*   Updated: 2025/03/07 18:29:16 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include <cub3d.h>
#include <stddef.h>

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void draw_circle(t_game *game, int pos_x, int pos_y, int radius, uint32_t color)
{
	double	i;
	double	angle;
	double	x;
	double	y;

	i = 0;
	while (i < 360)
	{
		angle = i;
		x = radius * cos(angle * PI / 180);
		y = radius * sin(angle * PI / 180);
		mlx_put_pixel(game->graphics->minimap, pos_x + x, pos_y + y, color);
		i += 0.1;
	}
}

uint32_t	minimap_tile_color(t_game *game, int y, int x)
{
	double	rot_x;
	double	rot_y;
	double	map_x;
	double	map_y;
	uint32_t color;
	
	rot_x = cos(game->player.angle) * x - sin(game->player.angle) * y;
	rot_y = sin(game->player.angle) * x + cos(game->player.angle) * y;
	map_x = game->player.x + rot_x;
	map_y = game->player.y + rot_y;
	color = 0x808080FF;
	if ((size_t)map_x <= game->map->cols
		&& (size_t)map_y <= game->map->rows)
	{
		if (game->map->mt[(int)map_y][(int)map_x] == WALL && printf("1"))
			color = 0xFF00FFFF; // pink
		else if (game->map->mt[(int)map_y][(int)map_x] != SPACE && printf("0"))
			color = 0x00FF00FF; // green
	}
	else
		printf(" ");
	return (color);
}

void	draw_minimap(t_game *game)
{
	//int	x;
	//int	y;
	//uint32_t color;

	mlx_delete_image(game->graphics->mlx, game->graphics->minimap);
	game->graphics->minimap = mlx_new_image(game->graphics->mlx, MINI, MINI);
	draw_circle(game, CENTER_POS, CENTER_POS, CENTER_POS, 0xFFFFFFFF);
	// y = -6;
	// while (++y <= 5)
	// {
	// 	x = -6;
	// 	while (++x <= 5)
	// 	{
	// 		color = minimap_tile_color(game, y, x);
	// 		draw_minimap_tile(game->graphics->minimap, y, x, color);
	// 	}
	// 	printf("\n");
	// }
	// draw_minimap_tile(game->graphics->minimap, 0, 0, 0xFFFF00FF);
	// Dibujar orientacion (N, S, E, W)
}
