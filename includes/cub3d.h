/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:19:06 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/16 21:27:13 by dmodrzej         ###   ########.fr       */
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
# include <stdbool.h>

// Rendering constants
# define FOV 60
// # define NUM_RAYS 320

// Movement and raycasting
# define TILE_SIZE 10
# define MOVE_STEP 0.1
# define STEP_SIZE 0.05
# define M_PI 3.14159265358979323846
# define WIN_WIDTH 1200
# define WIN_HEIGHT 800
# define TEX_SIZE 64
# define MOVESPEED 0.1
# define ROTSPEED 0.02

typedef struct s_image
{
	void	*img;
	int		*addr;
	int		pixel_bits;
	int		size_line;
	int		endian;
}	t_image;

typedef struct s_tex
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	int				*floor;
	int				*ceiling;
	unsigned long	hex_floor;
	unsigned long	hex_ceiling;
	int				size;
}	t_tex;

typedef struct s_map
{
	int		fd;
	int		line_count;
	char	*path;
	char	**map;
	int		height;
	int		width;
	int		start_of_map;
	int		end_of_map;
}	t_map;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	angle;
	double	rays_len[FOV];
	int		tile_x;
	int		tile_y;
	char	dir;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		key_state[6];
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			win_height;
	int			win_width;
	t_map		map;
	t_player	player;
	int			**textures;
	t_tex		texture;
}	t_game;

// Init
void			init_game(t_game *game);
void			init_player(t_player *player);
void			init_map(t_map *map);
void			init_mlx(t_game *game);
void			init_tex(t_tex *textures);
void			init_textures(t_game *game);
void			init_texture_img(t_game *game, t_image *image, char *path);
// void			init_img(t_game *game, t_image *image, int width, int height);
void			init_img_clean(t_image *img);

// Check file
int				is_cub_file(char *arg);
int				check_textures(t_tex *textures);
int				is_xpm_file(char *arg);

// Check map
int				check_map(t_game *game);
int				check_map_content(t_map *map);
int				check_map_top_bottom(char **map, int i, int j);
int				check_map_inside(char **map, int i, int j, int k);

// Init player
int				check_player_position(t_game *game, char **map);
int				check_position_is_valid(t_game *game, char **map);
void			init_player_north_south(t_player *player);
void			init_player_east_west(t_player *player);

// Get game info
int				read_file(char *path, t_game *game);
void			fill_tab(int row, t_game *game);
int				get_number_of_lines(char *path);
int				parse_file(t_game *game);
int				process_line_content(t_game *game, char **map, int i, int j);
int				set_direction_textures(t_tex *textures, char *line, int j);
char			*get_texture_path(char *line, int j);
int				set_color_textures(t_tex *textures, char *line, int j);
int				*parse_rgb(char *line);
int				check_rgb_strings(char **rgb_strings, int count);
int				rgb_str_digits(char *str);
int				*convert_rgb(char **rgb_strings);
unsigned long	convert_rgb_to_hex(int *rgb_tab);

// Engine
void    update_tile_position(t_game *game);
void    move_forward(t_game *game);
void    move_backward(t_game *game);
void    rotate_left(t_game *game);
void    rotate_right(t_game *game);
void	cast_rays(t_game *game);

// Graphics
void    init_textures(t_game *game);
t_image create_texture(t_game *game, char *path);
void    render_texture(t_game *game, t_image *sprite, int line, int column);

// Movement
int				move_player(t_game *game);
void			try_move(t_game *game, double new_x, double new_y);
void			rotate_player(t_player *p, double angle);

// Utils
int				count_map_lines(t_game *game, int map_start);
int				err(char *str, int code);
int				ft_isspace(int c);
int				ft_isspace_not_nl(int c);
int				is_surrounded_by_space_or_wall(char **map, int i, int j);
int				draw_map(t_game *game);

// End
void			clean_exit(t_game *game, int code);
int				quit_cub3d(t_game *game);
void			free_tab(void **tab);
void			free_texture(t_tex *textures);
int				free_game(t_game *game);

#endif