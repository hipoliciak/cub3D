/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:19:33 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/11/02 02:03:59 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_tile_position(t_game *game)
{
	int	new_tile_x;
	int	new_tile_y;

	new_tile_x = (int)game->player.x;
	new_tile_y = (int)game->player.y;
	if (new_tile_x != game->player.tile_x || new_tile_y != game->player.tile_y)
	{
		game->map.map[game->player.tile_y][game->player.tile_x] = '0';
		game->map.map[new_tile_y][new_tile_x] = 'P';
		game->player.tile_x = new_tile_x;
		game->player.tile_y = new_tile_y;
	}
}

void	move_forward(t_game *game)
{
	double	move_x;
	double	move_y;

	move_x = game->player.x + cos(game->player.angle * M_PI / 180) * MOVE_STEP;
	move_y = game->player.y + sin(game->player.angle * M_PI / 180) * MOVE_STEP;
	if (game->map.map[(int)move_y][(int)move_x] != '1')
	{
		game->player.x = move_x;
		game->player.y = move_y;
		update_tile_position(game);
	}
}

void	move_backward(t_game *game)
{
	double	move_x;
	double	move_y;

	move_x = game->player.x - cos(game->player.angle * M_PI / 180) * MOVE_STEP;
	move_y = game->player.y - sin(game->player.angle * M_PI / 180) * MOVE_STEP;
	if (game->map.map[(int)move_y][(int)move_x] != '1')
	{
		game->player.x = move_x;
		game->player.y = move_y;
		update_tile_position(game);
	}
}

void	rotate_left(t_game *game)
{
	game->player.angle -= 5.0;
	if (game->player.angle < 0.0)
		game->player.angle += 360.0;
}

void	rotate_right(t_game *game)
{
	game->player.angle += 5.0;
	if (game->player.angle >= 360.0)
		game->player.angle -= 360.0;
}
