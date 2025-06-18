/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:41:32 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/18 19:18:57 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdint.h>
# include <stdbool.h>
# include "MLX42/MLX42.h"

// --------------------- CORE TYPES -------------------- //
typedef struct s_color
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;
}	t_color;

typedef struct s_hlist
{
	void			*content;
	struct s_hlist	*head;
	struct s_hlist	*next;
}					t_hlist;

// Game types and structures
/**
 * \brief	Map tile types
 */
typedef enum e_map_tile
{
	EMPTY = '0',
	WALL = '1',
	SPACE = ' ',
	PLAYER_NORTH = 'N',
	PLAYER_SOUTH = 'S',
	PLAYER_EAST = 'E',
	PLAYER_WEST = 'W',
	ITEM = 'I',
	DOOR = 'D'
}	t_map_tile;

typedef enum e_direction
{
	INVALID = -1,
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
	//D_ITEM = 4,
	//D_DOOR = 5
}	t_direction;

typedef struct s_mini_item
{
	double				rel_x;
	double				rel_y;
	struct s_mini_item	*next;
}	t_mini_item;

/**
 * \brief	Parser state tracking
 */
typedef struct s_parser
{
	bool	textures[4];
	bool	floor_color;
	bool	ceiling_color;
	char	*line;
	char	**element;
	int		fd;
}	t_parser;

# ifdef IS_BONUS

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
	double	sprite_frame;
}	t_player;

typedef struct s_item_info
{
	double			dx;
	double			dy;
	double			dist;
	double			angle;
	double			offset;
	double			pos[2];
	double			size[2];
	mlx_texture_t	*tex;
}	t_item_info;

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
	double			time_end;
}	t_map;

typedef struct s_graphics
{
	mlx_t			*mlx;
	t_hlist			*textures_lst[5];
	mlx_image_t		*img;
	mlx_image_t		*fps;
	mlx_image_t		*minimap;
	mlx_image_t		*items_img;
	mlx_texture_t	*door_lst;
	mlx_texture_t	*items_lst;
}	t_graphics;

typedef struct s_game
{
	t_map			*map;
	t_player		player;
	t_graphics		*graphics;
	t_parser		*parser;
	double			fps;
	long			frames;
	int				item_sprite_n;
	bool			cursor_locked;
	bool			door_texture;
	bool			item_texture;
}	t_game;

# else

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
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
	mlx_image_t	*img;
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
	t_parser		*parser;
	double			fps;
	long			frames;
}	t_game;

# endif /* IS_BONUS */

void	free_hlist(t_hlist **lst, void (*del)(void *));
void	delete_texture(void *texture);

#endif /* TYPES_H */