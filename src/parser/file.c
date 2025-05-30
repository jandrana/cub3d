/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:17:54 by ana-cast          #+#    #+#             */
/*   Updated: 2025/02/18 19:42:08 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	check_file_extension(t_game *game, const char	*filename)
{
	char	*extension;

	extension = ft_strrchr(filename, '.');
	if (!extension)
		error_exit(game, E_FILE_EXT, filename);
	if (ft_strncmp(extension, ".cub", 5) != 0)
		error_exit(game, E_FILE_EXT, extension);
}

int	open_map_file(t_game *game, const char *filename)
{
	int	fd;

	check_file_extension(game, filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit(game, E_FILE_OPEN, filename);
	return (fd);
}
