#include "../includes/so_long.h"
#include "../mlx/mlx.h"

int	count_collectibles(char **map)
{
	int	row;
	int	col;
	int	count;

	count = 0;
	row = 0;
	while (map[row])
	{
		col = 0;
		while (map[row][col])
		{
			if (map[row][col] == 'C')
				count++;
			col++;
		}
		row++;
	}
	return (count);
}

void	init_game(t_game *game, char **map)
{
	game->map = map;
	game->rows = 0;
	while (map[game->rows])
		game->rows++;
	game->cols = ft_strlen(map[0]);
	game->collectibles_left = count_collectibles(map);
	game->move_count = 0;
	game->exit_anim_timer = 0;
	game->exit_anim_frame = 0;
	game->img_exit_1 = NULL;
	game->img_exit_2 = NULL;
	game->img_exit_3 = NULL;
	game->img_exit_4 = NULL;
	game->mlx = mlx_init();
	if (!game->mlx)
		exit(1);
	game->win = mlx_new_window(game->mlx,
			game->cols * TILE_SIZE,
			game->rows * TILE_SIZE,
			"So Long");
	if (!game->win)
		exit(1);
}

void	load_basic_images(t_game *game, int size)
{
	game->img_wall = mlx_xpm_file_to_image(game->mlx,
			"textures/sandbags.xpm", &size, &size);
	game->img_floor = mlx_xpm_file_to_image(game->mlx,
			"textures/floor.xpm", &size, &size);
	game->img_player = mlx_xpm_file_to_image(game->mlx,
			"textures/player.xpm", &size, &size);
	game->img_collect = mlx_xpm_file_to_image(game->mlx,
			"textures/collectible.xpm", &size, &size);
	game->img_exit = mlx_xpm_file_to_image(game->mlx,
			"textures/exit.xpm", &size, &size);
	game->img_runway = mlx_xpm_file_to_image(game->mlx,
			"textures/runway.xpm", &size, &size);
	game->img_exit_1 = mlx_xpm_file_to_image(game->mlx,
			"textures/exit_1.xpm", &size, &size);
	game->img_exit_2 = mlx_xpm_file_to_image(game->mlx,
			"textures/exit_2.xpm", &size, &size);
	game->img_exit_3 = mlx_xpm_file_to_image(game->mlx,
			"textures/exit_3.xpm", &size, &size);
	game->img_exit_4 = mlx_xpm_file_to_image(game->mlx,
			"textures/exit_4.xpm", &size, &size);
}

void	load_floor_images(t_game *game, int size)
{
	game->img_floor_1 = mlx_xpm_file_to_image(game->mlx,
			"textures/background64.xpm", &size, &size);
	game->img_floor_2 = mlx_xpm_file_to_image(game->mlx,
			"textures/battlefield_tile_1.xpm", &size, &size);
	game->img_floor_3 = mlx_xpm_file_to_image(game->mlx,
			"textures/battlefield_tile_2.xpm", &size, &size);
	if (!game->img_floor_1)
		game->img_floor_1 = game->img_floor;
	if (!game->img_floor_2)
		game->img_floor_2 = game->img_floor;
	if (!game->img_floor_3)
		game->img_floor_3 = game->img_floor;
}

void	load_wall_images(t_game *game, int size)
{
	game->img_wall_1 = mlx_xpm_file_to_image(game->mlx,
			"textures/wall_1.xpm", &size, &size);
	game->img_wall_2 = mlx_xpm_file_to_image(game->mlx,
			"textures/wall_2.xpm", &size, &size);
	game->img_wall_3 = mlx_xpm_file_to_image(game->mlx,
			"textures/wall_3.xpm", &size, &size);
	if (!game->img_wall_1)
		game->img_wall_1 = game->img_wall;
	if (!game->img_wall_2)
		game->img_wall_2 = game->img_wall;
	if (!game->img_wall_3)
		game->img_wall_3 = game->img_wall;
} 
