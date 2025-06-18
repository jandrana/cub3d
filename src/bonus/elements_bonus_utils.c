/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_bonus_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:28:33 by jorvarea          #+#    #+#             */
/*   Updated: 2025/06/18 19:28:41 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	is_door_or_item(t_game *game, t_line_type type)
{
	if (type == DOOR_LINE)
		game->door_texture = true;
	else
		game->item_texture = true;
}
