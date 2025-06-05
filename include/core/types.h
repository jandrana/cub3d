/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:41:32 by ana-cast          #+#    #+#             */
/*   Updated: 2025/05/27 19:11:23 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdint.h>	// provides uint8_t
# include <stdbool.h>	// provides bool

// Forward declarations ?
typedef struct mlx				mlx_t;
typedef struct mlx_image		mlx_image_t;
typedef struct mlx_texture		mlx_texture_t;

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

void	free_hlist(t_hlist **lst, void (*del)(void *)); // move to right place
void	delete_texture(void *texture);

#endif /* TYPES_H */