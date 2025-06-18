/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:41:32 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/18 19:30:01 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

// ------------------- CORE INCLUDES ------------------- //

# define IS_BONUS 1

# include "../core/error.h"
# include "../core/game.h"
# include "../core/init.h"
# include "../core/macros.h"
# include "../core/parser.h"
# include "../core/renderer.h"
# include "../core/types.h"
# include "free_bonus.h"

// -------------------- BONUS MACROS ------------------- //

# define MINI 220 // UNUSED
# define MINI_R 100
# define VISION_R 100
# define ORIG 100 // UNUSED
# define MOUSE_SENSITIVITY 0.02
# define BONUS 1

# define NO_REACH_PLAYER "1 VC"
# define VALID_MAP_CHARS "NSEW10ID \t\r\v\f\n"
# define NEAR_PLAYABLE "NSEW10ID"
# define NEAR_SPACE " 1\n"
# define ALLOW_SPRITES 1

typedef enum e_textures_minimap // not used?
{
	// M_COMPASS = 0,
	M_FLOOR = 1,
	M_WALL = 2,
	M_SPACE = 3
}		t_textures_map;

// ------------------ BONUS FUNCTIONS ------------------ //

t_map	*parser_bonus(t_game *game, int argc, char **argv);
void	parse_elements(t_game *game);
void	validate_map(t_game *game);
void	update_map_items(t_game *game);
void	parse_bonus_textures(t_game *game, t_line_type type);
void	is_door_or_item(t_game *game, t_line_type type);

/**
 * \brief	Initializes the game bonus structure
 */
t_game	*init_game_bonus(void);
void	allocate_structures(t_game *game); // unused

/**
 * \brief		Input handler for bonus game
 * \param ptr	Pointer to game structure
 */
void	manage_input(void *ptr);

/**
 * \brief			Window resize handler for bonus game
 * \param width		New window width
 * \param height	New window height
 * \param ptr		Pointer to game structure
 */
void	manage_resize(int32_t width, int32_t height, void *ptr);

void	render_bonus(t_game *game, unsigned int width, unsigned int height);
void	update_collected(t_game *game);
void	render_items(t_game *game);
double	get_distance(double x1, double x2, double y1, double y2);
double	get_angle(t_game *game, double x, double y);
void	get_tex_xy(uint32_t tex_xy[2], mlx_texture_t *tex, double size[2],
			int px[2]);
bool	stop_items(t_map_tile **mt, double position[2], bool *step_one,
			t_item item);

// ------------------------------------------------- //
//                  MINIMAP FOLDER                   //
// ------------------------------------------------- //

///                    minimap.c:               ///
void	draw_circle(mlx_image_t *img, double *pos, int radius[2],
			uint32_t color);
void	draw_filled_circle(mlx_image_t *img, double *pos, int radius,
			uint32_t color);

void	draw_minimap(t_game *game);

///                    vision_utils.c:          ///
char	get_tile_pos_type(t_map *map, double *pos);
bool	vision_hits_wall(t_game *game, double center, double *pos);

///                    item_utils.c:            ///
void	clear_map_items(t_mini_item **lst);
void	add_minimap_items(t_game *g, t_mini_item **map_items, double *rel_pos);
void	draw_items(t_game *game, t_mini_item *map_items);

// ------------------------------------------------- //
//                    DOORS FOLDER                   //
// ------------------------------------------------- //

///                    door_handler_bonus.c:   ///
void	handle_door_toggle(t_game *game, bool *moved);

// ------------------------------------------------- //
//                    ITEMS FOLDER                   //
// ------------------------------------------------- //

///                    items_handler_bonus.c:   ///
void	check_collected_item(t_game *game);

#endif /* CUB3D_BONUS_H */