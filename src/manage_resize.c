/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_resize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:44:23 by jorvarea          #+#    #+#             */
/*   Updated: 2025/03/02 17:21:02 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	manage_resize(int32_t width, int32_t height, void *ptr)
{
	t_game	*game;

	game = (t_game *)ptr;
	render_scene(game, width, height);
}
