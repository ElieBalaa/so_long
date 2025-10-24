#include "../includes/so_long.h"

void	load_enemy_images(t_game *game, int size)
{
	game->img_terrorist = mlx_xpm_file_to_image(game->mlx,
			"textures/terrorist.xpm", &size, &size);
	game->img_terrorist_left_1 = mlx_xpm_file_to_image(game->mlx,
			"textures/terrorist_left_1.xpm", &size, &size);
	game->img_terrorist_left_2 = mlx_xpm_file_to_image(game->mlx,
			"textures/terrorist_left_2.xpm", &size, &size);
	game->img_terrorist_left_3 = mlx_xpm_file_to_image(game->mlx,
			"textures/terrorist_left_3.xpm", &size, &size);
	game->img_terrorist_right_1 = mlx_xpm_file_to_image(game->mlx,
			"textures/terrorist_right_1.xpm", &size, &size);
	game->img_terrorist_right_2 = mlx_xpm_file_to_image(game->mlx,
			"textures/terrorist_right_2.xpm", &size, &size);
	game->img_terrorist_right_3 = mlx_xpm_file_to_image(game->mlx,
			"textures/terrorist_right_3.xpm", &size, &size);
}

void	init_enemies(t_game *game)
{
	int	row;
	int	col;

	game->enemy_count = 0;
	row = 0;
	while (game->map[row] && game->enemy_count < MAX_ENEMIES)
	{
		col = 0;
		while (game->map[row][col] && game->enemy_count < MAX_ENEMIES)
		{
			process_enemy_tile(game, row, col);
			col++;
		}
		row++;
	}
}

void	init_patrol_enemy(t_game *game, int row, int col)
{
	game->enemies[game->enemy_count].x = col;
	game->enemies[game->enemy_count].y = row;
	game->enemies[game->enemy_count].prev_x = col;
	game->enemies[game->enemy_count].prev_y = row;
	game->enemies[game->enemy_count].type = ENEMY_PATROL;
	game->enemies[game->enemy_count].direction = ANIM_RIGHT;
	game->enemies[game->enemy_count].anim_frame = 0;
	game->enemies[game->enemy_count].patrol_start = col - 2;
	game->enemies[game->enemy_count].patrol_end = col + 2;
	gettimeofday(&game->enemies[game->enemy_count].last_move_time, NULL);
	game->enemy_count++;
}

int	enemy_can_move_to(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->cols || y >= game->rows)
		return (0);
	if (game->map[y][x] == '1')
		return (0);
	if (game->map[y][x] == 'C')
		return (0);
	return (1);
}

long	get_time_diff_ms(struct timeval *start, struct timeval *end)
{
	long	sec_diff;
	long	usec_diff;

	sec_diff = end->tv_sec - start->tv_sec;
	usec_diff = end->tv_usec - start->tv_usec;
	return (sec_diff * 1000 + usec_diff / 1000);
} 
