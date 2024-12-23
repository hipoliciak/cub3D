/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:19:39 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/23 23:18:21 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_textures(t_game *game)
{
	game->north_texture = load_texture(game, game->texdata.north_path);
	game->south_texture = load_texture(game, game->texdata.south_path);
	game->west_texture = load_texture(game, game->texdata.west_path);
	game->east_texture = load_texture(game, game->texdata.east_path);
	game->hex_ceiling = convert_rgb_to_hex(game->texdata.rgb_ceiling);
	game->hex_floor = convert_rgb_to_hex(game->texdata.rgb_floor);
}

int	*load_texture(t_game *game, char *path)
{
	t_image	tmp;
	int		*buffer;

	init_image(&tmp);
	tmp.img = mlx_xpm_file_to_image(game->mlx_ptr, path,
			&game->texdata.texture_width, &game->texdata.texture_height);
	if (!tmp.img)
		clean_exit(game, err("Could not create image", 1));
	tmp.addr = (int *)mlx_get_data_addr(tmp.img, &tmp.pixel_bits,
			&tmp.size_line, &tmp.endian);
	buffer = copy_texture_to_buffer(game, &tmp);
	mlx_destroy_image(game->mlx_ptr, tmp.img);
	return (buffer);
}

int	*copy_texture_to_buffer(t_game *game, t_image *img)
{
	int		*buffer;
	int		x;
	int		y;
	int		width;
	int		height;

	width = game->texdata.texture_width;
	height = game->texdata.texture_height;
	buffer = malloc(sizeof(int) * width * height);
	if (!buffer)
		clean_exit(game, err("Could not allocate memory", 1));
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			buffer[y * width + x] = img->addr[y * width + x];
			x++;
		}
		y++;
	}
	return (buffer);
}

unsigned long	convert_rgb_to_hex(int *rgb)
{
	int	r;
	int	g;
	int	b;

	if (!rgb)
		return (err("Could not convert RGB to hex", 0));
	r = rgb[0] & 0xff;
	g = rgb[1] & 0xff;
	b = rgb[2] & 0xff;
	return ((r << 16) | (g << 8) | b);
}
