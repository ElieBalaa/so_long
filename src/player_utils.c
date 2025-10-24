#include "../includes/so_long.h"
#include "../mlx/mlx.h"

void	find_player_pos(char **map, int *x, int *y)
{
	int	row;
	int	col;

	row = 0;
	while (map[row])
	{
		col = 0;
		while (map[row][col])
		{
			if (map[row][col] == 'P')
			{
				*x = col;
				*y = row;
				return ;
			}
			col++;
		}
		row++;
	}
}

void	handle_collectible(t_game *game)
{
	int	exit_x;
	int	exit_y;
	int	row;
	int	col;

	game->collectibles_left--;
	render_ui_stats(game);
	if (game->collectibles_left == 0)
	{
		row = 0;
		while (game->map[row])
		{
			col = 0;
			while (game->map[row][col])
			{
				if (game->map[row][col] == 'E')
				{
					exit_y = row;
					exit_x = col;
					render_tile(game, exit_y, exit_x);
					return ;
				}
				col++;
			}
			row++;
		}
	}
}

int	check_exit(t_game *game)
{
	if (game->collectibles_left == 0)
	{
		printf("Congratulations! You won in %d moves!\n", game->move_count + 1);
		cleanup_game(game);
		exit(0);
	}
	else
	{
		render_ui_stats(game);
		return (1);
	}
	return (0);
}

void	update_player_position(t_game *game, int new_y, int new_x)
{
	int	old_y;
	int	old_x;

	find_player_pos(game->map, &old_x, &old_y);
	game->map[old_y][old_x] = '0';
	game->map[new_y][new_x] = 'P';
	game->move_count++;
	render_ui_stats(game);
	render_tile(game, old_y, old_x);
	render_tile(game, new_y, new_x);
}

void	move_player(t_game *game, int new_y, int new_x)
{
	if (game->map[new_y][new_x] == '1')
		return ;
	if (check_enemy_collision(game, new_x, new_y))
	{
		game_over(game);
		return ;
	}
	if (game->map[new_y][new_x] == 'C')
	{
		handle_collectible(game);
		game->map[new_y][new_x] = '0';
	}
	if (game->map[new_y][new_x] == 'E')
		if (check_exit(game))
			return ;
	update_player_position(game, new_y, new_x);
}
