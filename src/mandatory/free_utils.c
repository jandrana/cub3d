/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:59:21 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/11 15:49:51 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "MLX42/MLX42.h"

void	free_game(t_game *game)
{
	if (!game)
		return ;
	free_core_game(game);
	if (game->graphics && game->graphics->mlx)
		mlx_terminate(game->graphics->mlx);
	safe_free(game->map);
	safe_free(game->graphics);
	safe_free(game);
}
