/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_input_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:04:04 by jorvarea          #+#    #+#             */
/*   Updated: 2025/06/13 16:47:58 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "types.h"
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include "MLX42/MLX42.h"
#include "libft.h"

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

static void	collected_item(t_game *game, double x, double y)
{
	bool	found_item;
	int		i;

	found_item = false;
	i = 0;
	while (game->map->n_items > i && !found_item)
	{
		if (&game->map->items[i]) // ?
		{
			if (floor(x) == floor(game->map->items[i].x)
				&& floor(y) == floor(game->map->items[i].y))
			{
				game->map->items[i].collected = true;
				game->map->n_collected++;
				update_collected(game);
			}
		}
		i++;
	}
	game->map->mt[(int)(y)][(int)(x)] = EMPTY;
}

static bool	move_player(t_game *game, double angle_offset)
{
	double	direction[2];
	double	move_angle;
	double	new_x;
	double	new_y;

	move_angle = game->player.angle + angle_offset;
	direction[0] = cos(move_angle);
	direction[1] = sin(move_angle);
	new_x = game->player.x + direction[0] * WALK_SPEED / game->fps;
	new_y = game->player.y + direction[1] * WALK_SPEED / game->fps;
	if (game->map->mt[(int)(new_y)][(int)(new_x)] != WALL
		&& game->map->mt[(int)(new_y)][(int)(new_x)] != DOOR)
	{
		game->player.x = new_x;
		game->player.y = new_y;
		if (game->map->mt[(int)(new_y)][(int)(new_x)] == ITEM)
		{
			if (fabs((double)(new_x - (floor(new_x + 0.5)) < 0.3))
				&& fabs((double)(new_y - (floor(new_y + 0.5)) < 0.3)))
				collected_item(game, new_x, new_y);
		}
	}
	return (true);
}

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

static void	handle_door_toggle(t_game *game, bool *moved)
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

static void	handle_movement(t_game *game, bool *moved)
{
	if (mlx_is_key_down(game->graphics->mlx, MLX_KEY_W))
		*moved = move_player(game, 0);
	if (mlx_is_key_down(game->graphics->mlx, MLX_KEY_S))
		*moved = move_player(game, PI);
	if (mlx_is_key_down(game->graphics->mlx, MLX_KEY_D))
		*moved = move_player(game, PI / 2.0);
	if (mlx_is_key_down(game->graphics->mlx, MLX_KEY_A))
		*moved = move_player(game, -PI / 2.0);
	if (mlx_is_key_down(game->graphics->mlx, MLX_KEY_RIGHT))
	{
		game->player.angle += ROTATION_SPEED / game->fps;
		*moved = true;
	}
	if (mlx_is_key_down(game->graphics->mlx, MLX_KEY_LEFT))
	{
		game->player.angle -= ROTATION_SPEED / game->fps;
		*moved = true;
	}
	if (mlx_is_key_down(game->graphics->mlx, MLX_KEY_Q))
	{
		game->cursor_locked = false;
		mlx_set_cursor_mode(game->graphics->mlx, MLX_MOUSE_NORMAL);
	}
}

void	handle_cursor_movement(t_game *game, bool *moved)
{
	int32_t	mouse_x;
	int32_t	mouse_y;
	double	delta_x;

	mlx_get_mouse_pos(game->graphics->mlx, &mouse_x, &mouse_y);
	if (mouse_x != game->graphics->mlx->width / 2)
	{
		delta_x = (mouse_x - game->graphics->mlx->width / 2);
		game->player.angle += delta_x * MOUSE_SENSITIVITY / game->fps;
		*moved = true;
	}
	mlx_set_mouse_pos(game->graphics->mlx,
		game->graphics->mlx->width / 2,
		game->graphics->mlx->height / 2);
}

void	update_sprites(t_game *game)
{
	int		i;
	t_hlist	**txt_lst;

	i = 0;
	txt_lst = game->graphics->textures_lst;
	if (!(game->frames % 30))
	{
		while (txt_lst[i] && !(game->frames % 120))
		{
			if (!(txt_lst[i]->next))
				txt_lst[i] = txt_lst[i]->head;
			else
				txt_lst[i] = txt_lst[i]->next;
			i++;
		}
		if (game->item_sprite_n < game->map->n_items && (game->frames % 120))
			game->item_sprite_n += 1;
		else
			game->item_sprite_n = 0;
	}
}

void	manage_input(void *ptr)
{
	t_game	*game;
	bool	moved;

	game = (t_game *)ptr;
	if (mlx_is_key_down(game->graphics->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(game->graphics->mlx);
		return ;
	}
	moved = false;
	handle_door_toggle(game, &moved);
	handle_movement(game, &moved);
	if (game->cursor_locked)
		handle_cursor_movement(game, &moved);
	if (!(game->frames % 60))
		update_sprites(game);
	if (moved || !(game->frames % 15))
		render_bonus(game, game->graphics->mlx->width,
			game->graphics->mlx->height);
	game->frames += 1;
}
