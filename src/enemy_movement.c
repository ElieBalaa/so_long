#include "../includes/so_long.h"

static void	move_enemy_right(t_game *game, t_enemy *enemy)
{
	int	new_x;
	int	new_y;

	new_x = enemy->x + 1;
	new_y = enemy->y;
	if (new_x >= enemy->patrol_end || !enemy_can_move_to(game, new_x, new_y))
		enemy->direction = ANIM_LEFT;
	else
		enemy->x = new_x;
}

static void	move_enemy_left(t_game *game, t_enemy *enemy)
{
	int	new_x;
	int	new_y;

	new_x = enemy->x - 1;
	new_y = enemy->y;
	if (new_x <= enemy->patrol_start || !enemy_can_move_to(game, new_x, new_y))
		enemy->direction = ANIM_RIGHT;
	else
		enemy->x = new_x;
}

void	update_patrol_enemy_with_collision(t_game *game, t_enemy *enemy)
{
	struct timeval	current_time;
	long			time_diff;

	gettimeofday(&current_time, NULL);
	time_diff = get_time_diff_ms(&enemy->last_move_time, &current_time);
	if (time_diff >= PATROL_SPEED_MS)
	{
		enemy->last_move_time = current_time;
		enemy->prev_x = enemy->x;
		enemy->prev_y = enemy->y;
		if (enemy->direction == ANIM_RIGHT)
			move_enemy_right(game, enemy);
		else
			move_enemy_left(game, enemy);
		enemy->anim_frame = (enemy->anim_frame + 1) % 3;
	}
}

void	update_enemies(t_game *game)
{
	int	i;
	int	player_x;
	int	player_y;

	i = 0;
	while (i < game->enemy_count)
	{
		if (game->enemies[i].type == ENEMY_PATROL)
			update_patrol_enemy_with_collision(game, &game->enemies[i]);
		i++;
	}
	find_player_pos(game->map, &player_x, &player_y);
	i = 0;
	while (i < game->enemy_count)
	{
		if (game->enemies[i].x == player_x && game->enemies[i].y == player_y)
		{
			game_over(game);
			return ;
		}
		i++;
	}
} 
