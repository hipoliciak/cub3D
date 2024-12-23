/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:17:46 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/23 23:18:42 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_column(t_game *game, int x, t_ray ray, int tex_x)
{
	int			y;
	int			tex_y;
	double		step;
	double		tex_pos;
	int			color;

	step = 1.0 * TEX_HEIGHT / ray.line_height;
	tex_pos = (ray.draw_start - game->win_height / 2 + ray.line_height / 2)
		* step;
	y = ray.draw_start;
	while (y < ray.draw_end)
	{
		tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
		tex_pos += step;
		if (ray.side == 0 && ray.dir_x < 0)
			color = game->north_texture[tex_y * TEX_WIDTH + tex_x];
		else if (ray.side == 0 && ray.dir_x > 0)
			color = game->south_texture[tex_y * TEX_WIDTH + tex_x];
		else if (ray.side == 1 && ray.dir_y < 0)
			color = game->west_texture[tex_y * TEX_WIDTH + tex_x];
		else
			color = game->east_texture[tex_y * TEX_WIDTH + tex_x];
		game->image.addr[y * game->win_width + x] = color;
		y++;
	}
}

void	render_walls(t_game *game)
{
	int		x;
	t_ray	ray;
	int		tex_x;

	x = 0;
	while (x < game->win_width)
	{
		init_ray(game, &ray);
		calculate_ray_direction(game, &ray, x);
		calculate_step_and_side_dist(game, &ray);
		perform_dda(game, &ray);
		calculate_wall_and_tex(game, &ray, &tex_x);
		render_column(game, x, ray, tex_x);
		x++;
	}
}

void	fill_ceiling_and_floor(t_game *game, t_image *image)
{
	int		x;
	int		y;

	y = 0;
	while (y < game->win_height)
	{
		x = 0;
		while (x < game->win_width)
		{
			if (y < game->win_height / 2)
				image->addr[y * game->win_width + x] = game->hex_ceiling;
			else
				image->addr[y * game->win_width + x] = game->hex_floor;
			x++;
		}
		y++;
	}
}

void	render_frame(t_game *game)
{
	t_image	image;

	init_image(&image);
	image.img = mlx_new_image(game->mlx_ptr, game->win_width, game->win_height);
	if (!image.img)
		clean_exit(game, err("Could not create image", 1));
	image.addr = (int *)mlx_get_data_addr(image.img, &image.pixel_bits,
			&image.size_line, &image.endian);
	fill_ceiling_and_floor(game, &image);
	game->image = image;
	render_walls(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, image.img, 0, 0);
	mlx_destroy_image(game->mlx_ptr, image.img);
}

int	render_game(t_game *game)
{
	move_player(game);
	render_frame(game);
	return (0);
}
