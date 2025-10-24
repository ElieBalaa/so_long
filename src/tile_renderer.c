#include "../includes/so_long.h"
#include "../mlx/mlx.h"

void	render_wall_tile(t_game *game, int row, int col)
{
	void	*wall_img;

	if (is_border_wall(game, row, col))
		wall_img = get_border_wall_tile(game, row, col);
	else
		wall_img = game->img_wall;
	put_tile(game, wall_img, row, col);
}

void	render_game_objects(t_game *game, int row, int col)
{
	if (game->map[row][col] == 'P')
		put_tile(game, get_current_player_sprite(game), row, col);
	else if (game->map[row][col] == 'C')
		put_tile(game, get_collectible_variant(game, row, col), row, col);
	else if (game->map[row][col] == 'E')
	{
		if (game->collectibles_left > 0)
		{
			if (game->img_runway)
				put_tile(game, game->img_runway, row, col);
			else
				put_tile(game, game->img_floor, row, col);
		}
		else
		{
			put_tile(game, get_exit_frame(game), row, col);
		}
	}
}

void	render_enhanced_tile(t_game *game, int row, int col)
{
	render_floor_and_decorations(game, row, col);
	if (game->map[row][col] == '1')
		render_wall_tile(game, row, col);
	else
		render_game_objects(game, row, col);
}

void	render_tile(t_game *game, int row, int col)
{
	render_enhanced_tile(game, row, col);
} 
 
