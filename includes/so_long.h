#ifndef SO_LONG_H
# define SO_LONG_H

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

# define MAX_MAP_HEIGHT 1000
# define TILE_SIZE 64

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_Q 113
# define KEY_ESC 65307
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# define ANIM_LEFT 0
# define ANIM_RIGHT 1
# define ANIM_UP 2
# define ANIM_DOWN 3
# define ANIM_FRAMES 4

# define COLLECTIBLE_ANIM_SPEED 10
# define COLLECTIBLE_SWAY_RANGE 3
# define EXIT_ANIM_SPEED 1000
# define ANIMATION_DELAY 0

# define ENEMY_STATIC 0
# define ENEMY_PATROL 1
# define MAX_ENEMIES 50
# define PATROL_SPEED_MS 800

typedef struct s_enemy
{
	int				x;
	int				y;
	int				prev_x;
	int				prev_y;
	int				type;
	int				direction;
	int				anim_frame;
	int				patrol_start;
	int				patrol_end;
	struct timeval	last_move_time;
}	t_enemy;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	void	*img_wall;
	void	*img_floor;
	void	*img_player;
	void	*img_player_left_1;
	void	*img_player_left_2;
	void	*img_player_left_3;
	void	*img_player_left_4;
	void	*img_player_right_1;
	void	*img_player_right_2;
	void	*img_player_right_3;
	void	*img_player_right_4;
	void	*img_player_up_1;
	void	*img_player_up_2;
	void	*img_player_up_3;
	void	*img_player_up_4;
	void	*img_player_down_1;
	void	*img_player_down_2;
	void	*img_player_down_3;
	void	*img_player_down_4;
	void	*img_collect;
	void	*img_collect_radio;
	void	*img_collect_helmet;
	void	*img_collect_map;
	void	*img_collect_ammo;
	void	*img_collect_flag;
	void	*img_collect_cedar;
	void	*img_exit;
	void	*img_runway;
	void	*img_exit_1;
	void	*img_exit_2;
	void	*img_exit_3;
	void	*img_exit_4;
	void	*img_floor_1;
	void	*img_floor_2;
	void	*img_floor_3;
	void	*img_wall_1;
	void	*img_wall_2;
	void	*img_wall_3;
	void	*img_cedar_tree;
	void	*img_lebanese_flag;
	void	*img_ammo_crate;
	void	*img_wall_corner_top_left;
	void	*img_wall_corner_top_right;
	void	*img_wall_corner_bottom_left;
	void	*img_wall_corner_bottom_right;
	void	*img_wall_edge_top;
	void	*img_wall_edge_bottom;
	void	*img_wall_edge_left;
	void	*img_wall_edge_right;
	void	*img_terrorist;
	void	*img_terrorist_left_1;
	void	*img_terrorist_left_2;
	void	*img_terrorist_left_3;
	void	*img_terrorist_right_1;
	void	*img_terrorist_right_2;
	void	*img_terrorist_right_3;
	char	**map;
	int		rows;
	int		cols;
	int		move_count;
	int		collectibles_left;
	int		anim_frame;
	int		anim_direction;
	int		collectible_anim_timer;
	int		exit_anim_timer;
	int		exit_anim_frame;
	t_enemy	enemies[MAX_ENEMIES];
	int		enemy_count;
}	t_game;

/* Map loading */
char	**read_map(char *filename);
void	free_map(char **map);

/* Map validation */
int		validate_map(char **map);
int		check_borders(char **map, int rows, int cols);
int		count_chars(char **map, int *p, int *e, int *c);
int		is_valid_char(char c);
int		check_map_dimensions(char **map);

/* Flood fill */
void	find_player(char **map, int *x, int *y);
char	**copy_map(char **map);
void	flood_fill(char **map, int y, int x);
int		check_path(char **map);
int		is_path_valid(char **map);

/* Game functions */
void	init_game(t_game *game, char **map);
void	load_images(t_game *game);
void	render_map(t_game *game);
void	render_tile(t_game *game, int row, int col);
int		count_collectibles(char **map);

/* Render utilities */
void	*get_floor_variant(t_game *game, int row, int col);
void	*get_wall_variant(t_game *game, int row, int col);
void	*get_collectible_variant(t_game *game, int row, int col);
int		is_border_wall(t_game *game, int row, int col);
void	*get_corner_tile(t_game *game, int row, int col);
void	*get_edge_tile(t_game *game, int row, int col);
void	*get_border_wall_tile(t_game *game, int row, int col);
void	*get_decoration(t_game *game, int row, int col);
int		should_add_decoration(int row, int col);
void	render_floor_and_decorations(t_game *game, int row, int col);
void	render_wall_tile(t_game *game, int row, int col);
void	render_game_objects(t_game *game, int row, int col);
void	render_enhanced_tile(t_game *game, int row, int col);
void	put_tile(t_game *game, void *img, int row, int col);

/* Player functions */
void	find_player_pos(char **map, int *x, int *y);
void	handle_collectible(t_game *game);
int		check_exit(t_game *game);
void	update_player_position(t_game *game, int new_y, int new_x);
void	move_player(t_game *game, int new_y, int new_x);
int		handle_key(int keycode, t_game *game);
int		close_game(t_game *game);

/* Cleanup functions */
void	cleanup_images(t_game *game);
void	cleanup_game(t_game *game);
void	cleanup_basic_images(t_game *game);
void	cleanup_floor_images(t_game *game);
void	cleanup_wall_images(t_game *game);
void	cleanup_decoration_images(t_game *game);
void	cleanup_collectible_images(t_game *game);
void	cleanup_corner_images(t_game *game);
void	cleanup_edge_images(t_game *game);

/* Asset loading functions */
void	load_basic_images(t_game *game, int size);
void	load_floor_images(t_game *game, int size);
void	load_wall_images(t_game *game, int size);
void	load_decoration_images(t_game *game, int size);
void	load_collectible_images(t_game *game, int size);
void	load_player_animation_images(t_game *game, int size);
void	load_corner_images(t_game *game, int size);
void	load_edge_images(t_game *game, int size);
void	set_corner_fallbacks(t_game *game);
void	set_edge_fallbacks(t_game *game);
void	set_collectible_fallbacks(t_game *game);
void	set_player_animation_fallbacks(t_game *game);

/* Player animation functions */
void	*get_current_player_sprite(t_game *game);
void	*get_left_animation_frame(t_game *game);
void	*get_right_animation_frame(t_game *game);
void	*get_up_animation_frame(t_game *game);
void	*get_down_animation_frame(t_game *game);
void	init_player_animation(t_game *game);
void	update_player_animation(t_game *game, int direction);
void	cleanup_player_animation_images(t_game *game);
void	cleanup_left_animation_images(t_game *game);
void	cleanup_right_animation_images(t_game *game);
void	cleanup_up_animation_images(t_game *game);
void	cleanup_down_animation_images(t_game *game);

/* Collectible animation functions */
void	init_collectible_animation(t_game *game);
void	update_collectible_animation(t_game *game);
int		get_collectible_sway_offset(t_game *game, int row, int col);
void	redraw_collectible_area(t_game *game, int row, int col);
void	animate_all_collectibles(t_game *game);

/* UI rendering functions */
void	render_ui_shadow(t_game *game);
void	render_ui_border(t_game *game);
void	render_ui_background(t_game *game);
void	render_move_count(t_game *game);
void	render_collectibles_count(t_game *game);
void	render_ui_stats(t_game *game);

/* Enemy functions */
void	load_enemy_images(t_game *game, int size);
void	init_enemies(t_game *game);
void	init_patrol_enemy(t_game *game, int row, int col);
void	init_static_enemy(t_game *game, int row, int col);
void	process_enemy_tile(t_game *game, int row, int col);
void	update_enemies(t_game *game);
void	update_patrol_enemy_with_collision(t_game *game, t_enemy *enemy);
int		enemy_can_move_to(t_game *game, int x, int y);
long	get_time_diff_ms(struct timeval *start, struct timeval *end);
void	update_enemy_display(t_game *game);
void	render_enemies(t_game *game);
int		check_enemy_collision(t_game *game, int x, int y);
void	*get_enemy_sprite(t_game *game, t_enemy *enemy);
void	cleanup_enemy_images(t_game *game);
void	game_over(t_game *game);

void		ft_putstr_fd(char *s, int fd);
void		animate_collectibles(t_game *game);
void		*get_collectible_frame(t_game *game);
void		*get_exit_frame(t_game *game);
void		update_exit_animation(t_game *game);
void		animate_exit(t_game *game);

#endif
