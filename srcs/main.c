/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:19:45 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/16 16:31:53 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	key_hook(int keycode, t_game *game)
{
	if (keycode == KEY_ESC || keycode == KEY_Q)
		quit_cub3d(game);
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

// static int	key_press(int key, t_game *game)
// {
// 	if (key == CLOSE_BTN || key == KEY_ESC || key == KEY_Q)
// 		quit_cub3d(game);
// 	if (key == KEY_W)
// 		game->player.key_state[0] = 1;
// 	if (key == KEY_S)
// 		game->player.key_state[1] = 1;
// 	if (key == KEY_A)
// 		game->player.key_state[2] = 1;
// 	if (key == KEY_D)
// 		game->player.key_state[3] = 1;
// 	if (key == KEY_AR_L)
// 		game->player.key_state[4] = 1;
// 	if (key == KEY_AR_R)
// 		game->player.key_state[5] = 1;
// 	return (0);
// }

// static int	key_release(int key, t_game *game)
// {
// 	if (key == CLOSE_BTN || key == KEY_ESC || key == KEY_Q)
// 		quit_cub3d(game);
// 	if (key == KEY_W)
// 		game->player.key_state[0] = 0;
// 	if (key == KEY_S)
// 		game->player.key_state[1] = 0;
// 	if (key == KEY_A)
// 		game->player.key_state[2] = 0;
// 	if (key == KEY_D)
// 		game->player.key_state[3] = 0;
// 	if (key == KEY_AR_L)
// 		game->player.key_state[4] = 0;
// 	if (key == KEY_AR_R)
// 		game->player.key_state[5] = 0;
// 	return (0);
// }

static int	parse_args(t_game *game, char **av)
{
	// int	i;

	// i = 0;
	if (is_cub_file(av[1]))
		return (err("Not a .cub file", 1));
	if (read_file(av[1], game))
		return (err("Could not read file", 1));
	if (parse_file(game))
		return (free_game(game));
	// while (game->map.map[i])
	// {
	// 	printf("%s\n", game->map.map[i]);
	// 	i++;
	// }
	if (check_map(game))
		return (free_game(game));
	if (check_textures(&game->texture))
		return (free_game(game));
	if (game->player.dir == 'N' || game->player.dir == 'S')
		init_player_north_south(&game->player);
	else
		init_player_east_west(&game->player);
	printf("Player position: %f, %f\n", game->player.pos_x, game->player.pos_y);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (err("Wrong number of arguments", 1));
	init_game(&game);
	if (parse_args(&game, av))
		return (1);
	init_mlx(&game);
	init_textures(&game);
	mlx_key_hook(game.win, key_hook, &game);
	mlx_hook(game.win, CLOSE_BTN, 0, quit_cub3d, &game);
	mlx_hook(game.win, EXPOSE, EXPOSURE_MASK, draw_map, &game);
	// mlx_hook(game.win, KEY_PRESS, KEY_PRESS_MASK, key_press, &game);
	// mlx_hook(game.win, KEY_RELEASE, KEY_RELEASE_MASK, key_release, &game);
	// mlx_hook(game.win, CLOSE_BTN, NO_EVENT_MASK, quit_cub3d, &game);
	// mlx_loop_hook(game.mlx, render_game, &game);
	mlx_loop(game.mlx);
	return (0);
}
