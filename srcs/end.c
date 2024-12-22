/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:19:58 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/22 17:48:51 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tab(void **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
		tab = NULL;
	}
}

void	free_texdata(t_texdata *texdata)
{
	if (texdata->north_path)
		free(texdata->north_path);
	if (texdata->south_path)
		free(texdata->south_path);
	if (texdata->west_path)
		free(texdata->west_path);
	if (texdata->east_path)
		free(texdata->east_path);
	if (texdata->rgb_floor)
		free(texdata->rgb_floor);
	if (texdata->rgb_ceiling)
		free(texdata->rgb_ceiling);
}

int	free_game(t_game *game)
{
	if (game->map.fd > 0)
		close(game->map.fd);
	if (game->map.map)
	{
		free_tab((void **)game->map.map);
		game->map.map = NULL;
	}
	if (game->north_texture)
		free(game->north_texture);
	if (game->south_texture)
		free(game->south_texture);
	if (game->west_texture)
		free(game->west_texture);
	if (game->east_texture)
		free(game->east_texture);
	free_texdata(&game->texdata);
	return (1);
}

void	clean_exit(t_game *game, int code)
{
	if (!game)
		exit(code);
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		mlx_loop_end(game->mlx);
		free(game->mlx);
	}
	free_game(game);
	exit(code);
}

int	quit_cub3d(t_game *game)
{
	clean_exit(game, 0);
	return (0);
}
