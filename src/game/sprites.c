/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez <bperez@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:40:16 by bperez            #+#    #+#             */
/*   Updated: 2021/05/05 15:32:19 by bperez           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_pixels_sprites(t_env *env, int i, int h, int currenth)
{
	t_texture		*texture;
	float			ratio;
	float			y;
	unsigned int	next_pixel;
	unsigned int	index;

	texture = env->game.textures.current_texture;
	ratio = (float)texture->height / h;
	y = currenth * ratio;
	next_pixel = y + 1;
	texture->x *= (float)texture->width / UNIT_SIZE;
	index = (int)y * texture->width + texture->x;
	while (currenth++ < h && i < env->game.window_size)
	{
		if (texture->x < texture->width && \
				texture->layer_data[index].value != TRANSPARENT_VALUE)
			env->layer_data[i].value = texture->layer_data[index].value;
		y += ratio;
		if (y >= next_pixel)
		{
			index += ((int)(y - next_pixel + 1)) * texture->width;
			next_pixel = y + 1;
		}
		i += env->game.window_width;
	}
}

static int	is_angle_in_between(float first, float last, float angle)
{
	if ((first - last) < 0.0f)
		first = first - last + 360.0f;
	else
		first = first - last;
	if ((angle - last) < 0.0f)
		angle = angle - last + 360.0f;
	else
		angle = angle - last;
	return (angle < first);
}

static void	handle_sprite(t_env *env, float angle, int x, t_sprite *sprite)
{
	t_game	*game;
	int		wall_position;
	int		current_height;
	float	angle_tmp;

	game = &env->game;
	if (is_angle_in_between(sprite->first_angle, sprite->last_angle, angle))
	{
		angle_tmp = fix_degrees(angle - ((sprite->center_angle + 360) - \
					(180 + 360)));
		find_point(game, sprite, angle_tmp, angle);
		wall_position = (game->const_values.half_window_height -\
						(sprite->height >> 1)) * game->window_width + x;
		current_height = 0;
		if (wall_position < 0)
		{
			current_height -= wall_position / game->window_width;
			wall_position = x;
		}
		draw_pixels_sprites(env, wall_position, sprite->height, current_height);
	}
	sprite->is_in_ray = 0;
}

static void	draw_column_sprites(t_env *env, t_game *game, float angle, int x)
{
	t_sprite	*sprite;

	if (cast_ray_sprites(game, &game->player.pos, angle) == SPRITE)
	{
		while (1)
		{
			sprite = find_current_sprite(game->sprites.list);
			if (!sprite)
				break ;
			handle_sprite(env, angle, x, sprite);
		}
	}
}

void	draw_sprites(t_env *env, t_game *game)
{
	float		angle;
	float		gap_angle;
	int			x;
	t_sprite	*sprite;

	game->textures.current_texture = &game->textures.sprite_texture;
	angle = fix_degrees(game->player.orientation - game->const_values.half_fov);
	gap_angle = game->const_values.half_fov;
	x = game->window_width;
	while (x--)
	{
		draw_column_sprites(env, &env->game, angle, x);
		gap_angle -= game->const_values.angle_per_ray;
		angle = fix_degrees(angle + game->const_values.angle_per_ray);
	}
	sprite = game->sprites.list;
	while (sprite)
	{
		sprite->init = 0;
		sprite = sprite->next;
	}
}
