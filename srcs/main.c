/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:19:45 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/21 19:07:11 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	key_press(int key, t_game *game)
{
	if (key == CLOSE_BTN || key == KEY_ESC || key == KEY_Q)
		quit_cub3d(game);
	if (key == KEY_W)
		game->player.key_state[0] = 1;
	if (key == KEY_S)
		game->player.key_state[1] = 1;
	if (key == KEY_A)
		game->player.key_state[2] = 1;
	if (key == KEY_D)
		game->player.key_state[3] = 1;
	if (key == KEY_AR_L)
		game->player.key_state[4] = 1;
	if (key == KEY_AR_R)
		game->player.key_state[5] = 1;
	draw_map(game);
	return (0);
}

static int	key_release(int key, t_game *game)
{
	if (key == CLOSE_BTN || key == KEY_ESC || key == KEY_Q)
		quit_cub3d(game);
	if (key == KEY_W)
		game->player.key_state[0] = 0;
	if (key == KEY_S)
		game->player.key_state[1] = 0;
	if (key == KEY_A)
		game->player.key_state[2] = 0;
	if (key == KEY_D)
		game->player.key_state[3] = 0;
	if (key == KEY_AR_L)
		game->player.key_state[4] = 0;
	if (key == KEY_AR_R)
		game->player.key_state[5] = 0;
	return (0);
}

static int	parse_args(t_game *game, char **av)
{
	if (is_cub_file(av[1]))
		return (err("Not a .cub file", 1));
	if (read_file(av[1], game))
		return (err("Could not read file", 1));
	if (parse_file(game))
		return (free_game(game));
	if (check_map(game))
		return (free_game(game));
	if (check_textures(&game->texture))
		return (free_game(game));
	if (game->player.dir == 'N' || game->player.dir == 'S')
		init_player_north_south(&game->player);
	else
		init_player_east_west(&game->player);
	printf("Player position: %f, %f\n", game->player.pos_x, game->player.pos_y);
	printf("Player direction: %c\n", game->player.dir);
	printf("Player direction: %f, %f\n",
		game->player.dir_x, game->player.dir_y);
	printf("Player plane: %f, %f\n",
		game->player.plane_x, game->player.plane_y);
	printf("Textures: %s, %s, %s, %s\n", game->texture.north,
		game->texture.south, game->texture.east, game->texture.west);
	printf("Floor color: %ld\n", game->texture.hex_floor);
	printf("Ceiling color: %ld\n", game->texture.hex_ceiling);
	draw_map(game);
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
	game.mlx = mlx_init();
	if (!game.mlx)
		clean_exit(&game, err("Could not initialize mlx", 1));
	game.win = mlx_new_window(game.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (!game.win)
		clean_exit(&game, err("Could not create window", 1));
	init_textures(&game);
	mlx_hook(game.win, KEY_PRESS, KEY_PRESS_MASK, key_press, &game);
	mlx_hook(game.win, KEY_RELEASE, KEY_RELEASE_MASK, key_release, &game);
	mlx_hook(game.win, CLOSE_BTN, NO_EVENT_MASK, quit_cub3d, &game);
	mlx_loop_hook(game.mlx, render_game, &game);
	mlx_loop(game.mlx);
	return (0);
}
