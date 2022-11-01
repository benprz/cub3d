/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez <bperez@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 16:36:40 by bperez            #+#    #+#             */
/*   Updated: 2021/05/08 17:10:55 by bperez           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

#include <stdlib.h>

int	exit_program(t_env *env)
{
	t_sprite	*tmp;

	ft_free_2d((void **)env->game.map, env->game.map_height);
	while (env->game.sprites.list)
	{
		tmp = env->game.sprites.list;
		env->game.sprites.list = env->game.sprites.list->next;
		free(tmp);
	}
	if (env->mlx)
	{
		if (env->window)
			mlx_destroy_window(env->mlx, env->window);
	}
	exit(1);
	return (0);
}

int	error(const char *str)
{
	ft_putendl("Error, syntax error(s) or missing parameter(s)");
	if (*str)
		ft_putendl(str);
	return (0);
}

int	check_args(int argc, char **argv, t_env *env)
{
	if (argc == 2 || argc == 3)
	{
		if (ft_strlen(argv[1]) > FILE_EXTENSION_LEN && \
				!ft_strnrcmp(argv[1], FILE_EXTENSION, FILE_EXTENSION_LEN))
		{
			if (argc == 3)
			{
				if (ft_strlen(argv[2]) == SAVE_FLAG_LEN && \
						!ft_strnrcmp(argv[2], SAVE_FLAG, SAVE_FLAG_LEN))
				{
					env->save = 1;
					return (1);
				}
			}
			else
				return (1);
		}
	}
	return (error("./cub3d map.cub (--save)"));
}

int	is_void_or_sprite(t_game *game, int x, int y)
{
	if (game->map[y][x] == VOID || game->map[y][x] == SPRITE)
		return (1);
	return (0);
}

int	ft_strchrlen(char *str, char c)
{
	int	len;

	len = 0;
	if (str)
	{
		while (*str++)
		{
			if (*str == c)
				len++;
		}
	}
	return (len);
}
