/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_animation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhamad <mokhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 09:00:00 by mokhamad          #+#    #+#             */
/*   Updated: 2024/06/18 09:00:00 by mokhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	*get_exit_frame(t_game *game)
{
	if (game->exit_anim_frame == 0 && game->img_exit_1)
		return (game->img_exit_1);
	else if (game->exit_anim_frame == 1 && game->img_exit_2)
		return (game->img_exit_2);
	else if (game->exit_anim_frame == 2 && game->img_exit_3)
		return (game->img_exit_3);
	else if (game->exit_anim_frame == 3 && game->img_exit_4)
		return (game->img_exit_4);
	if (game->img_exit)
		return (game->img_exit);
	if (game->img_runway)
		return (game->img_runway);
	return (game->img_floor);
}

void	update_exit_animation(t_game *game)
{
	game->exit_anim_timer++;
	if (game->exit_anim_timer >= EXIT_ANIM_SPEED)
	{
		game->exit_anim_timer = 0;
		game->exit_anim_frame = (game->exit_anim_frame + 1) % 4;
	}
}

void	animate_exit(t_game *game)
{
	int	row;
	int	col;

	if (game->collectibles_left > 0)
		return ;
	update_exit_animation(game);
	row = 0;
	while (game->map[row])
	{
		col = 0;
		while (game->map[row][col])
		{
			if (game->map[row][col] == 'E')
			{
				render_enhanced_tile(game, row, col);
				return ;
			}
			col++;
		}
		row++;
	}
} 
