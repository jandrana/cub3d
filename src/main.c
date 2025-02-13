/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 16:27:29 by jorvarea          #+#    #+#             */
/*   Updated: 2025/02/13 20:55:58 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_game	*init_game(void)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	game->map = NULL;
	game->graphics = NULL;
	return (game);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = init_game();
	game->map = parser(argc, argv);
	return (0);
}
