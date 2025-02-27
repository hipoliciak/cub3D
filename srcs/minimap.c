/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 13:12:58 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/27 17:06:52 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_tile(t_game *game, int screen_x, int screen_y, int color)
{
	int	dx;
	int	dy;
	int	pixel_x;
	int	pixel_y;

	dy = 0;
	while (dy < MINIMAP_TILE_SIZE)
	{
		dx = 0;
		while (dx < MINIMAP_TILE_SIZE)
		{
			pixel_x = screen_x + dx;
			pixel_y = screen_y + dy;
			if (pixel_x >= 0 && pixel_x < game->win_width
				&& pixel_y >= 0 && pixel_y < game->win_height)
				game->frame.addr[pixel_y * game->win_width + pixel_x]
					= color;
			dx++;
		}
		dy++;
	}
}

int	get_tile_color(char tile)
{
	if (tile == '1')
		return (MINIMAP_WALL_COLOR);
	else if (tile == '0')
		return (MINIMAP_FLOOR_COLOR);
	else if (tile == 'P')
		return (MINIMAP_PLAYER_COLOR);
	return (-1);
}

void	render_minimap(t_game *game)
{
	int	x;
	int	y;
	int	screen_x;
	int	screen_y;
	int	color;

	y = 0;
	while (game->file.map[y])
	{
		x = 0;
		while (game->file.map[y][x] != '\0')
		{
			screen_x = x * MINIMAP_TILE_SIZE + MINIMAP_TILE_SIZE;
			screen_y = (y + 1) * MINIMAP_TILE_SIZE;
			color = get_tile_color(game->file.map[y][x]);
			if (color == -1)
			{
				x++;
				continue ;
			}
			draw_tile(game, screen_x, screen_y, color);
			x++;
		}
		y++;
	}
}
