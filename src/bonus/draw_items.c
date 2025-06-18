/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_items.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:00:29 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/18 19:06:05 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "cub3d_bonus.h"
#include "renderer.h"
#include "types.h"
#include <math.h>
#include <stdint.h>

static bool	find_item_hit(t_game *game, double ray_angle, t_item item)
{
	double	delta[2];
	double	position[2];
	bool	step_one;
	double	ray_direction[2];

	step_one = true;
	position[0] = game->player.x;
	position[1] = game->player.y;
	ray_direction[0] = cos(ray_angle);
	ray_direction[1] = sin(ray_angle);
	while (!stop_items(game->map->mt, position, &step_one, item))
	{
		calculate_delta(position, ray_direction, delta);
		if (delta[0] <= delta[1])
		{
			position[0] += ray_direction[0] * delta[0];
			position[1] += ray_direction[1] * delta[0];
		}
		else
		{
			position[0] += ray_direction[0] * delta[1];
			position[1] += ray_direction[1] * delta[1];
		}
	}
	return (game->map->mt[(int)position[1]][(int)position[0]] == ITEM);
}

static void	draw_item_scaled(t_game *game, t_item_info it, t_item item)
{
	uint32_t	tex_p[2];
	uint8_t		*pixel;
	int			row;
	int			col;

	row = -1;
	while (++row < it.size[1])
	{
		col = -1;
		while (++col < it.size[0])
		{
			get_tex_xy(tex_p, it.tex, it.size, (int []){row, col});
			pixel = &it.tex->pixels[(tex_p[1] * it.tex->width + tex_p[0]) * 4];
			if (pixel[3] > 0
				&& it.pos[0] + col >= 0 && it.pos[0] + col < game->graphics->mlx->width
				&& it.pos[1] + row >= 0 && it.pos[1] + row < game->graphics->mlx->height)
			{
				it.offset = (it.pos[0] + col - game->graphics->mlx->width / 2.0)
					* (FOV / game->graphics->mlx->width);
				if (find_item_hit(game, it.offset + game->player.angle, item))
					mlx_put_pixel(game->graphics->img, it.pos[0] + col,
						it.pos[1] + row, color_to_uint32(*(t_color *)pixel));
			}
		}
	}
}

static void	draw_collectible_sprite(t_game *game, t_item item)
{
	t_item_info		info;

	info.dx = item.x - game->player.x;
	info.dy = item.y - game->player.y;
	info.dist = get_distance(item.x, game->player.x, item.y, game->player.y);
	info.angle = get_angle(game, info.dx, info.dy);
	if (fabs(info.angle) > FOV)
		return ;
	info.size[1] = (game->graphics->mlx->height * 0.4) / info.dist;
	info.size[0] = info.size[1] * 0.8;
	info.pos[0] = (info.angle / FOV + 0.5) * game->graphics->mlx->width - info.size[0] / 2;
	info.pos[1] = (game->graphics->mlx->height - info.size[1]) / 2;
	info.pos[1] += info.size[1] * 0.1;
	info.tex = game->graphics->items_lst[0]->content;
	draw_item_scaled(game, info, item);
}

static void	sort_items(t_item *items, int n_items, t_player player)
{
	t_item		temp;
	int			i;

	i = 0;
	while (i < n_items - 1)
	{
		if (get_distance(player.x, items[i].x, player.y, items[i].y)
			< get_distance(player.x, items[i + 1].x, player.y, items[i + 1].y))
		{
			temp = items[i];
			items[i] = items[i + 1];
			items[i + 1] = temp;
		}
		i++;
	}
}

void	render_items(t_game *game)
{
	int	i;

	i = 0;
	sort_items(game->map->items, game->map->n_items, game->player);
	while (i < game->map->n_items)
	{
		if (game->map->items[i].collected == false)
			draw_collectible_sprite(game, game->map->items[i]);
		i++;
	}
}
