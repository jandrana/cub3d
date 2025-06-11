/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:17:54 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/11 15:45:05 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "libft.h"
#include "error.h"
#include <fcntl.h>

static int	number_of_occurrences(char *str, int c)
{
	int	i;
	int	n;

	i = -1;
	n = 0;
	while ((char)str[++i])
	{
		if (str[i] == (char)c)
			n++;
	}
	if ((char)c == '\0')
		return (1);
	return (n);
}

bool	check_extension(char *path, char *extension)
{
	char	*ext;
	char	*file;

	if (!path || ft_strlen(path) < ft_strlen(extension))
		return (1);
	file = ft_strrchr(path, '/');
	if (!file)
		file = path;
	if (number_of_occurrences(file, '.') != 1)
		return (1);
	ext = ft_strrchr(file, '.');
	if (!ext)
		return (1);
	if (ft_strncmp(ext, extension, ft_strlen(extension) + 1) != 0)
		return (1);
	return (0);
}

int	open_map_file(t_game *game, const char *filename)
{
	int	fd;

	if (check_extension((char *)filename, ".cub"))
		error_exit(game, E_FILE_EXT, filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit(game, E_FILE_OPEN, filename);
	return (fd);
}
