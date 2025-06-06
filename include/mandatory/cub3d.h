/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:53:03 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/06 15:16:48 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// ------------------- CORE INCLUDES ------------------- //

# include "MLX42/MLX42.h" // update dependencies
# include "../core/error.h"
# include "../core/game.h"
# include "../core/macros.h"
# include "../core/parser.h"
# include "../core/renderer.h"
# include "../core/types.h"
# include "../core/init.h"
# include "free.h"

// ------------------ MANDATORY MACROS ----------------- //

# define NO_REACH_PLAYER "1 V"
# define VALID_MAP_CHARS "NSEW10 \t\r\v\f\n"
# define NEAR_PLAYABLE "NSEW10"
# define NEAR_SPACE " 1\n"
# define ALLOW_SPRITES 0

// ---------------- MANDATORY STRUCTURES --------------- //

typedef struct s_player
{
	double	x;
	double	y;
	double	angle; // Rotation angle (rad)
}	t_player;

typedef struct s_map
{
	unsigned int	rows;
	unsigned int	cols;
	t_map_tile		**mt;
	t_color			floor_color;
	t_color			ceiling_color;
}	t_map;

// Game Graphics 
typedef struct s_graphics
{
	mlx_t		*mlx;
	t_hlist		*textures_lst[4];
	mlx_image_t	*img; // rework for no sprites in no bonus, fix leaks bonus
	mlx_image_t	*fps;
}	t_graphics;

/**
 * \brief	Main game structure for mandatory part
 */
typedef struct s_game
{
	t_map			*map;
	t_player		player;
	t_graphics		*graphics;
	t_parser_state	*parser_state;
	char			**parser_temp;
	double			fps;
	long			frames;
}	t_game;

// ---------------- MANDATORY FUNCTIONS ---------------- //

///                manage_input.c:                      /// (missing -> static)
/**
 * \brief		Input handler for mandatory game
 * \param ptr	Pointer to game structure
 */
void	manage_input(void *ptr);

///                manage_resize.c:                     /// (missing -> static)
/**
 * \brief			Window resize handler for mandatory game
 * \param width		New window width
 * \param height	New window height
 * \param ptr		Pointer to game structure
 */
void	manage_resize(int32_t width, int32_t height, void *ptr);

// ------------------- MISSING ORGANIZATION ------------------- //

#endif /* CUB3D_H */
