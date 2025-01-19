/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:53:03 by ana-cast          #+#    #+#             */
/*   Updated: 2025/01/19 18:28:18 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// ------------------- EXT LIBRARIES ------------------- //

# include <libft.h>
# include <MLX42.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <math.h>

// ------------------ COLOR MACROS ------------------ //

# define WHITE "\033[0m"
# define BOLD "\033[1m"
# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define BLUE "\033[0;34m"
# define YELLOW "\033[33m"
# define MAGENTA "\033[35m"
# define TURQUOISE "\033[36m"

// ------------------- STRUCTURES ------------------- //

typedef enum    e_map_tile
{
    EMPTY = 0,
	WALL = 1,
    PLAYER_NORTH = 'N',
    PLAYER_SOUTH = 'S',
    PLAYER_EAST = 'E',
    PLAYER_WEST = 'W'
}	            t_map_tile;

typedef struct s_player_position
{
	unsigned int    row;
	unsigned int    col;
}				t_player_position;

typedef struct s_map
{
	unsigned int		rows;
	unsigned int		cols;
    t_player_position   player;
	t_map_tile		    **mt;
}				t_map;

typedef struct s_texture
{
    // TBD
}               t_texture;

typedef struct s_graphics
{
    mlx_t           *mlx;
    mlx_image_t     *img;
    unsigned char   floor_color[3];
    unsigned char   ceiling_color[3];
    t_texture       north_texture;
    t_texture       south_texture;
    t_texture       east_texture;
    t_texture       west_texture;
}               t_graphics;

typedef struct s_game
{
    t_map           *map;
    t_graphics      graphics;
}               t_game;


// ------------------------------------------------------ //
//                     MAIN FUNCTIONS                     //
// ------------------------------------------------------ //



#endif /* CUB3D_H */