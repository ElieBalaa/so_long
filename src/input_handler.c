#include "../includes/so_long.h"
#include "../mlx/mlx.h"
#include <stdlib.h>
#include <unistd.h>

static void	complete_cleanup_and_exit(t_game *game)
{
	cleanup_game(game);
	_exit(0);
}

int	close_game(t_game *game)
{
	complete_cleanup_and_exit(game);
	return (0);
}

static void	handle_movement_keys(int keycode, t_game *game, int x, int y)
{
	if (keycode == KEY_W || keycode == KEY_UP)
	{
		update_player_animation(game, ANIM_UP);
		move_player(game, y - 1, x);
	}
	else if (keycode == KEY_S || keycode == KEY_DOWN)
	{
		update_player_animation(game, ANIM_DOWN);
		move_player(game, y + 1, x);
	}
	else if (keycode == KEY_A || keycode == KEY_LEFT)
	{
		update_player_animation(game, ANIM_LEFT);
		move_player(game, y, x - 1);
	}
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
	{
		update_player_animation(game, ANIM_RIGHT);
		move_player(game, y, x + 1);
	}
}

int	handle_key(int keycode, t_game *game)
{
	int	x;
	int	y;

	find_player_pos(game->map, &x, &y);
	if (keycode == KEY_ESC || keycode == KEY_Q)
		complete_cleanup_and_exit(game);
	else
	{
		int prev_moves = game->move_count;
		handle_movement_keys(keycode, game, x, y);
		if (game->move_count > prev_moves)
			printf("Number of Movements: %d\n", game->move_count);
	}
	return (0);
} 
 
