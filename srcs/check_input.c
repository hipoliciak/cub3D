/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:06:35 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/27 15:45:31 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_cub_file(char *arg)
{
	int	ret;

	if (!arg || ft_strlen(arg) < 4)
		return (0);
	ret = ft_strncmp(&arg[ft_strlen(arg) - 4], ".cub", 4);
	if (ret != 0)
		return (1);
	return (0);
}

int	is_xpm_file(char *arg)
{
	int	ret;

	if (!arg || ft_strlen(arg) < 4)
		return (0);
	ret = ft_strncmp(&arg[ft_strlen(arg) - 4], ".xpm", 4);
	if (ret == 0)
		return (1);
	return (0);
}

int	check_textures(t_game *game)
{
	if (!game->file.north_path || !game->file.south_path
		|| !game->file.west_path || !game->file.east_path)
		return (err("Missing texture(s)", 1));
	if (!game->file.rgb_floor || !game->file.rgb_ceiling)
		return (err("Missing color(s)", 1));
	if (!is_xpm_file(game->file.north_path)
		|| !is_xpm_file(game->file.south_path)
		|| !is_xpm_file(game->file.west_path)
		|| !is_xpm_file(game->file.east_path))
		return (err("Texture not .xpm", 1));
	return (0);
}
