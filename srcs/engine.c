/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:19:33 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/11/03 00:02:03 by dmodrzej         ###   ########.fr       */
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

// void cast_rays(t_game *game)
// {
//     int x;
//     double camera_x;
//     double ray_dir_x, ray_dir_y;
//     double perp_wall_dist;
//     int line_height;
//     int draw_start, draw_end;

//     for (x = 0; x < WIN_WIDTH; x++)
//     {
//         camera_x = 2 * x / (double)WIN_WIDTH - 1;
//         ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
//         ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;

//         perp_wall_dist = calculate_distance(game, ray_dir_x, ray_dir_y);
//         line_height = (int)(WIN_HEIGHT / perp_wall_dist);
//         draw_start = -line_height / 2 + WIN_HEIGHT / 2;
//         draw_end = line_height / 2 + WIN_HEIGHT / 2;

//         draw_vertical_slice(game, x, draw_start, draw_end);
//     }
// }