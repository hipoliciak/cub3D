/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:08:15 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/22 17:30:14 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_image(t_image *image)
{
	image->img = NULL;
	image->addr = NULL;
	image->pixel_bits = 0;
	image->size_line = 0;
	image->endian = 0;
}

void	init_player(t_player *player)
{
	player->dir = '\0';
	player->pos_x = 0.0;
	player->pos_y = 0.0;
	player->dir_x = 0.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.0;
	player->key_state[0] = 0;
	player->key_state[1] = 0;
	player->key_state[2] = 0;
	player->key_state[3] = 0;
	player->key_state[4] = 0;
	player->key_state[5] = 0;
}

void	init_texdata(t_texdata *texdata)
{
	texdata->north_path = NULL;
	texdata->south_path = NULL;
	texdata->west_path = NULL;
	texdata->east_path = NULL;
	texdata->rgb_floor = 0;
	texdata->rgb_ceiling = 0;
	texdata->texture_width = TEX_WIDTH;
	texdata->texture_height = TEX_HEIGHT;
}

void	init_map(t_map *map)
{
	map->fd = 0;
	map->map = NULL;
	map->height = 0;
	map->width = 0;
	map->end_of_map = 0;
	map->start_of_map = 0;
}

void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->win_height = WIN_HEIGHT;
	game->win_width = WIN_WIDTH;
	init_map(&game->map);
	init_player(&game->player);
	game->player_count = 0;
	game->north_texture = NULL;
	game->south_texture = NULL;
	game->west_texture = NULL;
	game->east_texture = NULL;
	game->hex_floor = 0x0;
	game->hex_ceiling = 0x0;
	init_texdata(&game->texdata);
}
