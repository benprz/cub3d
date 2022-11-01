/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez <bperez@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 16:36:55 by bperez            #+#    #+#             */
/*   Updated: 2021/05/07 13:06:08 by bperez           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	load_data(t_env *env, t_game *game)
{
	unsigned int	half_window;

	if (create_layer(env))
	{
		if (init_textures(env, &game->textures))
		{
			init_const_values(game);
			half_window = game->window_size >> 1;
			ft_memset_uint32(
				env->layer_data,
				game->ceiling_color.value,
				half_window);
			ft_memset_uint32(
				env->layer_data + half_window,
				game->floor_color.value,
				half_window);
			draw_screen(env, game);
		}
		else
			exit_program(env);
	}
}

void	fill_header(t_bmp_header *bmp_header, t_env *env, t_game *game)
{
	bmp_header->file_type = 0x4D42;
	bmp_header->file_size = 54 + env->size_line;
	bmp_header->data_offset = 54;
	bmp_header->headerinfo_size = 40;
	bmp_header->image_width = game->window_width;
	bmp_header->image_height = game->window_height;
	bmp_header->planes_number = 1;
	bmp_header->bits_per_pixel = 32;
}

void	bmp_screenshot(t_env *env, t_game *game)
{
	int				fd;
	t_bmp_header	bmp_header;
	unsigned int	row;

	load_data(env, game);
	fd = open("screenshot.bmp", O_WRONLY |\
		O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd > 0)
	{
		bmp_header = (const t_bmp_header){0};
		fill_header(&bmp_header, env, game);
		write(fd, &bmp_header.file_type, 2);
		write(fd, &bmp_header.file_size, 52);
		row = game->window_height;
		while (row > 0)
		{
			row--;
			write(fd, &env->layer_data[row * game->window_width], \
					env->size_line);
		}
		close(fd);
	}
}
