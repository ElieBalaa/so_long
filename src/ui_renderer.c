
#include "../includes/so_long.h"

void	render_ui_shadow(t_game *game)
{
	int	x;
	int	y;

	x = 12;
	while (x < (2 * TILE_SIZE + 12))
	{
		y = 12;
		while (y < 57)
		{
			mlx_pixel_put(game->mlx, game->win, x, y, 0x1E3A1E);
			y++;
		}
		x++;
	}
}

void	render_ui_background(t_game *game)
{
	int	x;
	int	y;

	x = 10;
	while (x < (2 * TILE_SIZE + 10))
	{
		y = 10;
		while (y < 55)
		{
			mlx_pixel_put(game->mlx, game->win, x, y, 0x1E3A1E);
			y++;
		}
		x++;
	}
}

void	render_ui_border(t_game *game)
{
	int	x;
	int	y;

	x = 10;
	while (x < (2 * TILE_SIZE + 10))
	{
		mlx_pixel_put(game->mlx, game->win, x, 10, 0x4A7C59);
		mlx_pixel_put(game->mlx, game->win, x, 54, 0x4A7C59);
		x++;
	}
	y = 10;
	while (y < 55)
	{
		mlx_pixel_put(game->mlx, game->win, 10, y, 0x4A7C59);
		mlx_pixel_put(game->mlx, game->win, (2 * TILE_SIZE + 9), y, 0x4A7C59);
		y++;
	}
}

void	render_move_count(t_game *game)
{
	char	*move_str;
	char	*move_num;

	move_num = ft_itoa(game->move_count);
	move_str = ft_strjoin("Moves: ", move_num);
	mlx_string_put(game->mlx, game->win, 20, 30, 0xF0F0F0, move_str);
	free(move_num);
	free(move_str);
}

void	render_ui_stats(t_game *game)
{
	char	*collect_str;
	char	*collect_num;

	render_ui_shadow(game);
	render_ui_background(game);
	render_ui_border(game);
	render_move_count(game);
	collect_num = ft_itoa(game->collectibles_left);
	collect_str = ft_strjoin("Items Left: ", collect_num);
	mlx_string_put(game->mlx, game->win, 20, 50, 0xF0F0F0, collect_str);
	free(collect_num);
	free(collect_str);
} 
