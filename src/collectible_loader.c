#include "../includes/so_long.h"
#include "../mlx/mlx.h"

void	load_collectible_images(t_game *game, int size)
{
	game->img_collect_radio = mlx_xpm_file_to_image(game->mlx,
			"textures/radio.xpm", &size, &size);
	game->img_collect_helmet = mlx_xpm_file_to_image(game->mlx,
			"textures/helmet.xpm", &size, &size);
	game->img_collect_map = mlx_xpm_file_to_image(game->mlx,
			"textures/military_map.xpm", &size, &size);
	game->img_collect_ammo = mlx_xpm_file_to_image(game->mlx,
			"textures/ammo_crate_closed.xpm", &size, &size);
	game->img_collect_flag = mlx_xpm_file_to_image(game->mlx,
			"textures/lebanese_flag.xpm", &size, &size);
	game->img_collect_cedar = mlx_xpm_file_to_image(game->mlx,
			"textures/cedar_tree.xpm", &size, &size);
}

void	set_collectible_fallbacks(t_game *game)
{
	if (!game->img_collect_radio)
		game->img_collect_radio = game->img_collect;
	if (!game->img_collect_helmet)
		game->img_collect_helmet = game->img_collect;
	if (!game->img_collect_map)
		game->img_collect_map = game->img_collect;
	if (!game->img_collect_ammo)
		game->img_collect_ammo = game->img_collect;
	if (!game->img_collect_flag)
		game->img_collect_flag = game->img_collect;
	if (!game->img_collect_cedar)
		game->img_collect_cedar = game->img_collect;
}

void	*get_collectible_variant(t_game *game, int row, int col)
{
	int	variant;

	variant = (row * 13 + col * 19) % 6;
	if (variant == 0 && game->img_collect_radio)
		return (game->img_collect_radio);
	else if (variant == 1 && game->img_collect_helmet)
		return (game->img_collect_helmet);
	else if (variant == 2 && game->img_collect_map)
		return (game->img_collect_map);
	else if (variant == 3 && game->img_collect_ammo)
		return (game->img_collect_ammo);
	else if (variant == 4 && game->img_collect_flag)
		return (game->img_collect_flag);
	else if (variant == 5 && game->img_collect_cedar)
		return (game->img_collect_cedar);
	else
		return (game->img_collect);
}

void	cleanup_collectible_images(t_game *game)
{
	if (game->img_collect_radio && game->mlx
		&& game->img_collect_radio != game->img_collect)
		mlx_destroy_image(game->mlx, game->img_collect_radio);
	if (game->img_collect_helmet && game->mlx
		&& game->img_collect_helmet != game->img_collect)
		mlx_destroy_image(game->mlx, game->img_collect_helmet);
	if (game->img_collect_map && game->mlx
		&& game->img_collect_map != game->img_collect)
		mlx_destroy_image(game->mlx, game->img_collect_map);
	if (game->img_collect_ammo && game->mlx
		&& game->img_collect_ammo != game->img_collect)
		mlx_destroy_image(game->mlx, game->img_collect_ammo);
	if (game->img_collect_flag && game->mlx
		&& game->img_collect_flag != game->img_collect)
		mlx_destroy_image(game->mlx, game->img_collect_flag);
	if (game->img_collect_cedar && game->mlx
		&& game->img_collect_cedar != game->img_collect)
		mlx_destroy_image(game->mlx, game->img_collect_cedar);
} 
 
