/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   draw_screen.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bperez <bperez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2021/02/11 15:46:47 by bperez       #+#   ##    ##    #+#       */
/*   Updated: 2021/05/07 13:51:29 by bperez           ###   ########lyon.fr   */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

float	draw_texture(t_texture *texture, int height, int current_height)
{
	float	index_y;

	index_y = (int)(current_height *\
			(float)texture->height / height) % \
			texture->height;
	return (index_y);
}

void	draw_column_pixels(t_env *env, int i, int height, int current_height)
{
	t_texture	*texture;
	float		ratio;
	float		y;
	int			next_pixel;
	int			index;

	texture = env->game.textures.current_texture;
	ratio = (float)texture->height / height;
	y = current_height * ratio;
	next_pixel = y + 1;
	index = (int)y * texture->width + texture->current_pixel.x_map;
	while (current_height++ < height && i < env->game.window_size)
	{
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

void	draw_column(t_env *env, t_game *game, float angle, int x)
{
	float	wall_distance;
	int		wall_height;
	int		wall_position;
	int		current_height;

	wall_distance = cast_ray(game, &game->textures, angle);
	wall_height = game->const_values.unit_size_on_fov_distance / wall_distance;
	wall_position = (game->const_values.half_window_height -\
			(wall_height >> 1)) * game->window_width + x;
	current_height = 0;
	if (wall_position < 0)
	{
		current_height -= wall_position / game->window_width;
		wall_position = x;
	}
	draw_column_pixels(env, wall_position, wall_height, current_height);
}

void	draw_screen(t_env *env, t_game *game)
{
	float	angle;
	int		x;

	angle = fix_degrees(game->player.orientation - game->const_values.half_fov);
	x = game->window_width;
	while (x--)
	{
		draw_column(env, &env->game, angle, x);
		angle = fix_degrees(angle + game->const_values.angle_per_ray);
	}
	draw_sprites(env, game);
}
