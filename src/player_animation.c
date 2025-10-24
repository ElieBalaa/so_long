#include "../includes/so_long.h"
#include "../mlx/mlx.h"

static void	load_left_animation_images(t_game *game, int size)
{
	game->img_player_left_1 = mlx_xpm_file_to_image(game->mlx,
			"textures/left_walk_frame_1.xpm", &size, &size);
	game->img_player_left_2 = mlx_xpm_file_to_image(game->mlx,
			"textures/left_walk_frame_2.xpm", &size, &size);
	game->img_player_left_3 = mlx_xpm_file_to_image(game->mlx,
			"textures/left_walk_frame_3.xpm", &size, &size);
	game->img_player_left_4 = mlx_xpm_file_to_image(game->mlx,
			"textures/left_walk_frame_4.xpm", &size, &size);
}

static void	load_right_animation_images(t_game *game, int size)
{
	game->img_player_right_1 = mlx_xpm_file_to_image(game->mlx,
			"textures/right_walk_frame_1.xpm", &size, &size);
	game->img_player_right_2 = mlx_xpm_file_to_image(game->mlx,
			"textures/right_walk_frame_2.xpm", &size, &size);
	game->img_player_right_3 = mlx_xpm_file_to_image(game->mlx,
			"textures/right_walk_frame_3.xpm", &size, &size);
	game->img_player_right_4 = mlx_xpm_file_to_image(game->mlx,
			"textures/right_walk_frame_4.xpm", &size, &size);
}

static void	load_up_animation_images(t_game *game, int size)
{
	game->img_player_up_1 = mlx_xpm_file_to_image(game->mlx,
			"textures/walking_up_1.xpm", &size, &size);
	game->img_player_up_2 = mlx_xpm_file_to_image(game->mlx,
			"textures/walking_up_2.xpm", &size, &size);
	game->img_player_up_3 = mlx_xpm_file_to_image(game->mlx,
			"textures/walking_up_3.xpm", &size, &size);
	game->img_player_up_4 = mlx_xpm_file_to_image(game->mlx,
			"textures/walking_up_4.xpm", &size, &size);
}

static void	load_down_animation_images(t_game *game, int size)
{
	game->img_player_down_1 = mlx_xpm_file_to_image(game->mlx,
			"textures/walking_down_1.xpm", &size, &size);
	game->img_player_down_2 = mlx_xpm_file_to_image(game->mlx,
			"textures/walking_down_2.xpm", &size, &size);
	game->img_player_down_3 = mlx_xpm_file_to_image(game->mlx,
			"textures/walking_down_3.xpm", &size, &size);
	game->img_player_down_4 = mlx_xpm_file_to_image(game->mlx,
			"textures/walking_down_4.xpm", &size, &size);
}

void	load_player_animation_images(t_game *game, int size)
{
	load_left_animation_images(game, size);
	load_right_animation_images(game, size);
	load_up_animation_images(game, size);
	load_down_animation_images(game, size);
} 
