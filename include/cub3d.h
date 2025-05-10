/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:53:03 by ana-cast          #+#    #+#             */
/*   Updated: 2025/05/10 22:24:58 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// ------------------- EXT LIBRARIES ------------------- //

# include "MLX42/MLX42.h"
# include "error.h"
# include <fcntl.h>
# include <libft.h>
# include <math.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

// ------------------ COLOR MACROS ------------------ //

# define WHITE "\033[0m"
# define BOLD "\033[1m"
# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define BLUE "\033[0;34m"
# define YELLOW "\033[33m"
# define MAGENTA "\033[35m"
# define TURQUOISE "\033[36m"

// ------------------ U_INT COLORS ------------------ //

# define U_WHITE 0xFFFFFFFF
# define U_PINK 0xFF00FFFF
# define U_GREEN 0x00FF00FF
# define U_RED 0xFF0000FF
# define U_GREY 0x808080FF
# define U_BLACK 0x424242FF
# define U_CLEAR 0x00000000

// ------------------ PARSER MACROS ------------------ //

# define VALID_MAP_CHARS "NSEW10I \t\r\v\f\n" // bonus
# define WHITESPACE " \t\r\v\f\n"

// ------------------- RENDERER MACROS ----------------- //

# define PI 3.14159265358979323846
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 1024
# define MINI 220
# define MINI_R 100
# define VISION_R 100
# define TILE_SIZE 20
# define ORIG 100
# define PLAYER_HEIGHT 0.5
# define FOV (PI * 0.42)
# define EPSILON 0.0000001
# define INITIAL_FPS 20
# define WALK_SPEED 1.5
# define ROTATION_SPEED 1.5
# define MOUSE_SENSITIVITY 0.02

// ------------------- ENUMS ------------------- //

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
	WEST = 3,
	D_ITEM = 4,
  D_DOOR = 5
}	t_direction;

typedef enum e_textures_map
{
	M_COMPASS = 0,
	M_FLOOR = 1,
	M_WALL = 2,
	M_SPACE = 3
}	t_textures_map;

typedef enum e_line_type
{
	EMPTY_LINE,
	MAP_LINE,
	TEXTURE_LINE,
	COLOR_LINE,
	INVALID_LINE
}	t_line_type;

// ------------------- STRUCTURES ------------------- //

typedef struct s_color
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;
}	t_color;

typedef struct s_player
{
	double	x;
	double	y;
	double	angle; // Rotation angle (rad)
}	t_player;

typedef struct s_item
{
	double			x;
	double			y;
	bool			  collected;
	double			sprite_frame;
}	t_item;

typedef struct s_mini_item
{
	double				rel_x;
	double				rel_y;
	struct s_mini_item	*next;
}	t_mini_item;

typedef struct s_map
{
	unsigned int	rows;
	unsigned int	cols;
	t_map_tile		**mt;
	t_color			  floor_color;
	t_color			  ceiling_color;
	t_item			  *items;
	int				    n_items;
	int				    n_collected;
}	t_map;

typedef struct s_hlist
{
	struct s_hlist	*head;
	void			      *content;
	struct s_hlist	*next;
}					t_hlist;

typedef struct s_graphics {
  mlx_t       *mlx;
  mlx_image_t *img;
  mlx_image_t *minimap;
  mlx_image_t *fps;
  bool		    skip_item;
  t_hlist	    *textures_lst[6];  // [NORTH, SOUTH, EAST, WEST, ITEM, DOOR]
} t_graphics;

typedef struct s_parser_state
{
	bool	textures[4]; // [NORTH, SOUTH, EAST, WEST]
	bool	floor_color;
	bool	ceiling_color;
}	t_parser_state;

typedef struct s_game
{
	t_map			       *map;
	t_player		      player;
	t_graphics		    *graphics;
	t_parser_state	  *parser_state;
	char			        **parser_temp;
	double			      fps;
	bool			        cursor_locked;
	long			        frames;
}	t_game;

// ------------------- calculate_color STRUCTURES ------------------- //

typedef struct s_wall_hit
{
	t_direction	direction;
  t_map_tile tile;
	double		position[2];
}	t_wall_hit;

typedef struct s_wall_info
{
	t_wall_hit		hit;
	double			  height;
	double			  top;
	double			  bottom;
	double			  distance;
	mlx_texture_t	*texture;
}	t_wall_info;

// ------------------------------------------------------ //
//                     MAIN FUNCTIONS                     //
// ------------------------------------------------------ //

///                error_handler.c:                     ///
void		error_exit(t_game *game, const char *msg, ...);
void		free_game(t_game *game);
void		free_array(char ***array);

///                manage_input.c:                      /// (missing -> static)
void		manage_input(void *ptr);

///                manage_resize.c:                     /// (missing -> static)
void		manage_resize(int32_t width, int32_t height, void *ptr);

// ----------------------------------------------------- //
//                     PARSER FOLDER                     //
// ----------------------------------------------------- //

	///                    init.c:                      ///
t_game		*init_game(void);

	///                    parser.c:                    ///
t_map		*parser(t_game *game, int argc, char **argv);
void		update_map_sizes(t_game *game, char *filename);

	///                    file.c:                      ///
void		check_file_extension(t_game *game, const char *filename);
int			open_map_file(t_game *game, const char *filename);

	///                    map.c:                       /// (todo: items prot)
void		parser_map(t_game *game, int fd, char *map_line);
void		allocate_map_tiles(t_game *game);
t_line_type	check_map_line(t_game *game, char *line, size_t row); // used?

	///                    validate_map.c:              /// (missing -> static)
void		validate_map(t_game *game);

	///                    utils.c:                     /// (missing ->static)
int			array_len(char **array);
bool		check_color_value(t_color color);
t_line_type	get_line_type(char *line);
void		print_map(t_game *game); // used? (print_utils.c)
int			print_row(t_game *game, size_t row); // used? (print_utils.c)

	// ------------------------------------------------- //
	//                  ELEMENTS FOLDER                  //
	// ------------------------------------------------- //

		///                    elements.c:              ///
char		*parse_elements(t_game *game, int fd);

		///                    textures.c:              ///
t_direction	get_texture_direction(char *content);
bool		add_texture(mlx_texture_t *texture, t_hlist **txt_lst);
void		check_textures(t_game *game);
void		parse_texture_line(t_game *game, char *line,
				t_direction dir);

		///                    colors.c:                ///
int			check_color_dup(t_game *game, char identifier);
t_color		get_color(t_game *game, char **rgb);
t_color		parse_color(t_game *game, char *content, char *identifier);
void		parse_color_line(t_game *game, char *line);

// ----------------------------------------------------- //
//                    RENDERER FOLDER                    //
// ----------------------------------------------------- //

	///                    init_player.c:               ///
void		init_player(t_game *game);

	///                    render_scene.c:              ///
void		render_scene(t_game *game, unsigned int width,
				unsigned int height);

	///                    manage_color.c:           ///
uint32_t	manage_color(t_game *game, unsigned int row,
				unsigned int col);

	///                    find_wall_hit.c:             ///
t_wall_hit	find_wall_hit(t_game *game, t_map_tile **mt,
				double ray_direction[2]);

	///                    format_fps.c:                ///
void		format_fps(char *dest, size_t size, double fps);

	///                    color_utils.c:               ///
uint32_t	color_to_uint32(t_color color);

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

#endif /* CUB3D_H */
