#include "../includes/so_long.h"
#include "../mlx/mlx.h"

static void	set_left_animation_fallbacks(t_game *game)
{
	if (!game->img_player_left_1)
		game->img_player_left_1 = game->img_player;
	if (!game->img_player_left_2)
		game->img_player_left_2 = game->img_player;
	if (!game->img_player_left_3)
		game->img_player_left_3 = game->img_player;
	if (!game->img_player_left_4)
		game->img_player_left_4 = game->img_player;
}

static void	set_right_animation_fallbacks(t_game *game)
{
	if (!game->img_player_right_1)
		game->img_player_right_1 = game->img_player;
	if (!game->img_player_right_2)
		game->img_player_right_2 = game->img_player;
	if (!game->img_player_right_3)
		game->img_player_right_3 = game->img_player;
	if (!game->img_player_right_4)
		game->img_player_right_4 = game->img_player;
}

static void	set_up_animation_fallbacks(t_game *game)
{
	if (!game->img_player_up_1)
		game->img_player_up_1 = game->img_player;
	if (!game->img_player_up_2)
		game->img_player_up_2 = game->img_player;
	if (!game->img_player_up_3)
		game->img_player_up_3 = game->img_player;
	if (!game->img_player_up_4)
		game->img_player_up_4 = game->img_player;
}

static void	set_down_animation_fallbacks(t_game *game)
{
	if (!game->img_player_down_1)
		game->img_player_down_1 = game->img_player;
	if (!game->img_player_down_2)
		game->img_player_down_2 = game->img_player;
	if (!game->img_player_down_3)
		game->img_player_down_3 = game->img_player;
	if (!game->img_player_down_4)
		game->img_player_down_4 = game->img_player;
}

void	set_player_animation_fallbacks(t_game *game)
{
	set_left_animation_fallbacks(game);
	set_right_animation_fallbacks(game);
	set_up_animation_fallbacks(game);
	set_down_animation_fallbacks(game);
} 
