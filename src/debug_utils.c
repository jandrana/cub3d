/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:51:56 by jorvarea          #+#    #+#             */
/*   Updated: 2025/03/01 17:59:24 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	print_map(t_map *map)
{
	unsigned int	i;
	unsigned int	j;

	if (!map || !map->mt || map->rows == 0 || map->cols == 0)
	{
		printf("Invalid map or dimensions\n");
		return ;
	}
	printf("Map Dimensions: %u rows x %u cols\n", map->rows, map->cols);
	printf("Map Layout:\n");
	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			printf("%2d ", map->mt[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("Floor Color: R=%d, G=%d, B=%d\n", map->floor_color.r,
		map->floor_color.g, map->floor_color.b);
	printf("Ceiling Color: R=%d, G=%d, B=%d\n", map->ceiling_color.r,
		map->ceiling_color.g, map->ceiling_color.b);
}
