#include "../includes/so_long.h"
#include "../mlx/mlx.h"

void	*get_edge_tile(t_game *game, int row, int col)
{
	if (row == 0)
		return (game->img_wall_edge_top);
	else if (row == game->rows - 1)
		return (game->img_wall_edge_bottom);
	else if (col == 0)
		return (game->img_wall_edge_left);
	else if (col == game->cols - 1)
		return (game->img_wall_edge_right);
	else
		return (get_wall_variant(game, row, col));
}

void	*get_border_wall_tile(t_game *game, int row, int col)
{
	void	*corner_tile;

	corner_tile = get_corner_tile(game, row, col);
	if (corner_tile)
		return (corner_tile);
	else
		return (get_edge_tile(game, row, col));
}

void	*get_decoration(t_game *game, int row, int col)
{
	(void)game;
	(void)row;
	(void)col;
	return (NULL);
}

int	should_add_decoration(int row, int col)
{
	(void)row;
	(void)col;
	return (0);
}

void	render_floor_and_decorations(t_game *game, int row, int col)
{
	void	*floor_img;
	void	*decoration;

	floor_img = get_floor_variant(game, row, col);
	put_tile(game, floor_img, row, col);
	if (game->map[row][col] == '0' && should_add_decoration(row, col))
	{
		decoration = get_decoration(game, row, col);
		if (decoration)
			put_tile(game, decoration, row, col);
	}
} 
