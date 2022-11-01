/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez <bperez@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 11:46:06 by bperez            #+#    #+#             */
/*   Updated: 2021/05/08 12:45:29 by bperez           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

#include <stdlib.h>

static int	check_textures(t_textures *textures)
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	char	*sprite;

	north = textures->north_texture.file_path;
	south = textures->south_texture.file_path;
	east = textures->east_texture.file_path;
	west = textures->west_texture.file_path;
	sprite = textures->sprite_texture.file_path;
	if (north == NULL || south == NULL || east == NULL || west == NULL || \
			sprite == NULL)
		return (0);
	if (ft_strnrcmp(north, TEXTURE_EXTENSION, TEXTURE_EXTENSION_LEN) || \
		ft_strnrcmp(south, TEXTURE_EXTENSION, TEXTURE_EXTENSION_LEN) || \
		ft_strnrcmp(east, TEXTURE_EXTENSION, TEXTURE_EXTENSION_LEN) || \
		ft_strnrcmp(west, TEXTURE_EXTENSION, TEXTURE_EXTENSION_LEN) || \
		ft_strnrcmp(sprite, TEXTURE_EXTENSION, TEXTURE_EXTENSION_LEN))
		return (0);
	return (1);
}

static void	check_inbetween_params_map(int fd)
{
	char	*line;

	line = NULL;
	if (get_next_line(fd, &line, NULL, 0) == 1 && line[0] != '\0')
	{
		if ((line[0] == 'R' || line[0] == 'F' || line[0] == 'C' || \
					line[0] == 'N' || line[0] == 'W' || line[0] == 'S' || \
					line[0] == 'E') && line [1] == ' ')
			error("Can't define multiple times the same parameter");
		else
			error("Invalid line between the parameters and the map");
		free(line);
		exit(1);
	}
	free(line);
}

int	check_settings(t_game *game, int colors, int print, int fd)
{
	if (print == 0)
	{
		if (!game->window_width || !game->window_height ||\
				!game->textures.north_texture.file_path ||\
				!game->textures.south_texture.file_path ||\
				!game->textures.west_texture.file_path ||\
				!game->textures.east_texture.file_path ||\
				!game->textures.sprite_texture.file_path || colors != 2)
			return (0);
		check_inbetween_params_map(fd);
	}
	else
	{
		if (!game->window_width || !game->window_height)
			return (error("Invalid or missing screen resolution (R w h)"));
		if (colors != 2)
			return (error("Invalid or missing floor/ceiling color (FC r,g,b)"));
		if (check_textures(&game->textures) == 0)
			return (error("Missing texture(s) or wrong extension (.xpm)"));
	}
	return (1);
}
