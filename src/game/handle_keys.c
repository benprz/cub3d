/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez <bperez@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 16:36:40 by bperez            #+#    #+#             */
/*   Updated: 2021/05/04 13:52:11 by bperez           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#include <math.h>

float	move_player_x(int keycode, float player_orientation)
{
	int	direction;

	if (keycode == 0 || keycode == 2)
	{
		direction = 1;
		if (keycode == 0)
			direction = -1;
		return (direction * sinf(player_orientation) * PLAYER_SPEED);
	}
	else
	{
		direction = 1;
		if (keycode == 13)
			direction = -1;
		return (direction * -cosf(player_orientation) * PLAYER_SPEED);
	}
}

float	move_player_y(int keycode, float player_orientation)
{
	int	direction;

	if (keycode == 0 || keycode == 2)
	{
		direction = 1;
		if (keycode == 0)
			direction = -1;
		return (direction * cosf(player_orientation) * PLAYER_SPEED);
	}
	else
	{
		direction = 1;
		if (keycode == 13)
			direction = -1;
		return (direction * sinf(player_orientation) * PLAYER_SPEED);
	}
}

void	move_player(t_env *env, t_player *player, int keycode)
{
	float	player_orientation;
	float	x;
	float	y;
	int		x_map;
	int		y_map;

	player_orientation = rad(player->orientation);
	x = player->pos.x + move_player_x(keycode, player_orientation);
	y = player->pos.y + move_player_y(keycode, player_orientation);
	x_map = x / UNIT_SIZE;
	y_map = y / UNIT_SIZE;
	if (env->game.map[y_map][x_map] != WALL)
	{
		player->pos.x = x;
		player->pos.y = y;
		player->pos.x_map = x_map;
		player->pos.y_map = y_map;
	}
}

void	rotate_player(t_player *player, int keycode)
{
	if (keycode == 123)
		player->orientation = fix_degrees(player->orientation + 2);
	if (keycode == 124)
		player->orientation = fix_degrees(player->orientation - 2);
}

int	handle_keys(int keycode, t_env *env)
{
	t_player	*player;

	player = &env->game.player;
	if (keycode == 53)
		exit_program(env);
	else if (keycode == 49)
		bmp_screenshot(env, &env->game);
	else if (keycode == 13 || keycode == 2 || keycode == 1 || keycode == 0)
		move_player(env, &env->game.player, keycode);
	else if (keycode == 123 || keycode == 124)
		rotate_player(&env->game.player, keycode);
	refresh_window(env, &env->game);
	return (0);
}
