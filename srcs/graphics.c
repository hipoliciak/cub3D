/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:19:39 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/11/02 02:35:33 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_textures(t_game *game)
{
	game->textures[0] = create_texture(game, NO);
	game->textures[1] = create_texture(game, SO);
	game->textures[2] = create_texture(game, WE);
	game->textures[3] = create_texture(game, EA);
}

t_image	create_texture(t_game *game, char *path)
{
	t_image	texture;

	texture.xpm_ptr = mlx_xpm_file_to_image(game->mlx_ptr, path,
			&texture.x, &texture.y);
	if (!texture.xpm_ptr)
		end_game(game);
	return (texture);
}

void	render_texture(t_game *game, t_image *sprite, int line, int column)
{
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, sprite->xpm_ptr,
		column * TEXTURE_SIZE, line * TEXTURE_SIZE);
}
