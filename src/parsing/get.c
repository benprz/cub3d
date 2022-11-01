/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez <bperez@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 15:47:24 by bperez            #+#    #+#             */
/*   Updated: 2021/05/08 16:20:27 by bperez           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

void	get_window_resolution(t_game *game, char *line)
{
	char	**r;
	size_t	len;

	r = ft_split(line, ' ');
	len = ft_strlen_2d(r);
	if (len == 2)
	{
		if (ft_regex(r[0], REGEX_DIGITS) && ft_regex(r[1], REGEX_DIGITS))
		{
			game->window_width = ft_atoi(r[0]);
			game->window_height = ft_atoi(r[1]);
			if (game->window_width > MAX_WINDOW_WIDTH_RESOLUTION || \
					game->window_width < 0 || \
					(ft_strlen(r[0]) >= 10 && game->window_width >= 0))
				game->window_width = MAX_WINDOW_WIDTH_RESOLUTION;
			if (game->window_height > MAX_WINDOW_HEIGHT_RESOLUTION || \
					game->window_height < 0 || \
					(ft_strlen(r[1]) >= 10 && game->window_height >= 0))
				game->window_height = MAX_WINDOW_HEIGHT_RESOLUTION;
			game->window_size = game->window_width * game->window_height;
		}
	}
	ft_free_2d((void **)r, len);
}

void	get_textures_path(t_game *game, char *line)
{
	char	**texture_path;

	texture_path = NULL;
	if (ft_strcmp(line, "NO ") == 0)
		texture_path = &game->textures.north_texture.file_path;
	else if (ft_strcmp(line, "SO ") == 0)
		texture_path = &game->textures.south_texture.file_path;
	else if (ft_strcmp(line, "WE ") == 0)
		texture_path = &game->textures.west_texture.file_path;
	else if (ft_strcmp(line, "EA ") == 0)
		texture_path = &game->textures.east_texture.file_path;
	else if (ft_strcmp(line, "S ") == 0)
		texture_path = &game->textures.sprite_texture.file_path;
	if (texture_path)
	{
		if (!*texture_path)
			*texture_path = ft_strtrim(line += 2, " ");
	}
}

int	put_colors(char **rgb, t_rgba *color)
{
	rgb[0] = ft_tmp(rgb[0], ft_strtrim(rgb[0], " "));
	rgb[1] = ft_tmp(rgb[1], ft_strtrim(rgb[1], " "));
	rgb[2] = ft_tmp(rgb[2], ft_strtrim(rgb[2], " "));
	if (!rgb[0] || !rgb[1] || !rgb[2])
		return (0);
	if (ft_strlen(rgb[0]) > 3 || ft_strlen(rgb[1]) > 3 || ft_strlen(rgb[2]) > 3)
		return (0);
	if (ft_regex(rgb[0], REGEX_DIGITS))
	{
		color->byte[RED] = ft_atoi(rgb[0]);
		if (ft_regex(rgb[1], REGEX_DIGITS) && ft_atoi(rgb[0]) <= 255)
		{
			color->byte[GREEN] = ft_atoi(rgb[1]);
			if (ft_regex(rgb[2], REGEX_DIGITS) && ft_atoi(rgb[1]) <= 255)
			{
				color->byte[BLUE] = ft_atoi(rgb[2]);
				if (ft_atoi(rgb[2]) <= 255)
					return (1);
			}
		}
	}
	return (0);
}

int	get_floor_and_ceiling_colors(t_game *game, char *line)
{
	char	**rgb;
	t_rgba	*color;
	size_t	len;
	int		ret;

	len = 0;
	ret = 0;
	color = &game->ceiling_color;
	if (line[0] == 'F')
		color = &game->floor_color;
	if (ft_strchrlen(line, ',') == 2)
	{
		rgb = ft_split(line + 2, ',');
		len = ft_strlen_2d(rgb);
		if (len == 3)
		{
			if (put_colors(rgb, color))
				ret = 1;
		}
		ft_free_2d((void **)rgb, len);
	}
	return (ret);
}

void	get_player_data(t_game *game, char orientation, int x)
{
	t_player	*player;

	player = &game->player;
	if (orientation == 'E')
		player->orientation = 0;
	else if (orientation == 'N')
		player->orientation = 90;
	else if (orientation == 'W')
		player->orientation = 180;
	else if (orientation == 'S')
		player->orientation = 270;
	player->pos.x = (float)((x << UNIT_SIZE_SHIFT) + (UNIT_SIZE >> 1));
	player->pos.y = (float)((game->map_height << UNIT_SIZE_SHIFT) \
		+ (UNIT_SIZE >> 1));
	player->pos.x_map = x;
	player->pos.y_map = game->map_height;
}
