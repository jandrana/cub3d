/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items_handler_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:37:55 by ana-cast          #+#    #+#             */
/*   Updated: 2025/06/13 18:17:35 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "cub3d_bonus.h"
#include "libft.h"
#include "types.h"

void	format_items(char *dest, int n_items, size_t size)
{
	char	*num_str;

	if (size < 1)
		return ;
	dest[0] = '\0';
	num_str = ft_itoa(n_items);
	ft_strlcpy(dest, "Items left: ", size);
	ft_strlcat(dest, num_str, size);
	free_str(&num_str);
}

void	finished_game_window(t_game *game)
{
	unsigned int	width;
	unsigned int	height;
	mlx_image_t		*img;
	char			str[68];

	str[0] = '\0';
	ft_strlcpy(str,
		"Congratulations! You finished the game after collecting every item",
		sizeof(str));
	width = game->graphics->mlx->width * 0.24;
	height = game->graphics->mlx->height * 0.95;
	img = mlx_put_string(game->graphics->mlx, str, width, height);
	if (!img)
		error_exit(game, E_MLX_IMAGE);
	if (!game->graphics->items_img)
	{
		if (mlx_image_to_window(game->graphics->mlx, img, width, height) == -1)
			error_exit(game, E_MLX_IMAGE2WIN);
		img->instances[0].z = 2;
	}
	else
		mlx_delete_image(game->graphics->mlx, game->graphics->items_img);
	game->graphics->items_img = img;
	game->map->time_end = mlx_get_time();
}

void	update_collected(t_game *game)
{
	mlx_image_t		*img;
	char			str[32];
	unsigned int	width;
	unsigned int	height;

	width = game->graphics->mlx->width * 0.85;
	height = game->graphics->mlx->height * 0.07;
	format_items(str, game->map->n_items - game->map->n_collected, sizeof(str));
	img = mlx_put_string(game->graphics->mlx, str, width, height);
	if (!img)
		error_exit(game, E_MLX_IMAGE);
	if (!game->graphics->items_img)
	{
		if (mlx_image_to_window(game->graphics->mlx, img, width, height) == -1)
			error_exit(game, E_MLX_IMAGE2WIN);
		img->instances[0].z = 2;
	}
	else
		mlx_delete_image(game->graphics->mlx, game->graphics->items_img);
	game->graphics->items_img = img;
	if (game->map->n_collected == game->map->n_items && game->map->n_items > 0)
		finished_game_window(game);
}

void	collected_item(t_game *game, double x, double y)
{
	bool	found_item;
	int		i;

	found_item = false;
	i = 0;
	while (game->map->n_items > i && !found_item)
	{
		if (game->map->items[i])
		{
			if ((int)x == (int)game->map->items[i].x
				&& (int)y == (int)game->map->items[i].y)
			{
				game->map->items[i].collected = true;
				game->map->n_collected++;
				update_collected(game);
				found_item = true;
			}
		}
		i++;
	}
	game->map->mt[(int)(y)][(int)(x)] = EMPTY;
}
