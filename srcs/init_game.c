/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:08:15 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/27 19:14:55 by dmodrzej         ###   ########.fr       */
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

void	init_file(t_file *file)
{
	file->file = NULL;
	file->map = NULL;
	file->map_start = 0;
	file->map_height = 0;
	file->player_count = 0;
	file->north_path = NULL;
	file->south_path = NULL;
	file->west_path = NULL;
	file->east_path = NULL;
	file->rgb_floor = 0;
	file->rgb_ceiling = 0;
}

void	init_game(t_game *game)
{
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->win_width = WIN_WIDTH;
	game->win_height = WIN_HEIGHT;
	init_file(&game->file);
	init_player(&game->player);
	game->texture_width = TEX_WIDTH;
	game->texture_height = TEX_HEIGHT;
	game->north_texture = NULL;
	game->south_texture = NULL;
	game->west_texture = NULL;
	game->east_texture = NULL;
	game->hex_floor = 0x0;
	game->hex_ceiling = 0x0;
	init_image(&game->frame);
}
