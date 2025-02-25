/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:10:36 by ana-cast          #+#    #+#             */
/*   Updated: 2025/02/25 17:10:57 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	print_map(t_game *game)
{
	size_t	row;

	row = 0;
	while (row <= game->map->rows)
	{
		print_row(game, row);
		row++;
	}
}

int print_row(t_game *game, size_t row)
{
	size_t	col;

	col = 0;
	while (col < game->map->cols)
	{
		printf("%c", game->map->mt[row][col]);
		col++;
	}
	printf("\n");
	return (1);
}
