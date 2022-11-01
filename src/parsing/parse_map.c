/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez <bperez@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 14:03:41 by bperez            #+#    #+#             */
/*   Updated: 2021/05/08 12:51:42 by bperez           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

#include <stdlib.h>

static int	check_if_another_player(char *line, char *player)
{
	char	*tmp;

	tmp = ft_strschr(line, "NSWE");
	if (tmp == player)
	{
		if (ft_strschr(player + 1, "NSWE"))
			return (1);
	}
	else
	{
		if (ft_strschr(line, "NSWE"))
			return (1);
	}
	return (0);
}

static int	add_row_to_map(t_game *game, char *line, int rows)
{
	char	**map;
	int		i;

	map = malloc(sizeof(char *) * (rows + 1));
	if (map)
	{
		i = 0;
		if (game->map)
		{
			while (game->map[i])
			{
				map[i] = game->map[i];
				i++;
			}
			free(game->map);
		}
		ft_strcreplace(line, ' ', VOID);
		if ((int)ft_strlen(line) > game->map_width)
			game->map_width = ft_strlen(line);
		map[i] = line;
		map[i + 1] = NULL;
		game->map = map;
		return (1);
	}
	return (0);
}

static int	error_free(char *str, char *ptr)
{
	free(ptr);
	return (error(str));
}

int	parse_map(t_game *game, int fd, char *line, char *player)
{
	while (get_next_line(fd, &line, NULL, 0) == 1)
	{
		if ((game->blank && line[0] != '\0') || !ft_regex(line, "012NSWE "))
			return (error_free("Invalid line(s) in the map", line));
		if (ft_regex(line, "012NSWE ") && line[0] != '\0')
		{
			if (!player)
			{
				player = ft_strschr(line, "NSWE");
				if (player)
					get_player_data(game, player[0], (player - line));
			}
			if (!add_row_to_map(game, line, ++game->map_height))
				return (error_free("Unknown memory problem occured", NULL));
			if (player && check_if_another_player(line, player))
				return (error("Only one player allowed"));
			line = NULL;
		}
		else if (line[0] == '\0' && game->map_height != 0)
			game->blank = 1;
		free(line);
	}
	free(line);
	return (last_checks_map(game, player));
}
