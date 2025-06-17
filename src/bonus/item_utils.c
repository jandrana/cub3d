/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:00:29 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/17 20:19:34 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "cub3d_bonus.h"
#include "types.h"
#include <math.h>
#include <stdint.h>

double	get_distance(double x1, double x2, double y1, double y2)
{
	return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

double	get_angle(t_game *game, double x, double y)
{
	double	angle;

	angle = atan2(y, x) - game->player.angle;
	while (angle > PI)
		angle -= 2 * PI;
	while (angle < -PI)
		angle += 2 * PI;
	return (angle);
}

void	get_tex_xy(uint32_t tex_xy[2], mlx_texture_t *tex, double size[2],
		int px[2])
{
	int	row;
	int	col;

	row = px[0];
	col = px[1];
	tex_xy[0] = (uint32_t)col * (tex->width / size[0]);
	tex_xy[1] = (uint32_t)row * (tex->height / size[1]);
	if (tex_xy[0] >= tex->width)
		tex_xy[0] = tex->width - 1;
	if (tex_xy[1] >= tex->height)
		tex_xy[1] = tex->height - 1;
}

bool	stop_items(t_map_tile **mt, double position[2], bool *step_one,
		t_item item)
{
	if (*step_one)
	{
		*step_one = false;
		return (false);
	}
	if (floor(position[1]) == floor(item.y)
		&& floor(position[0]) == floor(item.x))
		return (true);
	return (mt[(int)position[1]][(int)position[0]] == WALL
		|| mt[(int)position[1]][(int)position[0]] == DOOR);
}
