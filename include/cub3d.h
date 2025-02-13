/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:53:03 by ana-cast          #+#    #+#             */
/*   Updated: 2025/02/11 18:55:12 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// ------------------- EXT LIBRARIES ------------------- //

# include <error.h>
# include <libft.h>
# include <MLX42/MLX42.h>
# include <unistd.h>
# include <sys/time.h>
# include <fcntl.h>

// ------------------ COLOR MACROS ------------------ //

# define WHITE "\033[0m"
# define BOLD "\033[1m"
# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define BLUE "\033[0;34m"
# define YELLOW "\033[33m"
# define MAGENTA "\033[35m"
# define TURQUOISE "\033[36m"


// ------------------- ENUMS ------------------- //

typedef enum e_map_tile
{
	EMPTY = 0,
	WALL = 1,
	PLAYER_NORTH = 'N',
	PLAYER_SOUTH = 'S',
	PLAYER_EAST = 'E',
	PLAYER_WEST = 'W'
}	t_map_tile;

typedef enum e_direction
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
}	t_direction;

// ------------------- STRUCTURES ------------------- //

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;

typedef struct s_player
{
	double	x;
	double	y;
	double	angle; // Rotation angle (radianes)
	double	speed;
}	t_player;

typedef struct s_map
{
	unsigned int	rows;
	unsigned int	cols;
	t_player		player;
	t_map_tile		**mt;
	t_color			floor_color;
	t_color			ceiling_color;
}	t_map;

typedef struct s_graphics
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_texture_t	*textures[4]; // [NORTH, SOUTH, EAST, WEST]
}	t_graphics;

typedef struct s_game
{
	t_map		*map;
	t_graphics	*graphics;
}	t_game;


// ------------------------------------------------------ //
//                     MAIN FUNCTIONS                     //
// ------------------------------------------------------ //



#endif /* CUB3D_H */