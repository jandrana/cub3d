/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:41:32 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/10 17:29:45 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

// ------------------- CORE INCLUDES ------------------- //

# include "core/error.h"
# include "core/game.h"
# include "core/macros.h"
# include "core/parser.h"
# include "core/renderer.h"
# include "core/types.h"
# include "core/init.h"
# include "bonus/free_bonus.h"

// -------------------- BONUS MACROS ------------------- //

# define MINI 220 // UNUSED
# define MINI_R 100
# define VISION_R 100
# define ORIG 100 // UNUSED
# define MOUSE_SENSITIVITY 0.02
# define BONUS 1

# define NO_REACH_PLAYER "1 VC"
# define VALID_MAP_CHARS "NSEW10I \t\r\v\f\n"
# define NEAR_PLAYABLE "NSEW10I"
# define NEAR_SPACE " 1\n"
# define ALLOW_SPRITES 1

typedef enum e_map_tile_bonus
{
	ITEM = 'I',
	DOOR = 'D'
}	t_map_tile_bonus;

typedef enum e_textures_minimap // not used?
{
	//M_COMPASS = 0,
	M_FLOOR = 1,
	M_WALL = 2,
	M_SPACE = 3
}	t_textures_map;

// ------------------ BONUS STRUCTURES ----------------- //

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
	double	sprite_frame; // only bonus
}	t_player;

typedef struct s_item
{
	double			x;
	double			y;
	bool			collected;
	double			sprite_frame;
}	t_item;

typedef struct s_map
{
	unsigned int	rows;
	unsigned int	cols;
	t_map_tile		**mt;
	t_color			floor_color;
	t_color			ceiling_color;
	t_item			*items;
	int				n_items;
	int				n_collected;
}	t_map;

typedef struct s_mini_item
{
	double				rel_x;
	double				rel_y;
	struct s_mini_item	*next;
}	t_mini_item; // change with t_2D_item

typedef struct s_graphics
{
	mlx_t		*mlx;
	t_hlist		*textures_lst[4]; // [NORTH, SOUTH, EAST, WEST]
	mlx_image_t	*img;
	mlx_image_t	*fps;
	mlx_image_t	*minimap; //implement minimap in its own image
	t_hlist		*door_lst[4]; //implement door textures
	t_hlist		*items_lst[9];
	bool		skip_item;
}	t_graphics;

typedef struct s_game
{
	t_map			*map;
	t_player		player;
	t_graphics		*graphics;
	t_parser		*parser;
	double			fps;
	long			frames;
	int				item_sprite_n; // only bonus, check use
	bool			cursor_locked; // only bonus, check use
}	t_game;

// ------------------ BONUS FUNCTIONS ------------------ //

/**
 * \brief	Initializes the game bonus structure 
 */
t_game		*init_game_bonus(void);


/**
 * \brief		Input handler for bonus game
 * \param ptr	Pointer to game structure
 */
void		manage_input(void *ptr);

/**
 * \brief			Window resize handler for bonus game
 * \param width		New window width
 * \param height	New window height
 * \param ptr		Pointer to game structure
 */
void		manage_resize(int32_t width, int32_t height, void *ptr);

	// ------------------------------------------------- //
	//                  MINIMAP FOLDER                   //
	// ------------------------------------------------- //

		///                    minimap.c:               ///
void		draw_circle(mlx_image_t *img, double *pos, int radius,
				uint32_t color, int w);

void		draw_minimap(t_game *game);

		///                    vision_utils.c:          ///
char		get_tile_pos_type(t_map *map, double *pos);
bool		vision_hits_wall(t_game *game, double center, double *pos);

		///                    item_utils.c:            ///
void		clear_map_items(t_mini_item **lst);
void		add_minimap_items(t_game *g, t_mini_item **map_items,
				double *rel_pos);
void		draw_items(t_game *game, t_mini_item *map_items);

#endif /* CUB3D_BONUS_H */