/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:19:58 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/11/02 02:05:18 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	destroy_map_and_textures(t_game *game)
{
	int	i;

	i = 0;
	if (game->map.map)
	{
		while (i < game->map.height)
			free(game->map.map[i++]);
		free(game->map.map);
	}
	i = 0;
	while (i < 4)
	{
		if (game->textures[i].xpm_ptr)
			mlx_destroy_image(game->mlx_ptr, game->textures[i].xpm_ptr);
		i++;
	}
	return (0);
}

int	end_game_with_message(t_game *game, char *message, int error)
{
	destroy_map_and_textures(game);
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
