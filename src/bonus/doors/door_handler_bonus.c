/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_handler_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:37:52 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/13 18:16:07 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "types.h"
#include "MLX42/MLX42.h"
#include "libft.h"

static	void	toggle_door(t_game *game, int y, int x)
{
	if (game->map->mt[y][x] == DOOR)
		game->map->mt[y][x] = 'o';
	else if (game->map->mt[y][x] == 'o')
		game->map->mt[y][x] = DOOR;
}

static void	toggle_doors(t_game	*game)
{
	if (valid_tile(game->player.y + 1, game->map->rows)
		&& valid_tile(game->player.x, game->map->cols))
		toggle_door(game, (int)game->player.y + 1, (int)(game->player.x));
	if (valid_tile(game->player.y - 1, game->map->rows)
		&& valid_tile(game->player.x, game->map->cols))
		toggle_door(game, (int)game->player.y - 1, (int)(game->player.x));
	if (valid_tile(game->player.y, game->map->rows)
		&& valid_tile(game->player.x + 1, game->map->cols))
		toggle_door(game, (int)game->player.y, (int)(game->player.x + 1));
	if (valid_tile(game->player.y, game->map->rows)
		&& valid_tile(game->player.x - 1, game->map->cols))
		toggle_door(game, (int)game->player.y, (int)(game->player.x - 1));
}

void	handle_door_toggle(t_game *game, bool *moved)
{
	static bool	e_prev_state = false;
	bool		e_curr_state;

	e_curr_state = mlx_is_key_down(game->graphics->mlx, MLX_KEY_E);
	if (e_curr_state && !e_prev_state)
	{
		toggle_doors(game);
		e_prev_state = e_curr_state;
		*moved = true;
	}
	e_prev_state = e_curr_state;
}
