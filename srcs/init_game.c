/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:08:15 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/26 23:04:16 by dmodrzej         ###   ########.fr       */
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

void	init_map(t_map *map)
{
	map->map = NULL;
	map->player_count = 0;
	map->north_path = NULL;
	map->south_path = NULL;
	map->west_path = NULL;
	map->east_path = NULL;
	map->rgb_floor = 0;
	map->rgb_ceiling = 0;
	map->start_of_map = 0;
	map->end_of_map = 0;
}

void	init_game(t_game *game)
{
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->win_width = WIN_WIDTH;
	game->win_height = WIN_HEIGHT;
	init_map(&game->map);
	init_player(&game->player);
	game->texture_width = TEX_WIDTH;
	game->texture_height = TEX_HEIGHT;
	game->north_texture = NULL;
	game->south_texture = NULL;
	game->west_texture = NULL;
	game->east_texture = NULL;
	game->hex_floor = 0x0;
	game->hex_ceiling = 0x0;
	init_image(&game->labirynth);
}
