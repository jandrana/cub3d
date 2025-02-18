/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:55:12 by ana-cast          #+#    #+#             */
/*   Updated: 2025/02/18 18:52:53 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

// ------------------- ARGUMENT ERRORS ------------------- //
# define E_ARGS_COUNT "Invalid number of arguments. Usage: %s <map.cub>" // arg0

// ------------------- FILE ERRORS ------------------- //
# define E_FILE_OPEN "Failed to open file: %s"                   // file_path
# define E_FILE_EXT "Invalid file extension: %s (expected .cub)" // file_path
# define E_FILE_PERM "Permission denied: %s"                     // file_path
# define E_FILE_READ "Error reading file: %s"                    // file_path

// ------------------- MAP ERRORS ------------------- //
# define E_MAP_EMPTY "Empty map or missing map section"			// no args
# define E_MAP_FORMAT "Invalid map format: %s"					// error_detail
# define E_MAP_SIZE "Invalid map dimensions: %dx%d"				// width, height
# define E_MAP_WALLS "Map not properly enclosed with walls"		// no args
# define E_MAP_PLAYER "Invalid player configuration: %s"		// error_detail
# define E_MAP_CHAR "Invalid character in map: '%c' at [%d,%d]"	// char row,col
# define E_MAP_MULTI_PLAYER "Multiple player positions found"	// no args
# define E_MAP_NO_PLAYER "No player position found in map"		// no args

// ------------------- TEXTURE ERRORS ------------------- //
# define E_TEX_MISSING "Missing texture for %s direction"	// NO/SO/WE/EA
# define E_TEX_INVALID "Invalid texture path: %s"			// texture_path
# define E_TEX_LOAD "Failed to load texture: %s"			// texture_path

// ------------------- COLOR ERRORS ------------------- //
# define E_COLOR_FORMAT "Invalid color format for %s: %s"     // F/C, value
# define E_COLOR_RANGE "Color value out of range [0-255]: %s" // color_value
# define E_COLOR_MISSING "Missing color definition for %s"    // type (F/C)

// ------------------- MEMORY ERRORS ------------------- //
# define E_MEM_ALLOC "Memory allocation failed: %s" // component_name

// ------------------- MLX ERRORS ------------------- //
# define E_MLX_INIT "Failed to initialize MLX: %s"  // error_detail
# define E_MLX_WINDOW "Failed to create window: %s" // error_detail
# define E_MLX_IMAGE "Failed to create image: %s"   // error_detail

// ------------------- RESOURCE ERRORS ------------------- //
# define E_RES_LOAD "Failed to load resource: %s" // resource_path
# define E_RES_FREE "Failed to free resource: %s" // resource_name

#endif /* ERROR_H */
