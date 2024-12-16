/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:08:28 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/15 18:41:18 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_texture_img(t_game *game, t_image *image, char *path)
{
	init_img_clean(image);
	image->img = mlx_xpm_file_to_image(game->mlx, path, &game->texture.size,
			&game->texture.size);
	if (image->img == NULL)
		clean_exit(game, err("Could not create image", 1));
	image->addr = (int *)mlx_get_data_addr(image->img, &image->pixel_bits,
			&image->size_line, &image->endian);
	return ;
}

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		clean_exit(game, err("Could not initialize mlx", 1));
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (!game->win)
		clean_exit(game, err("Could not create window", 1));
	return ;
}
