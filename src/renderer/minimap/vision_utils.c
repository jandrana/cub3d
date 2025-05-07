/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vision_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:49:26 by ana-cast          #+#    #+#             */
/*   Updated: 2025/05/07 19:01:40 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static double	*get_absolute_px(t_game *game, double center, double x,
		double y)
{
	double	*abs_pos;

	abs_pos = (double *)malloc(sizeof(double) * 2);
	abs_pos[0] = game->player.x + (x - center) / TILE_SIZE;
	abs_pos[1] = game->player.y + (y - center) / TILE_SIZE;
	return (abs_pos);
}

char	get_tile_pos_type(t_map *map, double *pos)
{
	char	type;

	if (pos[0] >= 0 && pos[0] < map->cols && pos[1] >= 0 && pos[1] <= map->rows)
	{
		type = map->mt[(int)pos[1]][(int)pos[0]];
		return (type);
	}
	return (SPACE);
}

static bool	pixel_on_wall(t_game *game, double center, double x, double y)
{
	double	*pos;
	char	type;

	pos = get_absolute_px(game, center, x, y);
	type = get_tile_pos_type(game->map, pos);
	free(pos);
	if (type != WALL && type != SPACE)
		return (false);
	return (true);
}

static bool	in_player_row_column(t_game *game, double center, double x,
	double y)
{
	double	*pos;
	double	x_diff;
	double	y_diff;

	pos = get_absolute_px(game, center, x, y);
	x_diff = floor(pos[0]) - floor(game->player.x);
	y_diff = floor(pos[1]) - floor(game->player.y);
	free(pos);
	if (x_diff == 0 || y_diff == 0)
		return (true);
	return (false);
}

bool	vision_hits_wall(t_game *game, double center, double *pos)
{
	double	x;
	double	y;

	x = pos[0];
	y = pos[1];
	if (pixel_on_wall(game, center, x, y))
		return (true);
	if ((pixel_on_wall(game, center, x + 1, y)
			|| pixel_on_wall(game, center, x, y + 1)
			|| pixel_on_wall(game, center, x + 1, y + 1))
		&& !in_player_row_column(game, center, x, y))
		return (true);
	return (false);
}
