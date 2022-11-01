/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez <bperez@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 19:16:09 by bperez            #+#    #+#             */
/*   Updated: 2021/05/07 14:09:30 by bperez           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

#include <math.h>

void	init_const_values(t_game *game)
{
	game->width = game->map_width << UNIT_SIZE_SHIFT;
	game->const_values.half_fov = FOV >> 1;
	game->const_values.half_window_height = game->window_height >> 1;
	game->const_values.fov_distance =\
		(game->window_width >> 1) / tanf(rad(game->const_values.half_fov));
	game->const_values.angle_per_ray = (float)FOV / game->window_width;
	game->const_values.unit_size_on_fov_distance =\
		UNIT_SIZE * game->const_values.fov_distance;
	game->const_values.half_unit_size = UNIT_SIZE >> 1;
}

int	draw_background(t_env *env, t_game *game, t_background *background)
{
	int	half_window;

	background->layer = mlx_new_image(
			env->mlx,
			env->game.window_width,
			env->game.window_height);
	if (background->layer)
	{
		background->layer_data = (t_rgba *)mlx_get_data_addr(
				background->layer,
				&background->bits_per_pixel,
				&background->size_line,
				&background->big_endian);
		half_window = game->window_size >> 1;
		ft_memset_uint32(
			game->background.layer_data,
			game->ceiling_color.value,
			half_window);
		ft_memset_uint32(
			game->background.layer_data + half_window,
			game->floor_color.value,
			half_window);
		return (1);
	}
	return (0);
}

int	init_sprites(t_env *env, t_game *game)
{
	game->sprites.layer = mlx_new_image(
			env->mlx,
			env->game.window_width,
			env->game.window_height);
	if (game->sprites.layer)
	{
		game->sprites.layer_data = (t_rgba *)mlx_get_data_addr(
				game->sprites.layer,
				&game->sprites.bits_per_pixel,
				&game->sprites.size_line,
				&game->sprites.big_endian);
		return (1);
	}
	return (0);
}

void	refresh_window(t_env *env, t_game *game)
{
	ft_memset_uint32(env->layer_data, TRANSPARENT_VALUE, game->window_size);
	ft_memset_uint32(
		game->sprites.layer_data,
		TRANSPARENT_VALUE,
		game->window_size);
	draw_screen(env, game);
	mlx_put_image_to_window(
		env->mlx,
		env->window,
		game->background.layer, 0, 0);
	mlx_put_image_to_window(env->mlx, env->window, env->layer, 0, 0);
	mlx_put_image_to_window(env->mlx, env->window, game->sprites.layer, 0, 0);
}

void	launch_game(t_env *env, t_game *game)
{
	init_const_values(game);
	if (draw_background(env, game, &game->background))
	{
		if (init_sprites(env, game))
		{
			game->env = env;
			refresh_window(env, game);
		}
		else
		{
			error("Initialitzation of the sprites layer failed");
			exit_program(env);
		}
	}
	else
	{
		error("Initialitzation of the background layer failed");
		exit_program(env);
	}
}
