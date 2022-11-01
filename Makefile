#MAKEFLAGS += --silent

NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -g -Werror -Wpedantic 
INC_DIR = includes/
INC = cub3d.h

SRC_DIR = src/
SRC = 	main.c\
		utils.c\
		utils2.c\
		parsing/parse_file.c\
		parsing/parse_file2.c\
		parsing/parse_map.c\
		parsing/parse_map2.c\
		parsing/get.c\
		game/launch_game.c\
		game/draw_screen.c\
		game/cast_ray.c\
		game/cast_ray2.c\
		game/sprites.c\
		game/sprites2.c\
		game/sprites3.c\
		game/handle_keys.c\
		game/screenshot.c

LIBRARY_DIR = libs/

MLX_DIR = $(LIBRARY_DIR)minilibx_opengl_20191021 
MLX_FLAGS = -framework OpenGL -framework AppKit 
MLX_INC_DIR = $(MLX_DIR)
MLX_INC = -L $(MLX_DIR) -lmlx $(MLX_FLAGS) -I $(MLX_INC_DIR) 

LIBFT_DIR = $(LIBRARY_DIR)libft/
LIBFT_INC_DIR = $(LIBFT_DIR)includes/
LIBFT_INC = -I $(LIBFT_INC_DIR) $(LIBFT_DIR)libft.a

OBJ_DIR = .obj/
OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)

.PHONY : all clean fclean re $(MLX_DIR) $(LIBFT_DIR)

all: $(MLX_DIR) $(LIBFT_DIR) $(NAME) 

$(NAME): $(OBJ) $(LIBFT_DIR)libft.a
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(MLX_INC) $(LIBFT_INC) -I $(INC_DIR) -lm

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(addprefix $(INC_DIR),$(INC))
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(MLX_INC_DIR) -I $(LIBFT_INC_DIR) -I $(INC_DIR)

$(MLX_DIR):
	$(MAKE) -C $(MLX_DIR)

$(LIBFT_DIR):
	$(MAKE) -C $(LIBFT_DIR)

norm:
	norminette $(SRC_DIR)$(SRC) $(INC_DIR)$(INC)

clean:
	/bin/rm -rf $(OBJ_DIR)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) fclean

fclean: clean
	/bin/rm -f $(NAME)

re: 
	$(MAKE) fclean
	$(MAKE) all
