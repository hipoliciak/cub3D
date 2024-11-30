/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotr <piotr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:19:33 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/11/30 21:05:39 by piotr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool wall_hit(t_game *game, int inter)
{
	return false;
}

void	cast_rays(t_game *game)
{
	// need current pos x and y
	// need angle 
	int i;
	int tile_size; // set to macro check if there is any
	double radians;
	double ray_angle;
	double h_inter;
	double x_inter;

	tile_size = 10;
	ray_angle = fmod(((game->player.angle - FOV / 2) + 360), 360);
	radians = (ray_angle) * (M_PI / 180);

	if((ray_angle) <= 45 || (ray_angle) > 315)
	{
		x_inter = ceil((game->player.x / tile_size) * tile_size);
		h_inter = game->player.y + (x_inter - game->player.x) * tan(radians);
	}
	else if((ray_angle) <= 135)
	{
		h_inter = ceil((game->player.y / tile_size) * tile_size);
		x_inter = game->player.x + (h_inter - game->player.y) / tan(radians);
		printf("what is the tile: %c\n", game->map.map[(int)h_inter][(int)x_inter]);
		while(game->map.map[(int)h_inter][(int)x_inter] == '0')
		{
			printf("intersection: x = %lf, h = %lf\n", x_inter, h_inter);
			h_inter++;
			x_inter = game->player.x + (h_inter - game->player.y) / tan(radians);
		}
			printf("after wall hit: x = %lf, h = %lf\n", x_inter, h_inter);

	}
	else if((ray_angle) <= 225)
	{
		x_inter = floor((game->player.x / tile_size) * tile_size);
		h_inter = game->player.y + (x_inter - game->player.x) * tan(radians);	
	}
	else if((ray_angle) <= 315)
	{
		h_inter = floor((game->player.y / tile_size) * tile_size);
		x_inter = game->player.x + (h_inter - game->player.y) / tan(radians);
	}
	i = 0;

	printf("actual ray angle: %lf\n", ray_angle);
	printf("Player angle: %f\n", game->player.angle);
	printf("actual ray radians: %lf\n", radians);
	// printf("actual inter position: x = %lf, h = %lf\n", x_inter, h_inter);

	// printf("player_angle: %lf, radians: %lf\n", game->player.angle, radians);
	// if inter.h && inter.x = wall(1) then ray.len = twierdzenie pitagorasa
}

void	update_tile_position(t_game *game)
{
	int	new_tile_x;
	int	new_tile_y;

	new_tile_x = (int)game->player.x;
	new_tile_y = (int)game->player.y;

	if (new_tile_x != game->player.tile_x || new_tile_y != game->player.tile_y)
	{
		game->map.map[game->map.height -  game->player.tile_y - 1][game->player.tile_x] = '0';
		game->map.map[game->map.height -  new_tile_y - 1][new_tile_x] = 'P';
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
	game->player.angle -= 5.0;
	if (game->player.angle < 0.0)
		game->player.angle += 360.0;
	cast_rays(game);
}

void	rotate_left(t_game *game)
{
	game->player.angle += 5.0;
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