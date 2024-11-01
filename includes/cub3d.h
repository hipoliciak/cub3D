/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:19:06 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/11/01 22:49:45 by dmodrzej         ###   ########.fr       */
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

// Textures and colors
# define TEXTURE_SIZE 50
# define NO "textures/north.xpm"
# define SO "textures/south.xpm"
# define WE "textures/west.xpm"
# define EA "textures/east.xpm"
# define F	220,100,0
# define C	0,0,255

// Rendering constants
# define FOV 60.0
# define NUM_RAYS 320

// Movement and Raycasting
# define MOVE_STEP 0.1
# define STEP_SIZE 0.05
# define M_PI 3.14159265358979323846

typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
	int		x_player_pos;
	int		y_player_pos;
}	t_map;

typedef struct s_image
{
	void	*xpm_ptr;
	int		x;
	int		y;
}	t_image;

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
}	t_player;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_map		map;
	t_image		textures[4];
	t_image		image;
	t_player	player;
}	t_game;

// Engine
void	init_positions(t_game *game);
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	rotate_left(t_game *game);
void	rotate_right(t_game *game);

// Graphics
void	init_textures(t_game *game);
t_image	create_texture(t_game *game, char *path);
void	render_sprite(t_game *game, t_image *sprite, int line, int column);

// Map
void	read_map(t_game *game, char *path);
void	fill_map(t_game *game, char *path);
void	validate_elements(t_game *game);
void	check_walls(t_game *game);

// Utils
int		open_map(char *path, t_game *game);
char	*split_line(char *line);
int		draw_map(t_game *game);

// End
int		end_game_with_message(t_game *game, char *message, int error);
int		end_game(t_game *game);

#endif