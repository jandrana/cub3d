/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_mandatory.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:53:03 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/18 18:29:22 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_MANDATORY_H
# define CUB3D_MANDATORY_H

// ------------------- CORE INCLUDES ------------------- //

# include "MLX42/MLX42.h"
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

// ---------------- MANDATORY FUNCTIONS ---------------- //

// ----------------- PARSER PROTOTYPES ----------------- //

	///                    parser.c:                    ///
t_map		*parser(t_game *game, int argc, char **argv);
void		parse_elements(t_game *game);
void		validate_map(t_game *game);
void		allocate_structures(t_game *game);

///                manage_input.c:                      /// (missing -> static)
/**
 * \brief		Input handler for mandatory game
 * \param ptr	Pointer to game structure
 */
void		manage_input(void *ptr);

///                manage_resize.c:                     /// (missing -> static)
/**
 * \brief			Window resize handler for mandatory game
 * \param width		New window width
 * \param height	New window height
 * \param ptr		Pointer to game structure
 */
void		manage_resize(int32_t width, int32_t height, void *ptr);

// ------------------- MISSING ORGANIZATION ------------------- //

#endif /* CUB3D_MANDATORY_H */
