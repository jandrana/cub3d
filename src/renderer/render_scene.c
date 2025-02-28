/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:18:05 by jorvarea          #+#    #+#             */
/*   Updated: 2025/02/28 22:31:59 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include <cub3d.h>
#include <stdint.h>

uint32_t calculate_color(t_game *game, unsigned int row, unsigned int col)
{
    (void)game;
    (void)row;
    (void)col;
    return (0xFFFFFF);
}

void	render_scene(t_game *game)
{
    mlx_image_t	*img;
    int row;
    int col;

	img = mlx_new_image(game->graphics->mlx, game->graphics->mlx->width, game->graphics->mlx->height);
    if (!img)
        error_exit(game, E_MLX_IMAGE);
    row = 0;
    while (row < game->graphics->mlx->height)
    {
        col = 0;
        while (col < game->graphics->mlx->width)
        {
            mlx_put_pixel(img, col, row, calculate_color(game, row, col));
            col++;
        }
        row++;
    }    
    mlx_delete_image(game->graphics->mlx, game->graphics->img);
    game->graphics->img = img;
    if (mlx_image_to_window(game->graphics->mlx, img, 0, 0) == -1)
        error_exit(game, E_MLX_IMAGE2WIN);
}