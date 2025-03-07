/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:58:56 by ana-cast          #+#    #+#             */
/*   Updated: 2025/03/07 18:28:18 by ana-cast         ###   ########.fr       */
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
