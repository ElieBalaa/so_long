#include "../includes/so_long.h"
#include "../mlx/mlx.h"

void	cleanup_basic_images(t_game *game)
{
	if (game->img_wall && game->mlx)
		mlx_destroy_image(game->mlx, game->img_wall);
	if (game->img_floor && game->mlx)
		mlx_destroy_image(game->mlx, game->img_floor);
	if (game->img_player && game->mlx)
		mlx_destroy_image(game->mlx, game->img_player);
	if (game->img_collect && game->mlx)
		mlx_destroy_image(game->mlx, game->img_collect);
	if (game->img_exit && game->mlx)
		mlx_destroy_image(game->mlx, game->img_exit);
	if (game->img_runway && game->mlx)
		mlx_destroy_image(game->mlx, game->img_runway);
	if (game->img_exit_1 && game->mlx)
		mlx_destroy_image(game->mlx, game->img_exit_1);
	if (game->img_exit_2 && game->mlx)
		mlx_destroy_image(game->mlx, game->img_exit_2);
	if (game->img_exit_3 && game->mlx)
		mlx_destroy_image(game->mlx, game->img_exit_3);
	if (game->img_exit_4 && game->mlx)
		mlx_destroy_image(game->mlx, game->img_exit_4);
}

void	cleanup_floor_images(t_game *game)
{
	if (game->img_floor_1 && game->mlx
		&& game->img_floor_1 != game->img_floor)
		mlx_destroy_image(game->mlx, game->img_floor_1);
	if (game->img_floor_2 && game->mlx
		&& game->img_floor_2 != game->img_floor)
		mlx_destroy_image(game->mlx, game->img_floor_2);
	if (game->img_floor_3 && game->mlx
		&& game->img_floor_3 != game->img_floor)
		mlx_destroy_image(game->mlx, game->img_floor_3);
}

void	cleanup_wall_images(t_game *game)
{
	if (game->img_wall_1 && game->mlx
		&& game->img_wall_1 != game->img_wall)
		mlx_destroy_image(game->mlx, game->img_wall_1);
	if (game->img_wall_2 && game->mlx
		&& game->img_wall_2 != game->img_wall)
		mlx_destroy_image(game->mlx, game->img_wall_2);
	if (game->img_wall_3 && game->mlx
		&& game->img_wall_3 != game->img_wall)
		mlx_destroy_image(game->mlx, game->img_wall_3);
}

void	cleanup_decoration_images(t_game *game)
{
	if (game->img_cedar_tree && game->mlx)
		mlx_destroy_image(game->mlx, game->img_cedar_tree);
	if (game->img_lebanese_flag && game->mlx)
		mlx_destroy_image(game->mlx, game->img_lebanese_flag);
	if (game->img_ammo_crate && game->mlx)
		mlx_destroy_image(game->mlx, game->img_ammo_crate);
}

void	cleanup_corner_images(t_game *game)
{
	if (game->img_wall_corner_top_left && game->mlx
		&& game->img_wall_corner_top_left != game->img_wall)
		mlx_destroy_image(game->mlx, game->img_wall_corner_top_left);
	if (game->img_wall_corner_top_right && game->mlx
		&& game->img_wall_corner_top_right != game->img_wall)
		mlx_destroy_image(game->mlx, game->img_wall_corner_top_right);
	if (game->img_wall_corner_bottom_left && game->mlx
		&& game->img_wall_corner_bottom_left != game->img_wall)
		mlx_destroy_image(game->mlx, game->img_wall_corner_bottom_left);
	if (game->img_wall_corner_bottom_right && game->mlx
		&& game->img_wall_corner_bottom_right != game->img_wall)
		mlx_destroy_image(game->mlx, game->img_wall_corner_bottom_right);
} 
 
