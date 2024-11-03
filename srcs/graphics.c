/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:19:39 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/11/02 22:29:36 by dmodrzej         ###   ########.fr       */
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

// void draw_vertical_slice(t_game *game, int x, int draw_start, int draw_end)
// {
//     int y;
//     int texture_x;
//     int texture_y;
//     int color;

//     for (y = draw_start; y < draw_end; y++)
//     {
//         texture_x = (int)((x / (double)WIN_WIDTH) * TEXTURE_SIZE) % TEXTURE_SIZE;
//         texture_y = ((y * 256 - WIN_HEIGHT * 128 + (draw_end - draw_start) * 128) * TEXTURE_SIZE / (draw_end - draw_start)) / 256;
//         color = get_texture_pixel(&game->textures[select_texture(game)], texture_x, texture_y);
//         put_pixel(game, x, y, color);
//     }
// }

// void put_pixel(t_game *game, int x, int y, int color)
// {
//     if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
//         game->image.data[y * WIN_WIDTH + x] = color;
// }

// void draw_floor_and_ceiling(t_game *game)
// {
//     int x, y;
//     for (y = 0; y < WIN_HEIGHT / 2; y++)
//         for (x = 0; x < WIN_WIDTH; x++)
//             put_pixel(game, x, y, game->ceiling_color);

//     for (y = WIN_HEIGHT / 2; y < WIN_HEIGHT; y++)
//         for (x = 0; x < WIN_WIDTH; x++)
//             put_pixel(game, x, y, game->floor_color);
// }

// double calculate_distance(double ray_dir_x, double ray_dir_y, double side_dist_x, double side_dist_y, int side)
// {
//     if (side == 0)  // Wall hit on x-axis
//         return (side_dist_x - ray_dir_x);
//     else            // Wall hit on y-axis
//         return (side_dist_y - ray_dir_y);
// }

// int select_texture(int side, double ray_dir_x, double ray_dir_y)
// {
//     if (side == 0)
//     {
//         if (ray_dir_x > 0)  // Wall hit from the west
//             return 2;       // Use west texture
//         else                // Wall hit from the east
//             return 3;       // Use east texture
//     }
//     else
//     {
//         if (ray_dir_y > 0)  // Wall hit from the north
//             return 0;       // Use north texture
//         else                // Wall hit from the south
//             return 1;       // Use south texture
//     }
// }

// int get_texture_pixel(t_image *texture, int x, int y)
// {
//     if (x >= 0 && x < texture->width && y >= 0 && y < texture->height)
//         return texture->data[y * texture->width + x];
//     return 0;  // Return black if out of bounds
// }