#include "../includes/so_long.h"
#include "../mlx/mlx.h"

void	load_images(t_game *game)
{
	int	size;

	size = TILE_SIZE;
	load_basic_images(game, size);
	load_floor_images(game, size);
	load_wall_images(game, size);
	load_decoration_images(game, size);
	load_collectible_images(game, size);
	load_player_animation_images(game, size);
	load_enemy_images(game, size);
	load_corner_images(game, size);
	load_edge_images(game, size);
	set_corner_fallbacks(game);
	set_edge_fallbacks(game);
	set_collectible_fallbacks(game);
	set_player_animation_fallbacks(game);
	init_player_animation(game);
} 
 
