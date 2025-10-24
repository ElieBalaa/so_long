#include "../includes/so_long.h"
#include "../mlx/mlx.h"

void	load_decoration_images(t_game *game, int size)
{
	game->img_cedar_tree = mlx_xpm_file_to_image(game->mlx,
			"textures/cedar_tree.xpm", &size, &size);
	game->img_lebanese_flag = mlx_xpm_file_to_image(game->mlx,
			"textures/lebanese_flag.xpm", &size, &size);
	game->img_ammo_crate = mlx_xpm_file_to_image(game->mlx,
			"textures/ammo_crate_closed.xpm", &size, &size);
}

void	load_corner_images(t_game *game, int size)
{
	game->img_wall_corner_top_left = mlx_xpm_file_to_image(game->mlx,
			"textures/wall_corner_top_left.xpm", &size, &size);
	game->img_wall_corner_top_right = mlx_xpm_file_to_image(game->mlx,
			"textures/wall_corner_top_right.xpm", &size, &size);
	game->img_wall_corner_bottom_left = mlx_xpm_file_to_image(game->mlx,
			"textures/wall_corner_bottom_left.xpm", &size, &size);
	game->img_wall_corner_bottom_right = mlx_xpm_file_to_image(game->mlx,
			"textures/wall_corner_bottom_right.xpm", &size, &size);
}

void	load_edge_images(t_game *game, int size)
{
	game->img_wall_edge_top = mlx_xpm_file_to_image(game->mlx,
			"textures/wall_edge_top.xpm", &size, &size);
	game->img_wall_edge_bottom = mlx_xpm_file_to_image(game->mlx,
			"textures/wall_edge_bottom.xpm", &size, &size);
	game->img_wall_edge_left = mlx_xpm_file_to_image(game->mlx,
			"textures/wall_edge_left.xpm", &size, &size);
	game->img_wall_edge_right = mlx_xpm_file_to_image(game->mlx,
			"textures/wall_edge_right.xpm", &size, &size);
}

void	set_corner_fallbacks(t_game *game)
{
	if (!game->img_wall_corner_top_left)
		game->img_wall_corner_top_left = game->img_wall;
	if (!game->img_wall_corner_top_right)
		game->img_wall_corner_top_right = game->img_wall;
	if (!game->img_wall_corner_bottom_left)
		game->img_wall_corner_bottom_left = game->img_wall;
	if (!game->img_wall_corner_bottom_right)
		game->img_wall_corner_bottom_right = game->img_wall;
}

void	set_edge_fallbacks(t_game *game)
{
	if (!game->img_wall_edge_top)
		game->img_wall_edge_top = game->img_wall;
	if (!game->img_wall_edge_bottom)
		game->img_wall_edge_bottom = game->img_wall;
	if (!game->img_wall_edge_left)
		game->img_wall_edge_left = game->img_wall;
	if (!game->img_wall_edge_right)
		game->img_wall_edge_right = game->img_wall;
} 
 
