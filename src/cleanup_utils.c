#include "../includes/so_long.h"
#include "../mlx/mlx.h"
#include "../mlx/mlx_int.h"
#include <X11/Xlib.h>
#include <X11/extensions/XShm.h>

void	cleanup_edge_images(t_game *game)
{
	if (game->img_wall_edge_top && game->mlx
		&& game->img_wall_edge_top != game->img_wall)
		mlx_destroy_image(game->mlx, game->img_wall_edge_top);
	if (game->img_wall_edge_bottom && game->mlx
		&& game->img_wall_edge_bottom != game->img_wall)
		mlx_destroy_image(game->mlx, game->img_wall_edge_bottom);
	if (game->img_wall_edge_left && game->mlx
		&& game->img_wall_edge_left != game->img_wall)
		mlx_destroy_image(game->mlx, game->img_wall_edge_left);
	if (game->img_wall_edge_right && game->mlx
		&& game->img_wall_edge_right != game->img_wall)
		mlx_destroy_image(game->mlx, game->img_wall_edge_right);
}

void	cleanup_images(t_game *game)
{
	if (!game->mlx)
		return ;
	cleanup_basic_images(game);
	cleanup_floor_images(game);
	cleanup_wall_images(game);
	cleanup_decoration_images(game);
	cleanup_collectible_images(game);
	cleanup_player_animation_images(game);
	cleanup_enemy_images(game);
	cleanup_corner_images(game);
	cleanup_edge_images(game);
}

void	force_x11_cleanup(t_xvar *xvar)
{
	if (!xvar || !xvar->display)
		return ;
	XFlush(xvar->display);
	XSync(xvar->display, True);
	if (xvar->private_cmap && xvar->cmap != DefaultColormap(xvar->display, xvar->screen))
		XFreeColormap(xvar->display, xvar->cmap);
	XCloseDisplay(xvar->display);
	xvar->display = NULL;
}

void	cleanup_mlx_resources(t_game *game)
{
	t_xvar	*xvar;

	if (!game->mlx)
		return ;
	xvar = (t_xvar *)game->mlx;
	mlx_do_sync(game->mlx);
	force_x11_cleanup(xvar);
	free(game->mlx);
	game->mlx = NULL;
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	cleanup_images(game);
	if (game->win && game->mlx)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	cleanup_mlx_resources(game);
	if (game->map)
	{
		free_map(game->map);
		game->map = NULL;
	}
} 
 
