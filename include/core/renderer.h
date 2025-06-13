/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:43:09 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/13 13:29:12 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

# include "types.h"
# include <stddef.h>

/**
 * \brief	Wall hit information for raycasting
 */
typedef struct s_wall_hit
{
	t_direction	direction;
	t_map_tile	tile;
	double		position[2];
}	t_wall_hit;

/**
 * \brief	Wall rendering information
 */
typedef struct s_wall_info
{
	t_wall_hit		hit;
	double			height;
	double			top;
	double			bottom;
	double			distance;
	mlx_texture_t	*texture;
}	t_wall_info;

// ---------------- RENDERER PROTOTYPES ---------------- //

	///                    init_player.c:               ///
void		init_player(t_game *game);

	///                    render_scene.c:              ///
void		render_scene(t_game *game, unsigned int width,
				unsigned int height);

	///                    manage_color.c:           ///
uint32_t	manage_color(t_game *game, unsigned int row,
				unsigned int col);

uint32_t	calculate_color(t_game *game, unsigned int row, unsigned int col);

void		select_texture(t_game *game, t_wall_info *wall);

	///                    find_wall_hit.c:             ///
t_wall_hit	find_wall_hit(t_game *game, t_map_tile **mt,
				double ray_direction[2]);

bool		stop_condition(t_map_tile **mt, double position[2],
				bool *step_one, bool skip_item);

	///                    format_fps.c:                ///
void		format_fps(char *dest, size_t size, double fps);

	///                    color_utils.c:               ///
uint32_t	color_to_uint32(t_color color);

#endif /* RENDERER_H */