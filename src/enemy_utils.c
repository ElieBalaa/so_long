#include "../includes/so_long.h"
#include <unistd.h>

void	init_static_enemy(t_game *game, int row, int col)
{
	game->enemies[game->enemy_count].x = col;
	game->enemies[game->enemy_count].y = row;
	game->enemies[game->enemy_count].prev_x = col;
	game->enemies[game->enemy_count].prev_y = row;
	game->enemies[game->enemy_count].type = ENEMY_STATIC;
	game->enemies[game->enemy_count].direction = 0;
	game->enemies[game->enemy_count].anim_frame = 0;
	game->enemy_count++;
}

void	process_enemy_tile(t_game *game, int row, int col)
{
	if (game->map[row][col] == 'T')
		init_static_enemy(game, row, col);
	else if (game->map[row][col] == 'M')
		init_patrol_enemy(game, row, col);
}

int	check_enemy_collision(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->enemy_count)
	{
		if (game->enemies[i].x == x && game->enemies[i].y == y)
			return (1);
		i++;
	}
	return (0);
}

void	game_over(t_game *game)
{
	printf("GAME OVER! You were caught by a terrorist!\n");
	printf("Final Score: %d moves\n", game->move_count);
	cleanup_game(game);
	_exit(0);
}

void	cleanup_enemy_images(t_game *game)
{
	if (game->img_terrorist && game->mlx)
		mlx_destroy_image(game->mlx, game->img_terrorist);
	if (game->img_terrorist_left_1 && game->mlx)
		mlx_destroy_image(game->mlx, game->img_terrorist_left_1);
	if (game->img_terrorist_left_2 && game->mlx)
		mlx_destroy_image(game->mlx, game->img_terrorist_left_2);
	if (game->img_terrorist_left_3 && game->mlx)
		mlx_destroy_image(game->mlx, game->img_terrorist_left_3);
	if (game->img_terrorist_right_1 && game->mlx)
		mlx_destroy_image(game->mlx, game->img_terrorist_right_1);
	if (game->img_terrorist_right_2 && game->mlx)
		mlx_destroy_image(game->mlx, game->img_terrorist_right_2);
	if (game->img_terrorist_right_3 && game->mlx)
		mlx_destroy_image(game->mlx, game->img_terrorist_right_3);
}
