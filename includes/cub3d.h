/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cub3d.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bperez <bperez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/21 16:36:40 by bperez       #+#   ##    ##    #+#       */
/*   Updated: 2021/05/08 15:53:41 by bperez           ###   ########lyon.fr   */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdint.h>
# include <stdio.h>

# define ALPHA 3
# define RED 2
# define GREEN 1
# define BLUE 0
# define TRANSPARENT_VALUE 4278190080

# define MAX_WINDOW_WIDTH_RESOLUTION 2560
# define MAX_WINDOW_HEIGHT_RESOLUTION 1440
# define FILE_EXTENSION ".cub"
# define FILE_EXTENSION_LEN 4
# define TEXTURE_EXTENSION ".xpm"
# define TEXTURE_EXTENSION_LEN 4
# define SAVE_FLAG "--save"
# define SAVE_FLAG_LEN 6

# define VOID '0'
# define WALL '1'
# define SPRITE '2'
# define VOID_TMP '3'
# define SPRITE_TMP '4'

# define UNIT_SIZE 64
# define UNIT_SIZE_SHIFT 6
# define FOV 60
# define PLAYER_SPEED 10

typedef struct s_bmp_header
{
	uint16_t	file_type;
	uint32_t	file_size;
	uint16_t	reserved1;
	uint16_t	reserved2;
	uint32_t	data_offset;
	uint32_t	headerinfo_size;
	uint32_t	image_width;
	uint32_t	image_height;
	uint16_t	planes_number;
	uint16_t	bits_per_pixel;
	uint32_t	compression_type;
	uint32_t	image_size;
	uint32_t	x_pixels_per_meter;
	uint32_t	y_pixels_per_meter;
	uint32_t	colors_used;
	uint32_t	colors_required;
}				t_bmp_header;

typedef union u_rgba
{
	uint32_t		value;
	unsigned char	byte[4];
}					t_rgba;

typedef struct s_vector
{
	int		x_map;
	int		y_map;
	float	x;
	float	y;
}			t_vector;

typedef struct s_const_values
{
	int		half_window_height;
	float	half_fov;
	float	half_unit_size;
	float	fov_distance;
	float	unit_size_on_fov_distance;
	float	angle_per_ray;
}			t_const_values;

typedef struct s_texture
{
	char			*file_path;
	void			*layer;
	t_rgba			*layer_data;
	int				width;
	int				height;
	unsigned int	size;
	int				bits_per_pixel;
	int				size_line;
	int				big_endian;
	t_vector		current_pixel;
	float			x;
}					t_texture;

typedef struct s_textures
{
	t_texture	north_texture;
	t_texture	south_texture;
	t_texture	west_texture;
	t_texture	east_texture;
	t_texture	sprite_texture;
	t_texture	*current_texture;
}				t_textures;

typedef struct s_background
{
	char	*file_path;
	void	*layer;
	t_rgba	*layer_data;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		size_line;
	int		big_endian;
}			t_background;

typedef struct s_player
{
	t_vector	pos;
	short		orientation;
}				t_player;

typedef struct s_sprite
{
	int				init;
	struct s_sprite	*next;
	int				is_in_ray;
	float			point_distance;
	t_vector		center;
	float			center_distance;
	int				center_height;
	float			center_angle;
	float			gap_angle;
	float			first_angle;
	float			last_angle;
	t_vector		player_tmp;
	float			angle_tmp;
	int				height;
}					t_sprite;

typedef struct s_sprites
{
	void		*layer;
	t_rgba		*layer_data;
	int			width;
	int			height;
	int			bits_per_pixel;
	int			size_line;
	int			big_endian;
	t_sprite	*list;
}				t_sprites;

typedef struct s_check_parsing
{
	int	resolution;
	int	floor;
	int	ceiling;
	int	north;
	int	east;
	int	south;
	int	west;
	int	sprite;
}		t_check_parsing;

typedef struct s_game
{
	void			*env;
	t_sprites		sprites;
	t_background	background;
	t_textures		textures;
	t_player		player;
	char			**map;
	int				map_width;
	int				map_height;
	float			width;
	float			height;
	int				window_width;
	int				window_height;
	int				window_size;
	t_const_values	const_values;
	t_rgba			floor_color;
	t_rgba			ceiling_color;
	int				number_parameters;
	int				blank;
}					t_game;

typedef struct s_env
{
	t_game	game;
	void	*mlx;
	void	*window;
	void	*layer;
	t_rgba	*layer_data;
	int		bits_per_pixel;
	int		size_line;
	int		big_endian;
	short	save;
}			t_env;

int			check_args(int argc, char **argv, t_env *env);
int			create_layer(t_env *env);
int			init_textures(t_env *env, t_textures *textures);
int			init_texture(t_env *env, t_texture *texture);

int			parse_file(t_game *game, char *file);
int			parse_map(t_game *game, int fd, char *line, char *player);
int			last_checks_map(t_game *game, char *player);
int			check_settings(t_game *game, int colors, int print, int fd);
void		get_window_resolution(t_game *game, char *line);
void		get_textures_path(t_game *game, char *line);
int			get_floor_and_ceiling_colors(t_game *game, char *line);
void		get_player_data(t_game *game, char orientation, int x);

void		launch_game(t_env *env, t_game *game);
void		init_const_values(t_game *game);
int			draw_background(t_env *env, t_game *game, t_background *b);
void		refresh_window(t_env *env, t_game *game);
float		cast_ray(t_game *game, t_textures *textures, float angle);
float		hintersections(t_game *game, t_vector *point, float angle);
float		vintersections(t_game *game, t_vector *point, float angle);
float		calc_distance_rad(t_player *player, t_vector *point, float angle);
int			check_map_boundaries(t_game *game, t_vector *point);
void		draw_screen(t_env *env, t_game *game);
int			handle_keys(int keycode, t_env *env);

void		draw_sprites(t_env *env, t_game *game);
int			cast_ray_sprites(t_game *game, t_vector *from, float angle);
void		find_point(t_game *game, t_sprite *sprite, float atmp, float a);
float		vertical_ray_sprites(t_game *game, t_vector *from, float angle);
float		horizontal_ray_sprites(t_game *game, t_vector *from, float angle);
void		init_sprite(t_game *game, t_sprite *sprite, t_vector *point);

int			exit_program(t_env *env);
int			error(const char *str);
float		fix_degrees(float degrees);
float		rad(float degrees);
float		deg(float rad);
float		calc_distance(t_vector *p1, t_vector *p2);
int			is_void_or_sprite(t_game *game, int x, int y);
int			ft_strchrlen(char *str, char c);
void		bmp_screenshot(t_env *env, t_game *game);
t_sprite	*find_current_sprite(t_sprite *list);

#endif
