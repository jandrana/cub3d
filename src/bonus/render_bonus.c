/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:56:27 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/14 14:26:35 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "cub3d_bonus.h"
#include "renderer.h"
#include "types.h"
#include <math.h>
#include <stdlib.h>

bool	stop_condition(t_map_tile **mt, double position[2], bool *step_one)
{
	if (*step_one)
	{
		*step_one = false;
		return (false);
	}
	return (mt[(int)position[1]][(int)position[0]] == WALL
		|| mt[(int)position[1]][(int)position[0]] == DOOR);
}

void	select_texture(t_game *game, t_wall_info *wall)
{
	double	*pos;
	t_hlist	**textures_lst;

	textures_lst = game->graphics->textures_lst;
	if (wall->hit.tile == WALL)
	{
		wall->texture = textures_lst[wall->hit.direction]->content;
		if (wall->hit.direction == NORTH || wall->hit.direction == WEST)
		{
			pos = (double *)malloc(sizeof(double) * 2);
			pos[0] = wall->hit.position[0];
			pos[1] = wall->hit.position[1];
			if (wall->hit.direction == NORTH)
				pos[1] += 1;
			if (wall->hit.direction == WEST)
				pos[0] += 1;
			if (get_tile_pos_type(game->map, pos) == 'o')
				wall->texture = game->graphics->door_lst[0]->content;
			free(pos);
		}
	}
	else if (wall->hit.tile == DOOR)
		wall->texture = game->graphics->door_lst[0]->content;
}

typedef struct s_sprite_bounds
{
	int			start_x;
	int			end_x;
	int			start_y;
	int			end_y;
	int			width;
	int			height;
	double		trans_y;
}				t_sprite_bounds;

typedef struct s_sprite_distance
{
	t_item		*item;
	double		distance;
}				t_sprite_distance;

static bool	project_sprite(t_game *g, t_item *it, t_sprite_bounds *b)
{
	double	sx;
	double	sy;
	double	inv;
	double	tx;
	int		scr_x;

	sx = it->x - g->player.x;
	sy = it->y - g->player.y;
	inv = 1.0 / (cos(g->player.angle + PI / 2) * sin(g->player.angle)
		- cos(g->player.angle) * sin(g->player.angle + PI / 2));
	tx = inv * (sin(g->player.angle) * sx - cos(g->player.angle) * sy);
	b->trans_y = inv * (-sin(g->player.angle + PI / 2) * sx
		+ cos(g->player.angle + PI / 2) * sy);
	if (b->trans_y <= 0)
		return (false);
	b->width = fabs(g->graphics->mlx->height / b->trans_y);
	b->height = b->width;
	scr_x = (int)((g->graphics->mlx->width / 2) * (1 + tx / b->trans_y));
	b->start_x = -b->width / 2 + scr_x;
	b->end_x = b->width / 2 + scr_x;
	b->start_y = -b->height / 2 + g->graphics->mlx->height / 2;
	b->end_y = b->height / 2 + g->graphics->mlx->height / 2;
	if (b->start_x < 0)
		b->start_x = 0;
	if (b->end_x >= (int)g->graphics->mlx->width)
		b->end_x = g->graphics->mlx->width - 1;
	if (b->start_y < 0)
		b->start_y = 0;
	if (b->end_y >= (int)g->graphics->mlx->height)
		b->end_y = g->graphics->mlx->height - 1;
	return (true);
}

static void	draw_sprite_column(t_game *g, mlx_texture_t *tex,
		const t_sprite_bounds *b, int stripe)
{
	int		tex_x;
	int		d;
	int		tex_y;
	int		col;
	int		y;

	tex_x = (int)(256 * (stripe - (-b->width / 2 + (b->start_x + b->end_x) / 2))
		* tex->width / b->width) / 256;
	y = b->start_y;
	while (y < b->end_y)
	{
		d = y * 256 - g->graphics->mlx->height * 128 + b->height * 128;
		tex_y = ((d * tex->height) / b->height) / 256;
		col = color_to_uint32(*(t_color *)&tex->pixels[(tex_y * tex->width + tex_x) * 4]);
		if (((t_color *)&tex->pixels[(tex_y * tex->width + tex_x) * 4])->a >= 128)
			mlx_put_pixel(g->graphics->img, stripe, y, col);
		y++;
	}
}

static void	render_sprite(t_game *g, t_item *it, double *z)
{
	t_sprite_bounds	b;
	mlx_texture_t	*tex;
	int			s;

	if (it->collected || !project_sprite(g, it, &b))
		return ;
	tex = g->graphics->items_lst[0]->content;
	s = b.start_x;
	while (s < b.end_x)
	{
		if (b.trans_y < z[s])
			draw_sprite_column(g, tex, &b, s);
		s++;
	}
}

static double	*build_zbuffer(t_game *g, int w)
{
	double		*z;
	double		off;
	double		ang;
	t_wall_hit	h;
	int			i;

	z = malloc(sizeof(double) * w);
	if (!z)
		error_exit(g, E_MEM_ALLOC, "zbuffer");

	i = 0;
	while (i < w)
	{
		off = (i - w / 2.0) * (FOV / w);
		ang = off + g->player.angle;
		h = find_wall_hit(g, g->map->mt, (double [2]){cos(ang), sin(ang)});
		z[i] = sqrt((h.position[0] - g->player.x) * (h.position[0] - g->player.x)
				 + (h.position[1] - g->player.y) * (h.position[1] - g->player.y))
			 * cos(off);
		i++;
	}
	return (z);
}

static t_sprite_distance	*allocate_sprite_distances(t_game *g)
{
	t_sprite_distance	*sprite_distances;

	if (g->map->n_items == 0)
		return (NULL);
	sprite_distances = malloc(sizeof(t_sprite_distance) * g->map->n_items);
	if (!sprite_distances)
		error_exit(g, E_MEM_ALLOC, "sprite distances");
	return (sprite_distances);
}

static void	calculate_sprite_distances(t_game *g, t_sprite_distance *sprites)
{
	int	idx;

	idx = 0;
	while (idx < g->map->n_items)
	{
		sprites[idx].item = &g->map->items[idx];
		sprites[idx].distance = sqrt(
			(g->map->items[idx].x - g->player.x) * (g->map->items[idx].x - g->player.x) +
			(g->map->items[idx].y - g->player.y) * (g->map->items[idx].y - g->player.y)
		);
		idx++;
	}
}

static void	sort_sprites_by_distance(t_sprite_distance *sprites, int n_items)
{
	t_sprite_distance	temp;
	int					i;
	int					j;

	i = 0;
	while (i < n_items - 1)
	{
		j = 0;
		while (j < n_items - 1 - i)
		{
			if (sprites[j].distance < sprites[j + 1].distance)
			{
				temp = sprites[j];
				sprites[j] = sprites[j + 1];
				sprites[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

static void	render_sorted_sprites(t_game *g, t_sprite_distance *sprites, double *z)
{
	int	idx;

	idx = 0;
	while (idx < g->map->n_items)
	{
		render_sprite(g, sprites[idx].item, z);
		idx++;
	}
}

static void	render_all_sprites(t_game *g, double *z)
{
	t_sprite_distance	*sprite_distances;

	sprite_distances = allocate_sprite_distances(g);
	if (!sprite_distances)
		return ;
	calculate_sprite_distances(g, sprite_distances);
	sort_sprites_by_distance(sprite_distances, g->map->n_items);
	render_sorted_sprites(g, sprite_distances, z);
	free(sprite_distances);
}

void	render_bonus(t_game *g, unsigned int w, unsigned int h)
{
	double	*z;

	if (!g->graphics->img)
		update_collected(g);
	if (g->map->time_end != -1 && mlx_get_time() - g->map->time_end > 3)
	{
		if (g->graphics->items_img)
			mlx_delete_image(g->graphics->mlx, g->graphics->items_img);
		g->map->time_end = -1;
	}
	z = build_zbuffer(g, w);
	render_scene(g, w, h);
	render_all_sprites(g, z);
	draw_minimap(g);
	free(z);
}
