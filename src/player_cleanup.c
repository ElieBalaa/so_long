#include "../includes/so_long.h"
#include "../mlx/mlx.h"

void	cleanup_left_animation_images(t_game *game)
{
	if (game->img_player_left_1 && game->mlx
		&& game->img_player_left_1 != game->img_player)
		mlx_destroy_image(game->mlx, game->img_player_left_1);
	if (game->img_player_left_2 && game->mlx
		&& game->img_player_left_2 != game->img_player)
		mlx_destroy_image(game->mlx, game->img_player_left_2);
	if (game->img_player_left_3 && game->mlx
		&& game->img_player_left_3 != game->img_player)
		mlx_destroy_image(game->mlx, game->img_player_left_3);
	if (game->img_player_left_4 && game->mlx
		&& game->img_player_left_4 != game->img_player)
		mlx_destroy_image(game->mlx, game->img_player_left_4);
}

void	cleanup_right_animation_images(t_game *game)
{
	if (game->img_player_right_1 && game->mlx
		&& game->img_player_right_1 != game->img_player)
		mlx_destroy_image(game->mlx, game->img_player_right_1);
	if (game->img_player_right_2 && game->mlx
		&& game->img_player_right_2 != game->img_player)
		mlx_destroy_image(game->mlx, game->img_player_right_2);
	if (game->img_player_right_3 && game->mlx
		&& game->img_player_right_3 != game->img_player)
		mlx_destroy_image(game->mlx, game->img_player_right_3);
	if (game->img_player_right_4 && game->mlx
		&& game->img_player_right_4 != game->img_player)
		mlx_destroy_image(game->mlx, game->img_player_right_4);
}

void	cleanup_up_animation_images(t_game *game)
{
	if (game->img_player_up_1 && game->mlx
		&& game->img_player_up_1 != game->img_player)
		mlx_destroy_image(game->mlx, game->img_player_up_1);
	if (game->img_player_up_2 && game->mlx
		&& game->img_player_up_2 != game->img_player)
		mlx_destroy_image(game->mlx, game->img_player_up_2);
	if (game->img_player_up_3 && game->mlx
		&& game->img_player_up_3 != game->img_player)
		mlx_destroy_image(game->mlx, game->img_player_up_3);
	if (game->img_player_up_4 && game->mlx
		&& game->img_player_up_4 != game->img_player)
		mlx_destroy_image(game->mlx, game->img_player_up_4);
}

void	cleanup_down_animation_images(t_game *game)
{
	if (game->img_player_down_1 && game->mlx
		&& game->img_player_down_1 != game->img_player)
		mlx_destroy_image(game->mlx, game->img_player_down_1);
	if (game->img_player_down_2 && game->mlx
		&& game->img_player_down_2 != game->img_player)
		mlx_destroy_image(game->mlx, game->img_player_down_2);
	if (game->img_player_down_3 && game->mlx
		&& game->img_player_down_3 != game->img_player)
		mlx_destroy_image(game->mlx, game->img_player_down_3);
	if (game->img_player_down_4 && game->mlx
		&& game->img_player_down_4 != game->img_player)
		mlx_destroy_image(game->mlx, game->img_player_down_4);
}

void	cleanup_player_animation_images(t_game *game)
{
	cleanup_left_animation_images(game);
	cleanup_right_animation_images(game);
	cleanup_up_animation_images(game);
	cleanup_down_animation_images(game);
} 
