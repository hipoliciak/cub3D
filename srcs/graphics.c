/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:19:39 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/11/01 22:33:14 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_textures(t_game *game)
{
	game->textures[0] = create_texture(game, NO); // North texture
	game->textures[1] = create_texture(game, SO); // South texture
	game->textures[2] = create_texture(game, WE); // West texture
	game->textures[3] = create_texture(game, EA); // East texture
}

t_image	create_texture(t_game *game, char *path)
{
	t_image	sprite;

	sprite.xpm_ptr = mlx_xpm_file_to_image(game->mlx_ptr, path,
			&sprite.x, &sprite.y);
	if (!sprite.xpm_ptr)
		end_game(game);
	return (sprite);
}

void	render_sprite(t_game *game, t_image *sprite, int line, int column)
{
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, sprite->xpm_ptr,
		column * TEXTURE_SIZE, line * TEXTURE_SIZE);
}