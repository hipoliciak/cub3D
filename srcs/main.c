/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:19:45 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/11/01 22:52:53 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	key_hook(int keycode, t_game *game)
{
	if (keycode == KEY_ESC || keycode == KEY_Q)
		end_game(game);
	else if (keycode == KEY_W || keycode == KEY_AR_U)
		move_forward(game);
	else if (keycode == KEY_S || keycode == KEY_AR_D)
		move_backward(game);
	else if (keycode == KEY_A || keycode == KEY_AR_L)
		rotate_left(game);
	else if (keycode == KEY_D || keycode == KEY_AR_R)
		rotate_right(game);
	draw_map(game);
	return (0);
}

static void	init_game(t_game *game)
{
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->map.map = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->map.x_player_pos = 0;
	game->map.y_player_pos = 0;
	game->player.x = 0;
	game->player.y = 0;
	game->player.angle = 0;
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc <= 1)
		return (1);
	init_game(&game);
	game.mlx_ptr = mlx_init();
	if (!game.mlx_ptr)
		return (1);
	init_textures(&game);
	read_map(&game, argv[1]);
	fill_map(&game, argv[1]);
	validate_elements(&game);
	check_walls(&game);
	game.win_ptr = mlx_new_window(game.mlx_ptr, game.map.width * TEXTURE_SIZE,
			game.map.height * TEXTURE_SIZE, "Let's play Cub3D!");
	if (!game.win_ptr)
		return (1);
	init_positions(&game);
	mlx_key_hook(game.win_ptr, key_hook, &game);
	mlx_hook(game.win_ptr, CLOSE_BTN, 0, end_game, &game);
	mlx_hook(game.win_ptr, EXPOSE, EXPOSURE_MASK, draw_map, &game);
	mlx_loop(game.mlx_ptr);
	return (0);
}
