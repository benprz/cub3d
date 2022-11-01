/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez <bperez@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 16:36:40 by bperez            #+#    #+#             */
/*   Updated: 2021/05/07 12:48:46 by bperez           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	get_settings(t_game *game, char *line, int *colors)
{
	game->number_parameters++;
	if (game->number_parameters > 8)
	{
		free(line);
		error("Can't define multiple times the same parameter");
		exit(1);
	}
	if (line[0] == 'R' && line[1] == ' ')
		get_window_resolution(game, line + 2);
	else if ((line[0] == 'N') || (line[0] == 'S') || \
			(line[0] == 'W') || (line[0] == 'E'))
	{
		get_textures_path(game, line);
	}
	else if ((line[0] == 'F' || line[0] == 'C') && line[1] == ' ')
	{
		if (get_floor_and_ceiling_colors(game, line))
			colors[0]++;
	}
}

int	parse_settings(t_game *game, int fd)
{
	char	*line;
	int		colors;

	colors = 0;
	while (!check_settings(game, colors, 0, fd))
	{
		if (get_next_line(fd, &line, NULL, 0) == 1)
		{
			line = ft_tmp(line, ft_strtrim(line, " "));
			if (line)
			{
				if (ft_strchr("RFCNSEW", line[0]))
					get_settings(game, line, &colors);
				free(line);
			}
		}
		else
		{
			free(line);
			break ;
		}
	}
	if (check_settings(game, colors, 1, fd) == 0)
		return (0);
	return (1);
}

int	parse_file(t_game *game, char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd > 0)
	{
		ft_bzero(game, sizeof(t_game));
		if (parse_settings(game, fd))
		{
			if (parse_map(game, fd, NULL, NULL))
			{
				close(fd);
				return (1);
			}
		}
		close(fd);
		return (0);
	}
	return (error("Couldn't open the file"));
}
