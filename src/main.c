#include "../includes/so_long.h"

static int	animation_loop(t_game *game)
{
	animate_all_collectibles(game);
	animate_exit(game);
	update_enemies(game);
	update_enemy_display(game);
	return (0);
}

static char	**load_and_validate_map(char *filename)
{
	char	**map;

	map = read_map(filename);
	if (!map)
	{
		write(2, "Error\nFailed to read map.\n", 26);
		return (NULL);
	}
	if (!validate_map(map))
	{
		free_map(map);
		write(2, "Error\nInvalid map.\n", 20);
		return (NULL);
	}
	return (map);
}

static void	start_game(t_game *game)
{
	load_images(game);
	init_enemies(game);
	render_map(game);
	mlx_hook(game->win, 2, 1L<<0, handle_key, game);
	mlx_hook(game->win, 17, 1L<<17, close_game, game);
	mlx_loop_hook(game->mlx, animation_loop, game);
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	char	**map;
	t_game	game;

	if (argc != 2)
	{
		write(2, "Usage: ./so_long <map_file.ber>\n", 33);
		return (1);
	}
	map = load_and_validate_map(argv[1]);
	if (!map)
		return (1);
	init_game(&game, map);
	start_game(&game);
	free_map(map);
	return (0);
}
