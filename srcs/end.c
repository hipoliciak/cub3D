/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:19:58 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/11/01 22:49:25 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	end_game_with_message(t_game *game, char *message, int error)
{
	if (game->map.map)
	{
		while (game->map.height--)
			free(game->map.map[game->map.height]);
		free(game->map.map);
	}
	if (game->textures[0].xpm_ptr)
		mlx_destroy_image(game->mlx_ptr, game->textures[0].xpm_ptr);
	if (game->textures[1].xpm_ptr)
		mlx_destroy_image(game->mlx_ptr, game->textures[1].xpm_ptr);
	if (game->textures[2].xpm_ptr)
		mlx_destroy_image(game->mlx_ptr, game->textures[2].xpm_ptr);
	if (game->textures[3].xpm_ptr)
		mlx_destroy_image(game->mlx_ptr, game->textures[3].xpm_ptr);
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
	{
		mlx_loop_end(game->mlx_ptr);
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	if (message)
	{
		ft_printf("%s\n", message);
		exit(error);
	}
	exit(0);
	return (0);
}

int	end_game(t_game *game)
{
	return (end_game_with_message(game, NULL, 0));
}
