/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:41:32 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/18 16:17:33 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "types.h"
# include <stddef.h> 

/**
 * \brief	Line types for map file parsing
 */
typedef enum e_line_type
{
	EMPTY_LINE,
	MAP_LINE,
	TEXTURE_LINE,
	COLOR_LINE,
	DOOR_LINE,
	ITEM_LINE,
	INVALID_LINE
}	t_line_type;

// ----------------- PARSER PROTOTYPES ----------------- //

	///                    parser.c:                    ///
void		update_map_sizes(t_game *game, char *filename);

	///                    file.c:                      ///
bool		check_extension(char *path, char *extension);
int			open_map_file(t_game *game, const char *filename);

	///                    map.c:                       /// (todo: items prot)
void		parser_map(t_game *game);
void		allocate_map_tiles(t_game *game);
t_line_type	check_map_line(t_game *game, char *line, size_t row); // used?

	///                    validate_map.c:              /// (missing -> static)
void		validate_near_tiles(t_game *game, size_t row, size_t col);
bool		valid_tile(size_t tile, size_t max_tile);

	///                    utils.c:                     /// (missing ->static)
int			array_len(char **array);
t_line_type	get_line_type(char *line);
void		print_map(t_game *game); // used? (print_utils.c)
int			print_row(t_game *game, size_t row); // used? (print_utils.c)

	///                    hlst_utils.c:                     ///
t_hlist		*hslt_new_node(void *content, t_hlist *head);
t_hlist		*hlst_last_node(t_hlist *lst);
void		hlstadd_back(t_hlist **lst, t_hlist *node);

	// ------------------------------------------------- //
	//                  ELEMENTS FOLDER                  //
	// ------------------------------------------------- //

		///                    textures.c:              ///
t_direction	get_texture_direction(char *content);
char		*get_direction_name(t_direction dir);
bool		add_texture(mlx_texture_t *texture, t_hlist **txt_lst);
void		parse_texture_line(t_game *game, t_direction dir);
char		*path_from_texture(t_game *game, t_parser *parser);

		///                    colors.c:                ///
t_color		get_color(t_game *game, char **rgb);
t_color		parse_color(t_game *game, char *content, char *identifier);
void		parse_color_line(t_game *game);

		///                    check.c:              ///
bool		check_color_value(t_color color);
int			check_color_dup(t_game *game, char identifier);
void		check_missing_values(t_game *game);
void		check_textures(t_game *game);

void		free_parser(t_parser *parser);

#endif /* PARSER_H */