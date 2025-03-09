/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:18:05 by jorvarea          #+#    #+#             */
/*   Updated: 2025/03/09 20:23:23 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_scene(t_game *game, unsigned int width, unsigned int height)
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
}

static void	display_fps(t_game *game, unsigned int width, unsigned int height)
{
	mlx_image_t	*fps_img;
	char		fps_str[32];

	format_fps(fps_str, sizeof(fps_str), game->fps);
	fps_img = mlx_put_string(game->graphics->mlx, fps_str, 0.85 * width, 
			0.05 * height);
	if (!fps_img)
		error_exit(game, E_MLX_IMAGE);
	mlx_delete_image(game->graphics->mlx, game->graphics->fps);
	game->graphics->fps = fps_img;
	if (mlx_image_to_window(game->graphics->mlx, fps_img, 0.85 * width, 
			0.05 * height) == -1)
		error_exit(game, E_MLX_IMAGE2WIN);
	fps_img->instances[0].z = 1;
}

void	render_scene(t_game *game, unsigned int width, unsigned int height)
{
	double	current_time;
	double	delta;

	current_time = mlx_get_time();
	draw_scene(game, width, height);
	draw_minimap(game);
	display_fps(game, width, height);
	delta = mlx_get_time() - current_time;
	game->fps = 0.9 * game->fps + 0.1 * (1.0 / delta);
}
