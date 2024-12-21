/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 00:56:17 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/21 22:35:34 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// // Perform raycasting and render the scene
// void render_scene(t_game *game)
// {
//     int x;
//     double camera_x;
//     t_ray ray;

//     x = 0;
//     while (x < game->screen_width)
//     {
//         camera_x = 2 * x / (double)game->screen_width - 1;
//         ray.dir_x = game->player.dir_x + game->player.plane_x * camera_x;
//         ray.dir_y = game->player.dir_y + game->player.plane_y * camera_x;

//         ray.map_x = (int)game->player.pos_x;
//         ray.map_y = (int)game->player.pos_y;

//         ray.delta_dist_x = fabs(1 / ray.dir_x);
//         ray.delta_dist_y = fabs(1 / ray.dir_y);

//         if (ray.dir_x < 0)
//         {
//             ray.step_x = -1;
//             ray.side_dist_x = (game->player.pos_x - ray.map_x) * ray.delta_dist_x;
//         }
//         else
//         {
//             ray.step_x = 1;
//             ray.side_dist_x = (ray.map_x + 1.0 - game->player.pos_x) * ray.delta_dist_x;
//         }
//         if (ray.dir_y < 0)
//         {
//             ray.step_y = -1;
//             ray.side_dist_y = (game->player.pos_y - ray.map_y) * ray.delta_dist_y;
//         }
//         else
//         {
//             ray.step_y = 1;
//             ray.side_dist_y = (ray.map_y + 1.0 - game->player.pos_y) * ray.delta_dist_y;
//         }

//         while (game->map.map[ray.map_y][ray.map_x] == '0')
//         {
//             if (ray.side_dist_x < ray.side_dist_y)
//             {
//                 ray.side_dist_x += ray.delta_dist_x;
//                 ray.map_x += ray.step_x;
//                 ray.side = 0;
//             }
//             else
//             {
//                 ray.side_dist_y += ray.delta_dist_y;
//                 ray.map_y += ray.step_y;
//                 ray.side = 1;
//             }
//         }

//         if (ray.side == 0)
//         {
//             ray.perp_wall_dist = (ray.map_x - game->player.pos_x + (1 - ray.step_x) / 2) / ray.dir_x;
//             ray.wall_x = game->player.pos_y + ray.perp_wall_dist * ray.dir_y;
//         }
//         else
//         {
//             ray.perp_wall_dist = (ray.map_y - game->player.pos_y + (1 - ray.step_y) / 2) / ray.dir_y;
//             ray.wall_x = game->player.pos_x + ray.perp_wall_dist * ray.dir_x;
//         }
//         ray.wall_x -= floor(ray.wall_x);

//         ray.line_height = (int)(game->screen_height / ray.perp_wall_dist);
//         ray.draw_start = -ray.line_height / 2 + game->screen_height / 2;
//         ray.draw_end = ray.line_height / 2 + game->screen_height / 2;
//         if (ray.draw_start < 0) ray.draw_start = 0;
//         if (ray.draw_end >= game->screen_height) ray.draw_end = game->screen_height - 1;

//         int tex_x = (int)(ray.wall_x * (double)TEX_WIDTH);
//         if (ray.side == 0 && ray.dir_x > 0) tex_x = TEX_WIDTH - tex_x - 1;
//         if (ray.side == 1 && ray.dir_y < 0) tex_x = TEX_WIDTH - tex_x - 1;

//         render_column(game, x, ray.perp_wall_dist, tex_x);
//         x++;
//     }
// }

// void render_column(t_game *game, int x, double ray_dist, int tex_x)
// {
//     int y;
//     int wall_height = (int)(game->screen_height / ray_dist);
//     int draw_start = -wall_height / 2 + game->screen_height / 2;
//     int draw_end = wall_height / 2 + game->screen_height / 2;

//     double step = 1.0 * TEX_HEIGHT / wall_height;
//     double tex_pos = (draw_start - game->screen_height / 2 + wall_height / 2) * step;
//     if (draw_start < 0) draw_start = 0;
//     if (draw_end >= game->screen_height) draw_end = game->screen_height - 1;

//     y = draw_start;
//     while (y < draw_end)
//     {
//         int tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
//         tex_pos += step;
//         int color = game->textures[game->side][tex_y * TEX_WIDTH + tex_x];
//         game->image.addr[y * game->screen_width + x] = color;
//         y++;
//     }
// }

void	render_frame(t_game *game)
{
	t_image	image;
	int		x;
	int		y;

	init_image(&image);
	image.img = mlx_new_image(game->mlx, game->win_width, game->win_height);
	if (image.img == NULL)
		clean_exit(game, err("Could not create image", 1));
	image.addr = (int *)mlx_get_data_addr(image.img, &image.pixel_bits,
			&image.size_line, &image.endian);
	y = 0;
	while (y < game->win_height)
	{
		x = 0;
		while (x < game->win_width)
		{
			if (y < game->win_height / 2)
				image.addr[y * game->win_width + x] = game->texture.hex_ceiling;
			else
				image.addr[y * game->win_width + x] = game->texture.hex_floor;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, image.img, 0, 0);
	mlx_destroy_image(game->mlx, image.img);
}

int	render_game(t_game *game)
{
	move_player(game);
	render_frame(game);
	return (0);
}
