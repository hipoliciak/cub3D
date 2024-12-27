/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:19:58 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/27 15:44:16 by dmodrzej         ###   ########.fr       */
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

void	free_textures_info(t_file *file)
{
	if (file->north_path)
		free(file->north_path);
	if (file->south_path)
		free(file->south_path);
	if (file->west_path)
		free(file->west_path);
	if (file->east_path)
		free(file->east_path);
	if (file->rgb_floor)
		free(file->rgb_floor);
	if (file->rgb_ceiling)
		free(file->rgb_ceiling);
}

int	free_game(t_game *game)
{
	if (game->file.file)
	{
		free_tab((void **)game->file.file);
		game->file.file = NULL;
	}
	if (game->file.map)
	{
		free_tab((void **)game->file.map);
		game->file.map = NULL;
	}
	free_textures_info(&game->file);
	if (game->north_texture)
		free(game->north_texture);
	if (game->south_texture)
		free(game->south_texture);
	if (game->west_texture)
		free(game->west_texture);
	if (game->east_texture)
		free(game->east_texture);
	return (1);
}

void	clean_exit(t_game *game, int code)
{
	if (!game)
		exit(code);
	if (game->win_ptr && game->mlx_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		mlx_loop_end(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	free_game(game);
	exit(code);
}

int	end_game(t_game *game)
{
	clean_exit(game, 0);
	return (0);
}
