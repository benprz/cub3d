/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez <bperez@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 16:36:40 by bperez            #+#    #+#             */
/*   Updated: 2021/02/11 13:06:14 by bperez           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_north_and_south_texture_x(t_textures *textures, t_vector *h_point)
{
	textures->current_texture->current_pixel.x_map =\
		(int)(h_point->x * \
		(float)textures->current_texture->width / UNIT_SIZE) % \
		textures->current_texture->width;
}

void	get_east_and_west_texture_x(t_textures *textures, t_vector *v_point)
{
	textures->current_texture->current_pixel.x_map =\
		(int)(v_point->y * \
		(float)textures->current_texture->width / UNIT_SIZE) % \
		textures->current_texture->width;
}

float	cast_ray(t_game *game, t_textures *textures, float angle)
{
	t_vector	v_point;
	t_vector	h_point;
	float		v_dist;
	float		h_dist;

	v_dist = vintersections(game, &v_point, angle);
	h_dist = hintersections(game, &h_point, angle);
	if (h_dist < v_dist)
	{
		if ((int)h_point.y % UNIT_SIZE == 0)
			textures->current_texture = &textures->north_texture;
		else
			textures->current_texture = &textures->south_texture;
		get_north_and_south_texture_x(textures, &h_point);
		return (h_dist);
	}
	else
	{
		if ((int)v_point.x % UNIT_SIZE == 0)
			textures->current_texture = &textures->west_texture;
		else
			textures->current_texture = &textures->east_texture;
		get_east_and_west_texture_x(textures, &v_point);
		return (v_dist);
	}
}
