/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez <bperez@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 11:46:19 by bperez            #+#    #+#             */
/*   Updated: 2021/05/07 11:46:22 by bperez           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static int	fix_rows_length(t_game *game)
{
	int	i;
	int	length;

	i = 0;
	while (game->map[i])
	{
		length = game->map_width - ft_strlen(game->map[i]);
		if (length)
		{
			game->map[i] = ft_tmp(game->map[i], \
					ft_strlengthen(game->map[i], length, VOID));
			if (!game->map[i])
				return (error("Unknown memory problem"));
		}
		i++;
	}
	return (1);
}

static int	check_map(t_game *game, int x, int y)
{
	if (game->map[y][x] == VOID)
		game->map[y][x] = VOID_TMP;
	if (game->map[y][x] == SPRITE)
		game->map[y][x] = SPRITE_TMP;
	if (x == 0 || x == game->map_width - 1 || \
		y == 0 || y == game->map_height - 1)
		return (0);
	if (is_void_or_sprite(game, x, y + 1) && !check_map(game, x, y + 1))
		return (0);
	if (is_void_or_sprite(game, x + 1, y + 1) && !check_map(game, x + 1, y + 1))
		return (0);
	if (is_void_or_sprite(game, x + 1, y) && !check_map(game, x + 1, y))
		return (0);
	if (is_void_or_sprite(game, x + 1, y - 1) && !check_map(game, x + 1, y - 1))
		return (0);
	if (is_void_or_sprite(game, x, y - 1) && !check_map(game, x, y - 1))
		return (0);
	if (is_void_or_sprite(game, x - 1, y - 1) && !check_map(game, x - 1, y - 1))
		return (0);
	if (is_void_or_sprite(game, x - 1, y) && !check_map(game, x - 1, y))
		return (0);
	if (is_void_or_sprite(game, x - 1, y + 1) && !check_map(game, x - 1, y + 1))
		return (0);
	return (1);
}

int	last_checks_map(t_game *game, char *player)
{
	int	i;

	if (!player)
		return (error("Missing player position in the map (N,S,W,E)"));
	fix_rows_length(game);
	if (!(check_map(game, game->player.pos.x_map, game->player.pos.y_map)))
		return (error("The map needs to be closed/surrounded by walls"));
	i = 0;
	while (game->map[i])
	{
		ft_strcreplace(game->map[i], VOID_TMP, VOID);
		ft_strcreplace(game->map[i++], SPRITE_TMP, SPRITE);
	}
	return (1);
}
