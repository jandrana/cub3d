/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:51:50 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/18 16:00:57 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include <math.h>

void	draw_circle(mlx_image_t *img, double *pos, int radius[2],
			uint32_t color)
{
	double	angle;
	double	x;
	double	y;
	int		width;

	angle = 0;
	width = radius[1];
	while (angle < 360)
	{
		x = radius[0] * cos(angle);
		y = radius[0] * sin(angle);
		mlx_put_pixel(img, pos[0] + x, pos[1] + y, color);
		angle += 0.1;
	}
	while (width > 0 && width--)
		draw_circle(img, pos, (int []){radius[0] + 1, width}, color);
}

void	draw_filled_circle(mlx_image_t *img, double *pos, int radius,
			uint32_t color)
{
	int	x;
	int	y;
	int	dx;
	int	dy;

	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			dx = x;
			dy = y;
			if (dx * dx + dy * dy <= radius * radius)
			{
				if (pos[0] + x >= 0 && pos[0] + x < img->width
					&& pos[1] + y >= 0 && pos[1] + y < img->height)
					mlx_put_pixel(img, pos[0] + x, pos[1] + y, color);
			}
			x++;
		}
		y++;
	}
}
