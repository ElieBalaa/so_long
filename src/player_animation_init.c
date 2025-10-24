#include "../includes/so_long.h"
#include "../mlx/mlx.h"

void	init_player_animation(t_game *game)
{
	game->anim_frame = 0;
	game->anim_direction = ANIM_DOWN;
	init_collectible_animation(game);
}

void	update_player_animation(t_game *game, int direction)
{
	game->anim_direction = direction;
	game->anim_frame = (game->anim_frame + 1) % ANIM_FRAMES;
} 
