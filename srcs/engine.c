/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotr <piotr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:19:33 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/15 16:34:24 by piotr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	rc_right_qdr(t_game *game, double radians)
{
	double	h_inter;
	double	x_inter;

	x_inter = ceil((game->player.x / TILE_SIZE) * TILE_SIZE);
	h_inter = game->player.y + (x_inter - game->player.x) * tan(radians);
	while (game->map.map[game->map.height - (int)h_inter
		- 1][(int)x_inter] == '0')
	{
		x_inter += 0.01;
		h_inter = game->player.y + (x_inter - game->player.x) * tan(radians);
	}
	return (sqrt((game->player.y - h_inter) * (game->player.y - h_inter)
			+ (game->player.x - x_inter) * (game->player.x - x_inter)));
}

double	rc_upper_qdr(t_game *game, double radians)
{
	double	h_inter;
	double	x_inter;

	h_inter = ceil((game->player.y / TILE_SIZE) * TILE_SIZE);
	x_inter = game->player.x + (h_inter - game->player.y) / tan(radians);
	while (game->map.map[game->map.height - (int)h_inter
		- 1][(int)x_inter] == '0')
	{
		h_inter += 0.01;
		x_inter = game->player.x + (h_inter - game->player.y) / tan(radians);
	}
	return (sqrt((game->player.y - h_inter) * (game->player.y - h_inter)
			+ (game->player.x - x_inter) * (game->player.x - x_inter)));
}

double	rc_left_qdr(t_game *game, double radians)
{
	double	h_inter;
	double	x_inter;

	x_inter = floor((game->player.x / TILE_SIZE) * TILE_SIZE);
	h_inter = game->player.y + (x_inter - game->player.x) * tan(radians);
	x_inter -= 0.1;
	while (game->map.map[game->map.height - (int)h_inter
		- 1][(int)x_inter] == '0')
	{
		x_inter -= 0.1;
		h_inter = game->player.y + (x_inter - game->player.x) * tan(radians);
	}
	return (sqrt((game->player.y - h_inter) * (game->player.y - h_inter)
			+ (game->player.x - x_inter) * (game->player.x - x_inter)));
}

double	rc_bottom_qdr(t_game *game, double radians)
{
	double	h_inter;
	double	x_inter;

	h_inter = floor((game->player.y / TILE_SIZE) * TILE_SIZE);
	x_inter = game->player.x + (h_inter - game->player.y) / tan(radians);
	h_inter -= 0.1; // later swith to 0.01
	while (game->map.map[game->map.height - (int)h_inter
		- 1][(int)x_inter] == '0')
	{
		h_inter -= 0.01; 
		x_inter = game->player.x + (h_inter - game->player.y) / tan(radians);
	}
	return (sqrt((game->player.y - h_inter) * (game->player.y - h_inter)
			+ (game->player.x - x_inter) * (game->player.x - x_inter)));
}

void	cast_rays(t_game *game)
{
	int i;
	double	radians;
	double	ray_angle;
	double	ray_len;

	i = 0;
	while(i < FOV)
	{
		ray_angle = fmod(((game->player.angle - FOV / 2 + i) + 360), 360);
		radians = (ray_angle - 1) * (M_PI / 180);
		if ((ray_angle) <= 45 || (ray_angle) > 315)
			ray_len = rc_right_qdr(game, radians);
		else if ((ray_angle) <= 135)
			ray_len = rc_upper_qdr(game, radians);
		else if ((ray_angle) <= 225)
			ray_len = rc_left_qdr(game, radians);
		else if ((ray_angle) <= 315)
			ray_len = rc_bottom_qdr(game, radians);
		game->player.rays_len[i] = ray_len;
		printf("actual ray angle: %lf\n", ray_angle);
		printf("ray_len: %lf\n", game->player.rays_len[i]);
		i++;
	}

	// printf("Player angle: %f\n", game->player.angle);
	// printf("actual ray radians: %lf\n", radians);
}

void	update_tile_position(t_game *game)
{
	int	new_tile_x;
	int	new_tile_y;

	new_tile_x = (int)game->player.x;
	new_tile_y = (int)game->player.y;
	if (new_tile_x != game->player.tile_x || new_tile_y != game->player.tile_y)
	{
		game->map.map[game->map.height - game->player.tile_y
			- 1][game->player.tile_x] = '0';
		game->map.map[game->map.height - new_tile_y - 1][new_tile_x] = 'P';
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
	if (game->map.map[game->map.height - 1 - (int)move_y][(int)move_x] != '1')
	{
		game->player.x = move_x;
		game->player.y = move_y;
		update_tile_position(game);
	}
	cast_rays(game);
}

void	move_backward(t_game *game)
{
	double	move_x;
	double	move_y;

	move_x = game->player.x - cos(game->player.angle * M_PI / 180) * MOVE_STEP;
	move_y = game->player.y - sin(game->player.angle * M_PI / 180) * MOVE_STEP;
	if (game->map.map[game->map.height - 1 - (int)move_y][(int)move_x] != '1')
	{
		game->player.x = move_x;
		game->player.y = move_y;
		update_tile_position(game);
	}
	cast_rays(game);
}

void	rotate_right(t_game *game)
{
	game->player.angle -= 1.0;
	if (game->player.angle < 0.0)
		game->player.angle += 360.0;
	cast_rays(game);
}

void	rotate_left(t_game *game)
{
	game->player.angle += 1.0;
	if (game->player.angle >= 360.0)
		game->player.angle -= 360.0;
	cast_rays(game);
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