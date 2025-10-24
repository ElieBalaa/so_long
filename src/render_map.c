#include "../includes/so_long.h"
#include "../mlx/mlx.h"

void	put_tile(t_game *game, void *img, int row, int col)
{
	if (img)
	{
		mlx_put_image_to_window(game->mlx, game->win, img,
			col * TILE_SIZE, row * TILE_SIZE);
	}
}

void	*get_floor_variant(t_game *game, int row, int col)
{
	int	variant;

	variant = (row * 7 + col * 3) % 3;
	if (variant == 0 && game->img_floor_1)
		return (game->img_floor_1);
	else if (variant == 1 && game->img_floor_2)
		return (game->img_floor_2);
	else if (variant == 2 && game->img_floor_3)
		return (game->img_floor_3);
	else
		return (game->img_floor);
}

void	*get_wall_variant(t_game *game, int row, int col)
{
	int	variant;

	variant = (row * 5 + col * 2) % 3;
	if (variant == 0 && game->img_wall_1)
		return (game->img_wall_1);
	else if (variant == 1 && game->img_wall_2)
		return (game->img_wall_2);
	else if (variant == 2 && game->img_wall_3)
		return (game->img_wall_3);
	else
		return (game->img_wall);
}

int	is_border_wall(t_game *game, int row, int col)
{
	if (row == 0 || row == game->rows - 1)
		return (1);
	if (col == 0 || col == game->cols - 1)
		return (1);
	return (0);
}

void	*get_corner_tile(t_game *game, int row, int col)
{
	if (row == 0 && col == 0)
		return (game->img_wall_corner_top_left);
	else if (row == 0 && col == game->cols - 1)
		return (game->img_wall_corner_top_right);
	else if (row == game->rows - 1 && col == 0)
		return (game->img_wall_corner_bottom_left);
	else if (row == game->rows - 1 && col == game->cols - 1)
		return (game->img_wall_corner_bottom_right);
	else
		return (NULL);
}
