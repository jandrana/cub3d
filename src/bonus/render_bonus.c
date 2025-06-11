/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:56:27 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/11 19:18:57 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "renderer.h"
#include "cub3d_bonus.h"

void	render_bonus(t_game *game, unsigned int width, unsigned int height)
{
	render_scene(game, width, height);
	draw_minimap(game);
}
