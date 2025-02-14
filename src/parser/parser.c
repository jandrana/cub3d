/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:57:43 by ana-cast          #+#    #+#             */
/*   Updated: 2025/02/13 20:51:05 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	check_file_type(char *str, char *type)
{
	int	i;
	int	j;

	i = ft_strlen(str) - 1;
	j = 3;
	while (str[i] && j >= 0)
	{
		if (str[i] != type[j])
			return (0);
		i--;
		j--;
	}
	return (1);
}

t_map	*parser(int argc, char **argv)
{
	t_map	*map;
	int		fd;

	map = (t_map *)malloc(sizeof(t_map));
	if (argc == 2)
	{
		if (!check_file_type(argv[1], ".cub"))
			error_exit(NULL, E_FILE_EXT, argv[1]);
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			error_exit(NULL, E_FILE_OPEN, argv[1]);
	}
	else
		error_exit(NULL, E_ARGS_COUNT, argv[0]);
	return (map);
}

