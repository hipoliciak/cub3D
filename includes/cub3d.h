/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:19:06 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/23 23:26:06 by dmodrzej         ###   ########.fr       */
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

// Macros
# define WIN_WIDTH 1200
# define WIN_HEIGHT 800
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define MOVESPEED 0.05
# define ROTSPEED 0.02

// Structs
typedef struct s_image
{
	void		*img;
	int			*addr;
	int			pixel_bits;
	int			size_line;
	int			endian;
}	t_image;

typedef struct s_texdata
{
	char		*north_path;
	char		*south_path;
	char		*west_path;
	char		*east_path;
	int			*rgb_floor;
	int			*rgb_ceiling;
	int			texture_width;
	int			texture_height;
}	t_texdata;

typedef struct s_map
{
	int			fd;
	char		**map;
	int			start_of_map;
	int			end_of_map;
	int			height;
}	t_map;

typedef struct s_ray
{
	double		dir_x;
	double		dir_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			map_x;
	int			map_y;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		wall_x;
}	t_ray;

typedef struct s_player
{
	char		dir;
	int			player_count;
	double		dir_x;
	double		dir_y;
	double		pos_x;
	double		pos_y;
	double		plane_x;
	double		plane_y;
	int			key_state[6];
}	t_player;

typedef struct s_game
{
	void			*mlx_ptr;
	void			*win_ptr;
	int				win_width;
	int				win_height;
	t_map			map;
	t_player		player;
	int				*north_texture;
	int				*south_texture;
	int				*west_texture;
	int				*east_texture;
	unsigned long	hex_floor;
	unsigned long	hex_ceiling;
	t_texdata		texdata;
	t_image			image;
}	t_game;

// Init
void			init_game(t_game *game);
void			init_player(t_player *player);
void			init_map(t_map *map);
void			init_texdata(t_texdata *texdata);
void			init_image(t_image *image);

// Get game info
int				read_file(t_game *game, char *path);
void			fill_map(t_game *game);
int				get_number_of_lines(char *path);
int				parse_file(t_game *game);
int				process_line_content(t_game *game, char **map, int i, int j);
int				set_direction_textures(t_texdata *texdata, char *line, int j);
char			*get_texture_path(char *line, int j);
int				set_color_textures(t_texdata *texdata, char *line, int j);
int				*parse_rgb(char *line);
int				check_rgb_strings(char **rgb_strings, int count);
int				rgb_str_digits(char *str);
int				*convert_rgb_to_int(char **rgb_strings);

// Check file
int				is_cub_file(char *arg);
int				check_texdata(t_game *game);
int				is_xpm_file(char *arg);

// Check map
int				check_map(t_game *game);
int				check_map_content(t_map *map);
int				check_map_top_bottom(char **map, int i, int j);
int				check_map_inside(char **map, int i, int j, int k);

// Init player
int				check_player_position(t_game *game, char **map);
void			init_player_north_south(t_player *player);
void			init_player_east_west(t_player *player);

// Graphics
void			create_textures(t_game *game);
int				*load_texture(t_game *game, char *path);
int				*copy_texture_to_buffer(t_game *game, t_image *img);
unsigned long	convert_rgb_to_hex(int *rgb);

// Engine
int				move_player(t_game *game);
void			try_move(t_game *game, double new_x, double new_y);
void			rotate_player(t_player *p, double angle);

// Render
int				render_game(t_game *game);
void			render_frame(t_game *game);
void			fill_ceiling_and_floor(t_game *game, t_image *image);
void			render_walls(t_game *game);
void			render_column(t_game *game, int x, t_ray ray, int tex_x);
void			init_ray(t_game *game, t_ray *ray);
void			calculate_ray_direction(t_game *game, t_ray *ray, int x);
void			calculate_step_and_side_dist(t_game *game, t_ray *ray);
void			perform_dda(t_game *game, t_ray *ray);
void			calculate_wall_and_tex(t_game *game, t_ray *ray, int *tex_x);

// Utils
int				count_map_lines(t_game *game, int map_start);
int				err(char *str, int code);
int				ft_isspace(int c);
int				ft_isspace_not_nl(int c);
int				is_surrounded_by_space_or_wall(char **map, int i, int j);

// End
void			clean_exit(t_game *game, int code);
int				end_game(t_game *game);
void			free_tab(void **tab);
void			free_texdata(t_texdata *texdata);
int				free_game(t_game *game);

// Debug
int				draw_map(t_game *game);

#endif