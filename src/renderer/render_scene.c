/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:18:05 by jorvarea          #+#    #+#             */
/*   Updated: 2025/03/01 13:12:46 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

uint32_t calculate_color(t_game *game, unsigned int row, unsigned int col)
{
    double angle_offset;
    double ray_angle;
    double ray_direction[2];
    mlx_image_t *wall_img;

    angle_offset = (col - WINDOW_WIDTH / 2.0) * (FOV / WINDOW_WIDTH);
    ray_angle = angle_offset + game->player.angle;
    ray_direction[0] = cos(ray_angle);
    ray_direction[1] = sin(ray_angle);
    wall_img = mlx_texture_to_image(game->graphics->mlx, game->graphics->textures[find_wall_direction(game, ray_direction)]);
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
