/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:41:32 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/18 17:57:14 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

// ---------------- BASIC MAP CHARACTERS --------------- //
# define WHITESPACE " \t\r\v\f\n"

// ------------------- PHYSICS MACROS ----------------- //
# define PI 3.14159265358979323846
# define EPSILON 0.0000001
# define INITIAL_FPS 20
# define WALK_SPEED 1.5
# define ROTATION_SPEED 1.5

// --------------- WINDOW SETTINGS MACROS -------------- //
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 1024
# define FOV 1.31946891451 // PI * 0.42
# define TILE_SIZE 20

// ------------------- UNUSED MACROS ----------------- //
# define PLAYER_HEIGHT 0.5 // CHECK USABILITY

// --------------- TERMINAL OUTPUT COLORS -------------- //
# define WHITE "\033[0m"
# define BOLD "\033[1m"
# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define BLUE "\033[0;34m"
# define YELLOW "\033[33m"
# define MAGENTA "\033[35m"
# define TURQUOISE "\033[36m"

// ------------------ MLX PIXEL COLORS ----------------- //
# define U_WHITE 0xFFFFFFFF
# define U_PINK 0xFF00FFFF
# define U_GREEN 0x00FF00FF
# define U_RED 0xFF0000FF
# define U_GREY 0x808080FF
# define U_BLACK 0x424242FF
# define U_CLEAR 0x00000000

#endif /* MACROS_H */