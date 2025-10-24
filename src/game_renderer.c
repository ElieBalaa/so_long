#include "../includes/so_long.h"
#include "../mlx/mlx.h"

void	render_map(t_game *game)
{
	int	row;
	int	col;

	row = 0;
	while (game->map[row])
	{
		col = 0;
		while (game->map[row][col])
		{
			render_enhanced_tile(game, row, col);
			col++;
		}
		row++;
	}
	render_enemies(game);
	render_ui_stats(game);
} 
