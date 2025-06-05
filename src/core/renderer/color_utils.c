/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:26:31 by jorvarea          #+#    #+#             */
/*   Updated: 2025/05/29 17:09:02 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

uint32_t	color_to_uint32(t_color color)
{
	return (((uint32_t)color.r << 24) | ((uint32_t)color.g << 16)
		| ((uint32_t)color.b << 8) | color.a);
}
