/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:19:33 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/21 21:38:40 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	rc_right_qdr(t_game *game, double radians)
{
	double	h_inter;
	double	x_inter;

	x_inter = ceil((game->player.pos_x / TILE_SIZE) * TILE_SIZE);
	h_inter = game->player.pos_y + (x_inter - game->player.pos_x) * tan(radians);
	while (game->map.map[game->map.height - (int)h_inter
		- 1][(int)x_inter] == '0')
	{
		x_inter += 0.01;
		h_inter = game->player.pos_y + (x_inter - game->player.pos_x) * tan(radians);
	}
	return (sqrt((game->player.pos_y - h_inter) * (game->player.pos_y - h_inter)
			+ (game->player.pos_x - x_inter) * (game->player.pos_x - x_inter)));
}

double	rc_upper_qdr(t_game *game, double radians)
{
	double	h_inter;
	double	x_inter;

	h_inter = ceil((game->player.pos_y / TILE_SIZE) * TILE_SIZE);
	x_inter = game->player.pos_x + (h_inter - game->player.pos_y) / tan(radians);
	while (game->map.map[game->map.height - (int)h_inter
		- 1][(int)x_inter] == '0')
	{
		h_inter += 0.01;
		x_inter = game->player.pos_x + (h_inter - game->player.pos_y) / tan(radians);
	}
	return (sqrt((game->player.pos_y - h_inter) * (game->player.pos_y - h_inter)
			+ (game->player.pos_x - x_inter) * (game->player.pos_x - x_inter)));
}

double	rc_left_qdr(t_game *game, double radians)
{
	double	h_inter;
	double	x_inter;

	x_inter = floor((game->player.pos_x / TILE_SIZE) * TILE_SIZE);
	h_inter = game->player.pos_y + (x_inter - game->player.pos_x) * tan(radians);
	x_inter -= 0.1;
	while (game->map.map[game->map.height - (int)h_inter
		- 1][(int)x_inter] == '0')
	{
		x_inter -= 0.1;
		h_inter = game->player.pos_y + (x_inter - game->player.pos_x) * tan(radians);
	}
	return (sqrt((game->player.pos_y - h_inter) * (game->player.pos_y - h_inter)
			+ (game->player.pos_x - x_inter) * (game->player.pos_x - x_inter)));
}

double	rc_bottom_qdr(t_game *game, double radians)
{
	double	h_inter;
	double	x_inter;

	h_inter = floor((game->player.pos_y / TILE_SIZE) * TILE_SIZE);
	x_inter = game->player.pos_x + (h_inter - game->player.pos_y) / tan(radians);
	h_inter -= 0.1; // later swith to 0.01
	while (game->map.map[game->map.height - (int)h_inter
		- 1][(int)x_inter] == '0')
	{
		h_inter -= 0.01; 
		x_inter = game->player.pos_x + (h_inter - game->player.pos_y) / tan(radians);
	}
	return (sqrt((game->player.pos_y - h_inter) * (game->player.pos_y - h_inter)
			+ (game->player.pos_x - x_inter) * (game->player.pos_x - x_inter)));
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
