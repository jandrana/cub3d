/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:41:32 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/10 17:28:41 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "types.h"
# include <stddef.h>

typedef struct s_game	t_game;
typedef struct s_map	t_map;

/**
 * \brief	Line types for map file parsing
 */
typedef enum e_line_type
{
	EMPTY_LINE,
	MAP_LINE,
	TEXTURE_LINE,
	COLOR_LINE,
	INVALID_LINE
}	t_line_type;

/**
 * \brief	Parser state tracking
 */
typedef struct s_parser
{
	bool	textures[4]; // [NORTH, SOUTH, EAST, WEST] (check other textures)
	bool	floor_color;
	bool	ceiling_color;
	char	*line;
	char	**element;
	int		fd;
}	t_parser;

// ----------------- PARSER PROTOTYPES ----------------- //

	///                    parser.c:                    ///
t_map		*parser(t_game *game, int argc, char **argv);
void		update_map_sizes(t_game *game, char *filename);

	///                    file.c:                      ///
void		check_file_extension(t_game *game, const char *filename);
int			open_map_file(t_game *game, const char *filename, bool map);

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
void		parse_elements(t_game *game);

		///                    textures.c:              ///
t_direction	get_texture_direction(char *content);
bool		add_texture(mlx_texture_t *texture, t_hlist **txt_lst);
void		check_textures(t_game *game);
void		parse_texture_line(t_game *game, t_direction dir);

		///                    colors.c:                ///
int			check_color_dup(t_game *game, char identifier);
t_color		get_color(t_game *game, char **rgb);
t_color		parse_color(t_game *game, char *content, char *identifier);
void		parse_color_line(t_game *game);

void		free_parser(t_parser *parser);

#endif /* PARSER_H */