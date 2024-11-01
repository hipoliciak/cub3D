/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:19:33 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/11/01 22:21:02 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_positions(t_game *game)
{
	int x;
	int y;

	x = 0;
	while (x < game->map.width)
	{
		y = 0;
		while (y < game->map.height)
		{
			if (game->map.map[y][x] == 'N' || game->map.map[y][x] == 'E' ||
				game->map.map[y][x] == 'W' || game->map.map[y][x] == 'S')
			{
				
				game->player.x = x + 0.5;
				game->player.y = y + 0.5;
				if (game->map.map[y][x] == 'N')
					game->player.angle = 0.0;
				else if (game->map.map[y][x] == 'E')
					game->player.angle = 90.0;
				else if (game->map.map[y][x] == 'W')
					game->player.angle = 270.0;
				else if (game->map.map[y][x] == 'S')
					game->player.angle = 180.0;
				return ;
			}
			y++;
		}
		x++;
	}
}

void move_forward(t_game *game)
{
	double move_x;
	double move_y;

	move_x = game->player.x + cos(game->player.angle * M_PI / 180) * MOVE_STEP;
	move_y = game->player.y + sin(game->player.angle * M_PI / 180) * MOVE_STEP;
	if (game->map.map[(int)move_y][(int)move_x] != '1')
	{
		game->player.x = move_x;
		game->player.y = move_y;
	}
}

void move_backward(t_game *game)
{
	double move_x;
	double move_y;

	move_x = game->player.x - cos(game->player.angle * M_PI / 180) * MOVE_STEP;
	move_y = game->player.y - sin(game->player.angle * M_PI / 180) * MOVE_STEP;

	if (game->map.map[(int)move_y][(int)move_x] != '1')
	{
		game->player.x = move_x;
		game->player.y = move_y;
	}
}

void rotate_left(t_game *game)
{
	game->player.angle -= 5.0;
	if (game->player.angle < 0.0)
		game->player.angle += 360.0;
}

void rotate_right(t_game *game)
{
	game->player.angle += 5.0;
	if (game->player.angle >= 360.0)
		game->player.angle -= 360.0;
}
