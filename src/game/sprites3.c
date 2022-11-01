/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez <bperez@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 14:30:53 by bperez            #+#    #+#             */
/*   Updated: 2021/05/07 14:34:40 by bperez           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

#include <math.h>
#include <stdlib.h>

t_sprite	*is_sprite_in_list(t_sprite *sprite, t_vector *current_point)
{
	while (sprite)
	{
		if (sprite->center.x_map == current_point->x_map && \
			sprite->center.y_map == current_point->y_map)
			break ;
		sprite = sprite->next;
	}
	return (sprite);
}

t_sprite	*add_sprite(t_game *game, t_sprites *sprites, t_vector *point)
{
	t_sprite	*new_sprite;
	t_sprite	**current_sprite;

	new_sprite = malloc(sizeof(t_sprite));
	if (new_sprite)
	{
		ft_bzero(new_sprite, sizeof(t_sprite));
		init_sprite(game, new_sprite, point);
		current_sprite = &sprites->list;
		while (*current_sprite)
			current_sprite = &((*current_sprite)->next);
		*current_sprite = new_sprite;
	}
	else
	{
		error("Unknown memory problem occured");
		exit_program((t_env *)game->env);
	}
	return (new_sprite);
}

float	find_sprites(t_game *game, t_vector *p, float x, float y)
{
	t_sprite	*sprite;
	float		distance;

	while (1)
	{
		p->x_map = p->x / UNIT_SIZE;
		p->y_map = p->y / UNIT_SIZE;
		if (check_map_boundaries(game, p) || \
				game->map[p->y_map][p->x_map] == WALL)
			return (calc_distance(&game->player.pos, p));
		else if (game->map[p->y_map][p->x_map] == SPRITE)
		{
			sprite = is_sprite_in_list(game->sprites.list, p);
			if (!sprite)
				sprite = add_sprite(game, &game->sprites, p);
			if (sprite->init == 0)
				init_sprite(game, sprite, p);
			distance = calc_distance(&game->player.pos, p);
			if (sprite->is_in_ray == 0 || distance < sprite->point_distance)
				sprite->point_distance = distance;
			sprite->is_in_ray = 1;
		}
		p->x += x;
		p->y += y;
	}
}

float	vertical_ray_sprites(t_game *game, t_vector *from, float angle)
{
	float		adj_side;
	float		opp_side;
	float		tangent;
	t_vector	point;

	tangent = tanf(rad(angle));
	if (angle < 90 || angle > 270)
	{
		point.x = (from->x_map << UNIT_SIZE_SHIFT) + UNIT_SIZE;
		adj_side = -UNIT_SIZE;
	}
	else
	{
		point.x = (from->x_map << UNIT_SIZE_SHIFT) - 0.001;
		adj_side = UNIT_SIZE;
	}
	point.y = from->y + (from->x - point.x) * tangent;
	adj_side = -UNIT_SIZE;
	if (angle < 90 || angle > 270)
		adj_side = UNIT_SIZE;
	opp_side = -adj_side * tangent;
	return (find_sprites(game, &point, adj_side, opp_side));
}

float	horizontal_ray_sprites(t_game *game, t_vector *from, float angle)
{
	float		adj_side;
	float		opp_side;
	float		tangent;
	t_vector	point;

	tangent = tanf(rad(angle));
	if (angle < 180)
	{
		point.y = (from->y_map << UNIT_SIZE_SHIFT) - 0.001;
		adj_side = -UNIT_SIZE;
	}
	else
	{
		point.y = (from->y_map << UNIT_SIZE_SHIFT) + UNIT_SIZE;
		adj_side = UNIT_SIZE;
	}
	point.x = from->x + (from->y - point.y) / tangent;
	opp_side = -adj_side / tangent;
	return (find_sprites(game, &point, opp_side, adj_side));
}
