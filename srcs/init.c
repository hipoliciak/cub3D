/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotr <piotr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 02:03:28 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/11/19 17:11:19 by piotr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_angle(t_game *game, int x, int y)
{
	if (game->map.map[y][x] == 'N')
		game->player.angle = 90.0;
	else if (game->map.map[y][x] == 'E')
		game->player.angle = 0.0;
	else if (game->map.map[y][x] == 'W')
		game->player.angle = 180.0;
	else if (game->map.map[y][x] == 'S')
		game->player.angle = 270.0;
}

void	init_positions(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (game->map.map[y])
	{
		x = 0;
		while (game->map.map[y][x])
		{
			if (game->map.map[y][x] == 'N' || game->map.map[y][x] == 'E' ||
				game->map.map[y][x] == 'W' || game->map.map[y][x] == 'S')
			{
				game->player.x = x + 0.5;
				game->player.y = game->map.height - y - 1 + 0.5;
				game->player.tile_x = x;
				game->player.tile_y = game->map.height - y - 1;
				init_angle(game, x, y);
				game->map.map[y][x] = 'P';
				cast_rays(game);
				return ;
			}
			x++;
		}
		y++;
	}
}

void	init_game(t_game *game)
{
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->map.map = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->player.x = 0;
	game->player.y = 0;
	game->player.angle = 0;
	game->player.tile_x = 0;
	game->player.tile_y = 0;
}
