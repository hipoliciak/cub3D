/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:19:06 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/11/03 01:26:08 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "ft_printf.h"
# include "mlx.h"
# include "key_linux.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

# define SPACE " " || "\t" || "\n" || "\v" || "\f" || "\r"

// Textures and colors
# define TEXTURE_SIZE 50
# define NO "textures/north.xpm"
# define SO "textures/south.xpm"
# define WE "textures/west.xpm"
# define EA "textures/east.xpm"
# define F	220,100,0  // Floor color in RGB
# define C	0,0,255    // Ceiling color in RGB

// Rendering constants
# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define FOV 60.0
# define NUM_RAYS 320

// Movement and raycasting
# define MOVE_STEP 0.1
# define STEP_SIZE 0.05
# define M_PI 3.14159265358979323846

typedef struct s_map
{
    char    **map;
    int     width;
    int     height;
}   t_map;

typedef struct s_image
{
    void    *xpm_ptr;
    int     x;
    int     y;
    int     *data;
    int     width;
    int     height;
}   t_image;

typedef struct s_player
{
    double  x;
    double  y;
    double  angle;
    int     tile_x;
    int     tile_y;
}   t_player;

typedef struct s_game
{
    void        *mlx_ptr;
    void        *win_ptr;
    t_map       map;
    t_image     textures[4];  // Textures for walls
    t_image     image;        // Main image buffer for rendering
    t_player    player;
    int         ceiling_color;
    int         floor_color;
}   t_game;

// Map
int		check_extension(char *path);
void	read_map(t_game *game, char *path);
void	fill_map(t_game *game, char *path);
void	check_characters(t_game *game);
void	check_walls(t_game *game);

// Init
void    init_positions(t_game *game);
void    init_angle(t_game *game, int x, int y);
void    init_game(t_game *game);

// Engine
void    update_tile_position(t_game *game);
void    move_forward(t_game *game);
void    move_backward(t_game *game);
void    rotate_left(t_game *game);
void    rotate_right(t_game *game);

// Graphics
void    init_textures(t_game *game);
t_image create_texture(t_game *game, char *path);
void    render_texture(t_game *game, t_image *sprite, int line, int column);
// void    render_frame(t_game *game);
// void    draw_floor_and_ceiling(t_game *game);
// void    cast_rays(t_game *game);
// void    draw_vertical_slice(t_game *game, int x, int draw_start, int draw_end);
// void    put_pixel(t_game *game, int x, int y, int color);

// End
int     destroy_map_and_textures(t_game *game);
int     end_game_with_message(t_game *game, char *message, int error);
int     end_game(t_game *game);

// Utils
int     open_map(char *path, t_game *game);
char    *split_line(char *line);
int     draw_map(t_game *game);

// // Additional utility functions for raycasting
// double calculate_distance(double ray_dir_x, double ray_dir_y, double side_dist_x, double side_dist_y, int side);
// int select_texture(int side, double ray_dir_x, double ray_dir_y);
// int get_texture_pixel(t_image *texture, int x, int y);

#endif


// #ifndef CUB3D_H
// # define CUB3D_H

// # include "libft.h"
// # include "ft_printf.h"
// # include "mlx.h"
// # include "key_linux.h"
// # include <fcntl.h>
// # include <math.h>
// # include <stdio.h>

// // Textures and colors
// # define TEXTURE_SIZE 50
// # define NO "textures/north.xpm"
// # define SO "textures/south.xpm"
// # define WE "textures/west.xpm"
// # define EA "textures/east.xpm"
// # define F	220,100,0
// # define C	0,0,255

// // Rendering constants
// # define FOV 60.0
// # define NUM_RAYS 320

// // Movement and raycasting
// # define MOVE_STEP 0.1
// # define STEP_SIZE 0.05
// # define M_PI 3.14159265358979323846

// typedef struct s_map
// {
// 	char	**map;
// 	int		width;
// 	int		height;
// }	t_map;

// typedef struct s_image
// {
// 	void	*xpm_ptr;
// 	int		x;
// 	int		y;
// }	t_image;

// typedef struct s_player
// {
// 	double	x;
// 	double	y;
// 	double	angle;
// 	int		tile_x;
// 	int		tile_y;
// }	t_player;

// typedef struct s_game
// {
// 	void		*mlx_ptr;
// 	void		*win_ptr;
// 	t_map		map;
// 	t_image		textures[4];
// 	t_image		image;
// 	t_player	player;
// }	t_game;

// // Map
// void	read_map(t_game *game, char *path);
// void	fill_map(t_game *game, char *path);
// void	validate_elements(t_game *game);
// void	check_walls(t_game *game);

// // Init
// void	init_positions(t_game *game);
// void	init_angle(t_game *game, int x, int y);
// void	init_game(t_game *game);

// // Engine
// void	update_tile_position(t_game *game);
// void	move_forward(t_game *game);
// void	move_backward(t_game *game);
// void	rotate_left(t_game *game);
// void	rotate_right(t_game *game);

// // Graphics
// void	init_textures(t_game *game);
// t_image	create_texture(t_game *game, char *path);
// void	render_texture(t_game *game, t_image *sprite, int line, int column);

// // End
// int		destroy_map_and_textures(t_game *game);
// int		end_game_with_message(t_game *game, char *message, int error);
// int		end_game(t_game *game);

// // Utils
// int		open_map(char *path, t_game *game);
// char	*split_line(char *line);
// int		draw_map(t_game *game);

// #endif