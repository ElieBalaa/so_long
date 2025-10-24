#include "../includes/so_long.h"

static int	check_enemy_moved(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->enemy_count)
	{
		if (game->enemies[i].x != game->enemies[i].prev_x
			|| game->enemies[i].y != game->enemies[i].prev_y)
			return (1);
		i++;
	}
	return (0);
}

static int	is_tile_occupied_by_enemy(t_game *game, int x, int y, int exclude)
{
	int	j;

	j = 0;
	while (j < game->enemy_count)
	{
		if (j != exclude && game->enemies[j].x == x
			&& game->enemies[j].y == y)
			return (1);
		j++;
	}
	return (0);
}

void	update_enemy_display(t_game *game)
{
	int	i;

	if (!check_enemy_moved(game))
		return ;
	i = 0;
	while (i < game->enemy_count)
	{
		if (game->enemies[i].x != game->enemies[i].prev_x
			|| game->enemies[i].y != game->enemies[i].prev_y)
		{
			if (!is_tile_occupied_by_enemy(game, game->enemies[i].prev_x,
					game->enemies[i].prev_y, i))
				render_enhanced_tile(game, game->enemies[i].prev_y,
					game->enemies[i].prev_x);
		}
		i++;
	}
	render_enemies(game);
}

void	*get_enemy_sprite(t_game *game, t_enemy *enemy)
{
	if (enemy->type == ENEMY_STATIC)
		return (game->img_terrorist);
	if (enemy->direction == ANIM_LEFT)
	{
		if (enemy->anim_frame == 0)
			return (game->img_terrorist_left_1);
		else if (enemy->anim_frame == 1)
			return (game->img_terrorist_left_2);
		else
			return (game->img_terrorist_left_3);
	}
	else
	{
		if (enemy->anim_frame == 0)
			return (game->img_terrorist_right_1);
		else if (enemy->anim_frame == 1)
			return (game->img_terrorist_right_2);
		else
			return (game->img_terrorist_right_3);
	}
}

void	render_enemies(t_game *game)
{
	int		i;
	void	*sprite;

	i = 0;
	while (i < game->enemy_count)
	{
		sprite = get_enemy_sprite(game, &game->enemies[i]);
		if (sprite)
		{
			mlx_put_image_to_window(game->mlx, game->win, sprite,
				game->enemies[i].x * TILE_SIZE,
				game->enemies[i].y * TILE_SIZE);
		}
		i++;
	}
}
