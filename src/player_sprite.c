#include "../includes/so_long.h"
#include "../mlx/mlx.h"

void	*get_left_animation_frame(t_game *game)
{
	if (game->anim_frame == 0)
		return (game->img_player_left_1);
	else if (game->anim_frame == 1)
		return (game->img_player_left_2);
	else if (game->anim_frame == 2)
		return (game->img_player_left_3);
	else
		return (game->img_player_left_4);
}

void	*get_right_animation_frame(t_game *game)
{
	if (game->anim_frame == 0)
		return (game->img_player_right_1);
	else if (game->anim_frame == 1)
		return (game->img_player_right_2);
	else if (game->anim_frame == 2)
		return (game->img_player_right_3);
	else
		return (game->img_player_right_4);
}

void	*get_up_animation_frame(t_game *game)
{
	if (game->anim_frame == 0)
		return (game->img_player_up_1);
	else if (game->anim_frame == 1)
		return (game->img_player_up_2);
	else if (game->anim_frame == 2)
		return (game->img_player_up_3);
	else
		return (game->img_player_up_4);
}

void	*get_down_animation_frame(t_game *game)
{
	if (game->anim_frame == 0)
		return (game->img_player_down_1);
	else if (game->anim_frame == 1)
		return (game->img_player_down_2);
	else if (game->anim_frame == 2)
		return (game->img_player_down_3);
	else
		return (game->img_player_down_4);
}

void	*get_current_player_sprite(t_game *game)
{
	if (game->anim_direction == ANIM_LEFT)
		return (get_left_animation_frame(game));
	else if (game->anim_direction == ANIM_RIGHT)
		return (get_right_animation_frame(game));
	else if (game->anim_direction == ANIM_UP)
		return (get_up_animation_frame(game));
	else if (game->anim_direction == ANIM_DOWN)
		return (get_down_animation_frame(game));
	else
		return (game->img_player);
} 
