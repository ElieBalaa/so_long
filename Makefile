NAME		= so_long

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

MLX_DIR		= ./mlx
MLX			= -L$(MLX_DIR) -lmlx -lX11 -lXext -lm
LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a

SRCS		= src/main.c \
			  src/map_loader.c \
			  src/map_validator.c \
			  src/flood_fill.c \
			  src/init_game.c \
			  src/asset_loader.c \
			  src/image_loader.c \
			  src/collectible_loader.c \
			  src/collectible_animation.c \
			  src/exit_animation.c \
			  src/player_animation.c \
			  src/player_animation_utils.c \
			  src/player_animation_init.c \
			  src/player_sprite.c \
			  src/player_cleanup.c \
			  src/cleanup.c \
			  src/cleanup_utils.c \
			  src/render_map.c \
			  src/render_utils.c \
			  src/game_renderer.c \
			  src/tile_renderer.c \
			  src/player_utils.c \
			  src/input_handler.c \
			  src/ui_renderer.c \
			  src/enemy_system.c \
			  src/enemy_movement.c \
			  src/enemy_display.c \
			  src/enemy_utils.c \
			  get_next_line/get_next_line.c \
			  get_next_line/get_next_line_utils.c

OBJS		= $(SRCS:.c=.o)

INCLUDES	= -I includes -I $(LIBFT_DIR) -I get_next_line -I $(MLX_DIR)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR) > /dev/null 2>&1
	@make -C $(MLX_DIR) > /dev/null 2>&1
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) -o $(NAME) > /dev/null 2>&1
	@echo "\033[1;32m[$(NAME)] created successfully.\033[0m"

clean:
	@make -C $(LIBFT_DIR) clean > /dev/null 2>&1
	@make -C $(MLX_DIR) clean > /dev/null 2>&1
	@rm -f $(OBJS) > /dev/null 2>&1

fclean: clean
	@make -C $(LIBFT_DIR) fclean > /dev/null 2>&1
	@make -C $(MLX_DIR) clean > /dev/null 2>&1
	@rm -f $(NAME) > /dev/null 2>&1
	@echo "\033[1;31m[$(NAME)] executables removed.\033[0m"

re: fclean all
	@echo "\033[1;34m[$(NAME)] project rebuilt successfully.\033[0m"


%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ > /dev/null 2>&1

.PHONY: all clean fclean re