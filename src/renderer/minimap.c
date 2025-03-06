/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:58:56 by ana-cast          #+#    #+#             */
/*   Updated: 2025/03/06 21:14:26 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include <cub3d.h>
#include <stddef.h>

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_minimap_tile(t_game *game, size_t row, size_t col, uint32_t color)
{
	size_t	x;
	size_t	y;

	col = fabs(col - game->player.x) + 6;
	row = fabs(row - game->player.y) + 6;
	x= 0;
	while (x < 20)
	{
		y = 0;
		while (y < 20)
		{
			mlx_put_pixel(game->graphics->minimap, (col * 20) + x , (row * 20) + y, 0x000000);
			mlx_put_pixel(game->graphics->minimap, (col * 20) + x , (row * 20) + y, color);
			y++;
		}
		x++;
	}
}

/* IN PROGRESS:

CHANGING MINIMAP TO WORK BY PROXIMITY INSTEAD OF THE WHOLE MAP, TAKING
	PLAYER AS CENTER

	row = game->player.y;
	col = game->player.x;
	color = get_rgba(121, 12, 142, 255);
	draw_minimap_tile(game, row, col, color);
	row = game->player.y - 6;
	col = game->player.x - 6;

*/
void	draw_minimap(t_game *game)
{
	(void)game;
	// uint32_t color;
	// size_t	row;
	// size_t	col;
	// t_map_tile	current;

	// row = 0;
	// while (row <= game->map->rows)
	// {
	// 	col = 0;
	// 	while (col <= game->map->cols)
	// 	{
	// 		current = game->map->mt[row][col];
	// 		if (current == WALL)
	// 			color = get_rgba(121, 12, 142, 255);
	// 		else if (current == SPACE)
	// 			color = get_rgba(0, 0, 0, 255);
	// 		else
	// 		 	color = get_rgba(255, 255, 255, 255);
	// 		printf("%c", current);
	// 		//draw_minimap_tile(game, row, col, color);
	// 		col++;
	// 	}
	// 	printf("\n");
	// 	row++;
	// }
}
