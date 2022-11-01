/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez <bperez@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 16:36:55 by bperez            #+#    #+#             */
/*   Updated: 2021/05/07 14:01:12 by bperez           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

#include <math.h>
#include <stdlib.h>

static int	create_window(t_env *env, char *title)
{
	env->window = mlx_new_window(
			env->mlx,
			env->game.window_width,
			env->game.window_height,
			title);
	return (env->window != NULL);
}

int	create_layer(t_env *env)
{
	env->layer = mlx_new_image(
			env->mlx,
			env->game.window_width,
			env->game.window_height);
	if (env->layer)
	{
		env->layer_data = (t_rgba *)mlx_get_data_addr(
				env->layer,
				&env->bits_per_pixel,
				&env->size_line,
				&env->big_endian);
	}
	return (env->layer != NULL);
}

int	init_texture(t_env *env, t_texture *texture)
{
	texture->layer = mlx_xpm_file_to_image(
			env->mlx,
			texture->file_path,
			&texture->width,
			&texture->height);
	if (texture->layer)
	{
		texture->layer_data = (t_rgba *)mlx_get_data_addr(
				texture->layer,
				&texture->bits_per_pixel,
				&texture->size_line,
				&texture->big_endian);
		texture->size = texture->width * texture->height;
	}
	return (texture->layer != NULL);
}

int	init_textures(t_env *env, t_textures *textures)
{
	if (!init_texture(env, &textures->north_texture) || \
		!init_texture(env, &textures->south_texture) || \
		!init_texture(env, &textures->west_texture) || \
		!init_texture(env, &textures->east_texture) || \
		!init_texture(env, &textures->sprite_texture))
		return (error("Couldn't load one or multiple texture(s)"));
	return (1);
}

int	main(int argc, char **argv)
{
	t_env	env;

	ft_bzero(&env, sizeof(t_env));
	if (check_args(argc, argv, &env) && parse_file(&env.game, argv[1]))
	{
		env.mlx = mlx_init();
		if (env.mlx)
		{
			if (env.save == 1)
				bmp_screenshot(&env, &env.game);
			else if (create_window(&env, argv[1]) && create_layer(&env))
			{
				if (init_textures(&env, &env.game.textures))
				{
					mlx_hook(env.window, 17, 0, exit_program, &env);
					mlx_hook(env.window, 2, 1L << 0, handle_keys, &env);
					launch_game(&env, &env.game);
					mlx_loop(env.mlx);
				}
			}
		}
	}
	exit_program(&env);
	return (ERROR);
}
