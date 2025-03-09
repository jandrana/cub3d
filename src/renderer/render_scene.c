/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:18:05 by jorvarea          #+#    #+#             */
/*   Updated: 2025/03/09 18:54:35 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_scene(t_game *game, unsigned int width, unsigned int height)
{
	mlx_image_t		*img;
	unsigned int	row;
	unsigned int	col;

	img = mlx_new_image(game->graphics->mlx, width, height);
	if (!img)
		error_exit(game, E_MLX_IMAGE);
	row = 0;
	while (row < height)
	{
		col = 0;
		while (col < width)
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
	img = game->graphics->minimap;
	if (mlx_image_to_window(game->graphics->mlx, img, 0, 0) == -1)
		error_exit(game, E_MLX_IMAGE2WIN);
}

void	full_render(t_game *game, unsigned int width, unsigned int height)
{
	double	current_time;
	double	delta;

	current_time = mlx_get_time();
	render_scene(game, width, height);
	draw_minimap(game);
	delta = mlx_get_time() - current_time;
	game->fps = 0.9 * game->fps + 0.1 * (1.0 / delta);
}
