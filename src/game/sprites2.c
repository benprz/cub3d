/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez <bperez@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 14:28:48 by bperez            #+#    #+#             */
/*   Updated: 2021/04/30 15:11:02 by bperez           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

#include <math.h>

void	init_sprite(t_game *game, t_sprite *sprite, t_vector *point)
{
	t_player	*player;

	player = &game->player;
	sprite->init = 1;
	sprite->center.x_map = point->x_map;
	sprite->center.y_map = point->y_map;
	sprite->center.x = (point->x_map << UNIT_SIZE_SHIFT) + \
					   game->const_values.half_unit_size;
	sprite->center.y = (point->y_map << UNIT_SIZE_SHIFT) + \
					   game->const_values.half_unit_size;
	sprite->center_distance = calc_distance(&game->player.pos, &sprite->center);
	sprite->center_height = game->const_values.unit_size_on_fov_distance / \
			sprite->center_distance;
	sprite->gap_angle = deg(atanf(game->const_values.half_unit_size / \
			sprite->center_distance));
	sprite->center_angle = deg(acosf((sprite->center.x - player->pos.x) / \
			sprite->center_distance));
	if (player->pos.y < sprite->center.y)
		sprite->center_angle = 360 - sprite->center_angle;
	sprite->first_angle = fix_degrees(sprite->center_angle + sprite->gap_angle);
	sprite->last_angle = fix_degrees(sprite->center_angle - sprite->gap_angle);
	sprite->player_tmp.x = sprite->center.x + sprite->center_distance;
	sprite->player_tmp.y = sprite->center.y;
}

int	is_there_a_sprite(t_sprite *sprite)
{
	while (sprite)
	{
		if (sprite->is_in_ray)
			return (SPRITE);
		sprite = sprite->next;
	}
	return (WALL);
}

t_sprite	*find_current_sprite(t_sprite *list)
{
	t_sprite	*sprite;

	sprite = NULL;
	while (list)
	{
		if (list->is_in_ray)
		{
			if (sprite == NULL)
				sprite = list;
			else if (list->point_distance > sprite->point_distance)
				sprite = list;
		}
		list = list->next;
	}
	return (sprite);
}

void	find_point(t_game *game, t_sprite *sprite, float angle_tmp, float angle)
{
	t_vector	point;
	float		distance;

	if (angle_tmp == 180)
	{
		sprite->height = sprite->center_height;
		game->textures.current_texture->x = 32;
	}
	else
	{
		point.x = sprite->center.x;
		point.y = sprite->center.y + (tanf(rad(angle_tmp - 180)) * \
				(sprite->player_tmp.x - sprite->center.x));
		distance = calc_distance(&sprite->player_tmp, &point) * \
				   cosf(rad(ft_abs(game->player.orientation - angle)));
		sprite->height = game->const_values.unit_size_on_fov_distance / \
						 distance;
		game->textures.current_texture->x = sprite->center.y - point.y + 32;
	}
}

int	cast_ray_sprites(t_game *game, t_vector *from, float angle)
{
	float		vray;
	float		hray;
	float		wall_distance;
	t_sprite	*sprite;

	vray = vertical_ray_sprites(game, from, angle);
	hray = horizontal_ray_sprites(game, from, angle);
	wall_distance = hray;
	if (vray < hray)
		wall_distance = vray;
	sprite = game->sprites.list;
	while (sprite)
	{
		if (sprite->is_in_ray)
		{
			if (wall_distance < sprite->point_distance)
				sprite->is_in_ray = 0;
		}
		sprite = sprite->next;
	}
	return (is_there_a_sprite(game->sprites.list));
}
