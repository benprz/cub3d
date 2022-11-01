/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez <bperez@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 16:36:40 by bperez            #+#    #+#             */
/*   Updated: 2021/03/23 11:38:22 by bperez           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

#include <math.h>

float	calc_distance_rad(t_player *player, t_vector *point, float angle)
{
	float		distance;
	t_vector	*pos;

	pos = &player->pos;
	distance = sqrtf(
			(pos->x - point->x) * (pos->x - point->x) + \
			(pos->y - point->y) * (pos->y - point->y));
	return (distance * cosf(rad(ft_abs(player->orientation - angle))));
}

int	check_map_boundaries(t_game *game, t_vector *point)
{
	if (point->x_map < 0 || point->y_map < 0 || \
			point->x_map >= game->map_width || point->y_map >= game->map_height)
		return (1);
	return (0);
}

int	find_wall(t_game *game, t_vector *point, float x, float y)
{
	while (1)
	{
		point->x_map = point->x / UNIT_SIZE;
		point->y_map = point->y / UNIT_SIZE;
		if (check_map_boundaries(game, point))
			return (WALL);
		else if (game->map[point->y_map][point->x_map] == WALL)
			return (WALL);
		point->x += x;
		point->y += y;
	}
}

float	vintersections(t_game *game, t_vector *point, float angle)
{
	t_vector	*player;
	float		adj_side;
	float		opp_side;
	float		tangent;

	player = &game->player.pos;
	tangent = tanf(rad(angle));
	if (angle < 90 || angle > 270)
	{
		point->x = (player->x_map << UNIT_SIZE_SHIFT) + UNIT_SIZE;
		adj_side = -UNIT_SIZE;
	}
	else
	{
		point->x = (player->x_map << UNIT_SIZE_SHIFT) - 0.001;
		adj_side = UNIT_SIZE;
	}
	point->y = player->y + (player->x - point->x) * tangent;
	if (angle < 90 || angle > 270)
		adj_side = UNIT_SIZE;
	else
		adj_side = -UNIT_SIZE;
	opp_side = -adj_side * tangent;
	find_wall(game, point, adj_side, opp_side);
	return (calc_distance_rad(&game->player, point, angle));
}

float	hintersections(t_game *game, t_vector *point, float angle)
{
	t_vector	*player;
	float		adj_side;
	float		opp_side;
	float		tangent;

	player = &game->player.pos;
	tangent = tanf(rad(angle));
	if (angle < 180)
	{
		point->y = (player->y_map << UNIT_SIZE_SHIFT) - 0.001;
		adj_side = -UNIT_SIZE;
	}
	else
	{
		point->y = (player->y_map << UNIT_SIZE_SHIFT) + UNIT_SIZE;
		adj_side = UNIT_SIZE;
	}
	point->x = player->x + (player->y - point->y) / tangent;
	opp_side = -adj_side / tangent;
	find_wall(game, point, opp_side, adj_side);
	return (calc_distance_rad(&game->player, point, angle));
}
