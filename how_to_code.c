/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   how_to_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42AI                                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 by 42AI                #+#    #+#             */
/*   Updated: 2024/06/10 by 42AI               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define TILE_SIZE 64
#define MAP_WIDTH 8
#define MAP_HEIGHT 6

// Key codes for WASD and ESC
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_ESC 65307

// Simple map: 1=wall, 0=floor, P=player, C=collectible, E=exit
char map[MAP_HEIGHT][MAP_WIDTH + 1] = {
    "11111111",
    "1P0000C1",
    "10000001",
    "1C0000E1",
    "10000001",
    "11111111"
};

typedef struct s_game {
	void *mlx;
	void *win;
	void *img_wall;
	void *img_floor;
	void *img_player;
	void *img_collect;
	void *img_exit;
	int player_x;
	int player_y;
	int moves;
} t_game;

// Create a solid color image
void *create_color_img(void *mlx, int color) {
	int bpp, size_line, endian;
	void *img = mlx_new_image(mlx, TILE_SIZE, TILE_SIZE);
	if (!img) {
		fprintf(stderr, "mlx_new_image failed\n");
		exit(1);
	}
	int *data = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);
	if (!data) {
		fprintf(stderr, "mlx_get_data_addr failed\n");
		exit(1);
	}
	for (int y = 0; y < TILE_SIZE; y++) {
		for (int x = 0; x < TILE_SIZE; x++) {
			data[y * (size_line / 4) + x] = color;
		}
	}
	return img;
}

void render_map(t_game *game) {
	int x, y;
	for (y = 0; y < MAP_HEIGHT; y++) {
		for (x = 0; x < MAP_WIDTH; x++) {
			void *img = NULL;
			if (map[y][x] == '1')
				img = game->img_wall;
			else if (map[y][x] == '0')
				img = game->img_floor;
			else if (map[y][x] == 'P')
				img = game->img_player;
			else if (map[y][x] == 'C')
				img = game->img_collect;
			else if (map[y][x] == 'E')
				img = game->img_exit;
			if (img)
				mlx_put_image_to_window(game->mlx, game->win, img, x * TILE_SIZE, y * TILE_SIZE);
		}
	}
}

void find_player(t_game *game) {
	int x, y;
	for (y = 0; y < MAP_HEIGHT; y++) {
		for (x = 0; x < MAP_WIDTH; x++) {
			if (map[y][x] == 'P') {
				game->player_x = x;
				game->player_y = y;
				return;
			}
		}
	}
}

void cleanup_images(t_game *game) {
	if (game->img_wall)
		mlx_destroy_image(game->mlx, game->img_wall);
	if (game->img_floor)
		mlx_destroy_image(game->mlx, game->img_floor);
	if (game->img_player)
		mlx_destroy_image(game->mlx, game->img_player);
	if (game->img_collect)
		mlx_destroy_image(game->mlx, game->img_collect);
	if (game->img_exit)
		mlx_destroy_image(game->mlx, game->img_exit);
}

// Count remaining collectibles
int count_collectibles(void) {
	int x, y, count = 0;
	for (y = 0; y < MAP_HEIGHT; y++) {
		for (x = 0; x < MAP_WIDTH; x++) {
			if (map[y][x] == 'C')
				count++;
		}
	}
	return count;
}

int handle_key(int keycode, t_game *game) {
	int nx = game->player_x;
	int ny = game->player_y;
	if (keycode == KEY_ESC) {
		cleanup_images(game);
		exit(0);
	}
	else if (keycode == KEY_W)
		ny--;
	else if (keycode == KEY_S)
		ny++;
	else if (keycode == KEY_A)
		nx--;
	else if (keycode == KEY_D)
		nx++;
	// Bounds check
	if (nx < 0 || nx >= MAP_WIDTH || ny < 0 || ny >= MAP_HEIGHT)
		return (0);
	if (map[ny][nx] == '1')
		return (0); // Wall, can't move
	if (map[ny][nx] == 'E') {
		if (count_collectibles() == 0) {
			printf("You win!\n");
			cleanup_images(game);
			exit(0);
		} else {
			printf("Collect all collectibles first!\n");
			return (0);
		}
	}
	if (map[ny][nx] == 'C')
		map[ny][nx] = '0'; // Collectible picked up
	map[game->player_y][game->player_x] = '0';
	game->player_x = nx;
	game->player_y = ny;
	map[ny][nx] = 'P';
	game->moves++;
	printf("Moves: %d\n", game->moves);
	render_map(game);
	return (0);
}

int main() {
	t_game game;
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE, "Mini so_long");
	game.img_wall = create_color_img(game.mlx, 0x333333);
	game.img_floor = create_color_img(game.mlx, 0xAAAAAA);
	game.img_player = create_color_img(game.mlx, 0x00FF00);
	game.img_collect = create_color_img(game.mlx, 0xFFFF00);
	game.img_exit = create_color_img(game.mlx, 0xFF0000);
	game.moves = 0;
	find_player(&game);
	render_map(&game);
	mlx_key_hook(game.win, handle_key, &game);
	mlx_loop(game.mlx);
	cleanup_images(&game); // In case loop ever returns
	return (0);
} 