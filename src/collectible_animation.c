#include "../includes/so_long.h"
#include "../mlx/mlx.h"
#include <math.h>
#include <unistd.h>

void	init_collectible_animation(t_game *game)
{
	game->collectible_anim_timer = 0;
}

void	update_collectible_animation(t_game *game)
{
	game->collectible_anim_timer++;
	if (game->collectible_anim_timer >= 360 * COLLECTIBLE_ANIM_SPEED)
		game->collectible_anim_timer = 0;
}

int	get_collectible_sway_offset(t_game *game, int row, int col)
{
	int		phase;
	double	angle;
	int		offset;
	double	timer_ratio;

	phase = (row * 13 + col * 17) % 120;
	timer_ratio = game->collectible_anim_timer / (double)COLLECTIBLE_ANIM_SPEED;
	angle = (timer_ratio + phase) * 3.14159 / 60.0;
	offset = (int)(sin(angle) * COLLECTIBLE_SWAY_RANGE);
	return (offset);
}

void	redraw_collectible_area(t_game *game, int row, int col)
{
	void	*floor_img;
	void	*collectible_img;
	int		sway_offset;
	int		x;
	int		y;

	floor_img = get_floor_variant(game, row, col);
	x = col * TILE_SIZE;
	y = row * TILE_SIZE;
	mlx_put_image_to_window(game->mlx, game->win, floor_img,
		x - COLLECTIBLE_SWAY_RANGE, y);
	mlx_put_image_to_window(game->mlx, game->win, floor_img, x, y);
	mlx_put_image_to_window(game->mlx, game->win, floor_img,
		x + COLLECTIBLE_SWAY_RANGE, y);
	collectible_img = get_collectible_variant(game, row, col);
	sway_offset = get_collectible_sway_offset(game, row, col);
	x += sway_offset;
	mlx_put_image_to_window(game->mlx, game->win, collectible_img, x, y);
}

void	animate_all_collectibles(t_game *game)
{
	int	row;
	int	col;

	update_collectible_animation(game);
	row = 0;
	while (game->map[row])
	{
		col = 0;
		while (game->map[row][col])
		{
			if (game->map[row][col] == 'C')
				redraw_collectible_area(game, row, col);
			col++;
		}
		row++;
	}
	usleep(ANIMATION_DELAY);
} 
