/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:08:36 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/15 18:39:21 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	*xpm_to_img(t_game *game, char *path)
{
	t_image	tmp;
	int		*buffer;
	int		x;
	int		y;

	init_texture_img(game, &tmp, path);
	buffer = ft_calloc(1, sizeof * buffer * game->texture.size
			* game->texture.size);
	if (!buffer)
		clean_exit(game, err("Could not allocate memory", 1));
	y = 0;
	while (y < game->texture.size)
	{
		x = 0;
		while (x < game->texture.size)
		{
			buffer[y * game->texture.size + x]
				= tmp.addr[y * game->texture.size + x];
			++x;
		}
		y++;
	}
	mlx_destroy_image(game->mlx, tmp.img);
	return (buffer);
}

void	init_textures(t_game *game)
{
	game->textures = malloc(sizeof(int *) * 4);
	if (!game->textures)
		clean_exit(game, err("Could not allocate memory", 1));
	game->textures[0] = xpm_to_img(game, game->texture.north);
	game->textures[1] = xpm_to_img(game, game->texture.south);
	game->textures[2] = xpm_to_img(game, game->texture.east);
	game->textures[3] = xpm_to_img(game, game->texture.west);
}

void	init_tex(t_tex *textures)
{
	textures->north = NULL;
	textures->south = NULL;
	textures->west = NULL;
	textures->east = NULL;
	textures->floor = 0;
	textures->ceiling = 0;
	textures->hex_floor = 0x0;
	textures->hex_ceiling = 0x0;
	textures->size = TEX_SIZE;
}
