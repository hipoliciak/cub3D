/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:19:06 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/10/30 23:19:10 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "ft_printf.h"
# include "mlx.h"
# include "key_linux.h"
# include <fcntl.h>

# define SPRITE_SIZE 512

# define COLLECTIBLE "textures/painting-20.xpm"
# define EXIT "textures/painting-21.xpm"
# define WALL "textures/painting-24.xpm"
# define FLOOR "textures/painting-32.xpm"
# define PLAYER_R "textures/painting-20.xpm"
# define PLAYER_L "textures/painting-20.xpm"
# define PLAYER_U "textures/painting-20.xpm"
# define PLAYER_D "textures/painting-20.xpm"

typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
	int		x_player_pos;
	int		y_player_pos;
	int		x_exit_pos;
	int		y_exit_pos;
}	t_map;

typedef struct s_image
{
	void	*xpm_ptr;
	int		x;
	int		y;
}	t_image;

typedef struct s_player
{
	t_image	player_r;
	t_image	player_l;
	t_image	player_u;
	t_image	player_d;
	char	direction;
}	t_player;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			collectibles;
	int			moves;
	t_map		map;
	t_image		collectible;
	t_image		exit;
	t_image		wall;
	t_image		floor;
	t_player	player;
}	t_game;

//Engine
void	init_positions(t_game *game);
void	move_up(t_game *game);
void	move_down(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);

//Graphics
void	init_sprites(t_game *game);
t_image	create_sprite(t_game *game, char *path);
void	render_sprite(t_game *game, t_image *sprite, int line, int column);
void	render_player(t_game *game, int line, int column);
int		render_map(t_game *game);

//Map
void	read_map(t_game *game, char *path);
void	fill_map(t_game *game, char *path);
void	validate_elements(t_game *game);
void	check_walls(t_game *game);
void	count_elements(t_game *game);

//Utils
int		open_map(char *path, t_game *game);
char	*split_line(char *line);
void	display_moves_and_collectibles(t_game *game);
// void	draw_map(t_game *game);

//Messages
int		end_game(t_game *game, char *message, int code);
void	destroy_images(t_game *game);
void	exit_message(t_game *game, char *message, int code);

#endif