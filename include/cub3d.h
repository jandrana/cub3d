/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:53:03 by ana-cast          #+#    #+#             */
/*   Updated: 2025/03/09 20:14:01 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

// ------------------- EXT LIBRARIES ------------------- //

#include "MLX42/MLX42.h"
#include "error.h"
#include <fcntl.h>
#include <libft.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

// ------------------ COLOR MACROS ------------------ //

#define WHITE "\033[0m"
#define BOLD "\033[1m"
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define BLUE "\033[0;34m"
#define YELLOW "\033[33m"
#define MAGENTA "\033[35m"
#define TURQUOISE "\033[36m"

// ------------------ PARSER MACROS ------------------ //

#define VALID_MAP_CHARS "NSEW10 \t\r\v\f\n"
#define WHITESPACE " \t\r\v\f\n"

// ------------------- RENDERER MACROS ----------------- //

#define PI 3.14159265358979323846
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define MINI 220
#define TILE_SIZE 20
#define CENTER_POS 100
#define PLAYER_HEIGHT 0.5
#define FOV (PI / 2.0)
#define EPSILON 0.0000001
#define INITIAL_FPS 30
#define WALK_SPEED 1.5
#define ROTATION_SPEED 1.5
#define MOUSE_SENSITIVITY 0.001

// ------------------- ENUMS ------------------- //

typedef enum e_map_tile {
  EMPTY = '0',
  WALL = '1',
  SPACE = ' ',
  PLAYER_NORTH = 'N',
  PLAYER_SOUTH = 'S',
  PLAYER_EAST = 'E',
  PLAYER_WEST = 'W'
} t_map_tile;

typedef enum e_direction {
  INVALID = -1,
  NORTH = 0,
  SOUTH = 1,
  EAST = 2,
  WEST = 3
} t_direction;

typedef enum e_line_type {
  EMPTY_LINE,
  MAP_LINE,
  TEXTURE_LINE,
  COLOR_LINE,
  INVALID_LINE
} t_line_type;

// ------------------- STRUCTURES ------------------- //

typedef struct s_color {
  int r;
  int g;
  int b;
} t_color;

typedef struct s_player {
  double x;
  double y;
  double angle; // Rotation angle (rad)
} t_player;

typedef struct s_map {
  unsigned int rows;
  unsigned int cols;
  t_map_tile **mt;
  t_color floor_color;
  t_color ceiling_color;
} t_map;

typedef struct s_graphics {
  mlx_t *mlx;
  mlx_image_t *img;
  mlx_image_t *minimap;
  mlx_image_t *fps;
  mlx_texture_t *textures[4]; // [NORTH, SOUTH, EAST, WEST]
} t_graphics;

typedef struct s_parser_state {
  bool textures[4]; // [NORTH, SOUTH, EAST, WEST]
  bool floor_color;
  bool ceiling_color;
} t_parser_state;

typedef struct s_cursor {
  int32_t last_cursor_x;
  int32_t last_cursor_y;
} t_cursor;

typedef struct s_game {
  t_map *map;
  t_player player;
  t_graphics *graphics;
  t_parser_state *parser_state;
  t_cursor cursor;
  char **parser_temp;
  double fps;
} t_game;

// ------------------------------------------------------ //
//                     MAIN FUNCTIONS                     //
// ------------------------------------------------------ //

//                   ERROR HANDLER                   //

void error_exit(t_game *game, const char *msg, ...);
void free_game(t_game *game);
void free_array(char ***array);

//                       PARSER                      //
t_map *parser(t_game *game, int argc, char **argv);
void update_map_sizes(t_game *game, char *filename);

//                 PARSER: ELEMENTS                //
char *parse_elements(t_game *game, int fd);

//                  COLORS                   //
int check_color_dup(t_game *game, char identifier);
t_color get_color(t_game *game, char **rgb);
t_color parse_color(t_game *game, char *content, char *identifier);
void parse_color_line(t_game *game, char *line);

//                 TEXTURES                  //
t_direction get_texture_direction(char *content);
void check_textures(t_game *game);
void parse_texture_line(t_game *game, char *line, t_direction dir);

//                    MAP                    //
void parser_map(t_game *game, int fd, char *map_line);
t_line_type check_map_line(t_game *game, char *line, size_t row);
void allocate_map_tiles(t_game *game);
void validate_map(t_game *game);

//                 RENDERER                  //
void init_player(t_game *game);
void render_scene(t_game *game, unsigned int width, unsigned int height);
uint32_t calculate_color(t_game *game, unsigned int row, unsigned int col);
uint32_t color_to_uint32(t_color color);
void format_fps(char *dest, size_t size, double fps);
void draw_minimap(t_game *game);

//                   INIT                    //
t_game *init_game(void);

//                   FILE                    //
void check_file_extension(t_game *game, const char *filename);
int open_map_file(t_game *game, const char *filename);

//                 UTILITIES                 //
int array_len(char **array);
bool check_color_value(t_color color);
t_line_type get_line_type(char *line);
void print_map(t_game *game);
int print_row(t_game *game, size_t row);

//					INPUT				     //
void manage_key_pressed(void *ptr);
void manage_mouse(mouse_key_t button, action_t action, modifier_key_t mods,
                  void *ptr);
void manage_resize(int32_t width, int32_t height, void *ptr);

#endif /* CUB3D_H */
