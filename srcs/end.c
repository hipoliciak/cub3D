/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:19:58 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/15 23:27:28 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_tab(void **tab)
{
    int i = 0;

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

void	free_texture(t_tex *textures)
{
	if (textures->north)
		free(textures->north);
	if (textures->south)
		free(textures->south);
	if (textures->west)
		free(textures->west);
	if (textures->east)
		free(textures->east);
	if (textures->floor)
		free(textures->floor);
	if (textures->ceiling)
		free(textures->ceiling);
}

int	free_game(t_game *game)
{
	if (game->textures)
	{
		free(game->textures[0]);
		free(game->textures[1]);
		free(game->textures[2]);
		free(game->textures[3]);
		free(game->textures);
	}
	if (game->map.fd > 0)
		close(game->map.fd);
	if (game->map.map)
	{
		free_tab((void **)game->map.map);
		game->map.map = NULL;
	}
	free_texture(&game->texture);
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
